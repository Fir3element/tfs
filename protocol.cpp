//////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//////////////////////////////////////////////////////////////////////
#include "otpch.h"

#include "definitions.h"

#if defined WIN32
#include <winerror.h>
#endif

#include "protocol.h"
#include "connection.h"
#include "outputmessage.h"
#include "rsa.h"

void Protocol::onSendMessage(OutputMessage* msg)
{
	#ifdef __DEBUG_NET_DETAIL__
	std::cout << "Protocol::onSendMessage" << std::endl;
	#endif

	if(!m_rawMessages)
	{
		msg->writeMessageLength();
		if(m_encryptionEnabled)
		{
			#ifdef __DEBUG_NET_DETAIL__
			std::cout << "Protocol::onSendMessage - encrypt" << std::endl;
			#endif
			XTEA_encrypt(*msg);

			addChecksum(*msg);

			int32_t messageLength = msg->getMessageLength();
			if((messageLength % 8) != 0)
				msg->AddPaddingBytes(8 - (messageLength % 8));

			uint16_t *size = (uint16_t*)msg->getBuffer();
			*size = *((uint16_t*)msg->getBuffer()) + 4;
		}
	}

	if(msg == m_outputBuffer)
		m_outputBuffer = NULL;
}

void Protocol::onRecvMessage(NetworkMessage& msg)
{
	#ifdef __DEBUG_NET_DETAIL__
	std::cout << "Protocol::onRecvMessage" << std::endl;
	#endif

	if(m_encryptionEnabled)
	{
		#ifdef __DEBUG_NET_DETAIL__
		std::cout << "Protocol::onRecvMessage - decrypt" << std::endl;
		#endif

		XTEA_decrypt(msg);
	}
	parsePacket(msg);
}

OutputMessage* Protocol::getOutputBuffer()
{
	if(m_outputBuffer)
		return m_outputBuffer;

	else if(m_connection)
	{
		m_outputBuffer = OutputMessagePool::getInstance()->getOutputMessage(this);
		return m_outputBuffer;
	}
	else
		return NULL;
}

void Protocol::deleteProtocolTask()
{
	//dispather thread
	if(m_outputBuffer)
		OutputMessagePool::getInstance()->releaseMessage(m_outputBuffer);

	delete this;
}

void Protocol::XTEA_encrypt(OutputMessage& msg)
{
	uint32_t k[4];
	k[0] = m_key[0];
	k[1] = m_key[1];
	k[2] = m_key[2];
	k[3] = m_key[3];

	int32_t messageLength = msg.getMessageLength();

	//add bytes until reach 8 multiple
	uint32_t n;
	if((messageLength % 8) != 0)
	{
		n = 8 - (messageLength % 8);
		msg.AddPaddingBytes(n);
		messageLength = messageLength + n;
	}

	int read_pos = 0;
	uint32_t* buffer = (uint32_t*)msg.getBodyBuffer();
	while(read_pos < messageLength / 4)
	{
		uint32_t v0 = buffer[read_pos], v1 = buffer[read_pos + 1];
		uint32_t delta = 0x61C88647;
		uint32_t sum = 0;

		for(int32_t i = 0; i < 32; i++)
		{
			v0 += ((v1 << 4 ^ v1 >> 5) + v1) ^ (sum + k[sum & 3]);
			sum -= delta;
			v1 += ((v0 << 4 ^ v0 >> 5) + v0) ^ (sum + k[sum>>11 & 3]);
		}
		buffer[read_pos] = v0; buffer[read_pos + 1] = v1;
		read_pos = read_pos + 2;
	}
	msg.addCryptoHeader();
}

bool Protocol::XTEA_decrypt(NetworkMessage& msg)
{
	if((msg.getMessageLength() - 2) % 8 != 0)
	{
		std::cout << "Failure: [Protocol::XTEA_decrypt]. Not valid encrypted message size" << std::endl;
		return false;
	}

	//
	uint32_t k[4];
	k[0] = m_key[0];
	k[1] = m_key[1];
	k[2] = m_key[2];
	k[3] = m_key[3];

	uint32_t* buffer = (uint32_t*)msg.getBodyBuffer();
	int32_t read_pos = 0;
	int32_t messageLength = msg.getMessageLength();
	while(read_pos < messageLength / 4)
	{
		uint32_t v0 = buffer[read_pos], v1 = buffer[read_pos + 1];
		uint32_t delta = 0x61C88647;
		uint32_t sum = 0xC6EF3720;

		for(int32_t i = 0; i < 32; i++)
		{
			v1 -= ((v0 << 4 ^ v0 >> 5) + v0) ^ (sum + k[sum>>11 & 3]);
			sum += delta;
			v0 -= ((v1 << 4 ^ v1 >> 5) + v1) ^ (sum + k[sum & 3]);
		}
		buffer[read_pos] = v0; buffer[read_pos + 1] = v1;
		read_pos = read_pos + 2;
	}
	//

	int32_t tmp = msg.GetU16();
	if(tmp > msg.getMessageLength() - 4)
	{
		std::cout << "Failure: [Protocol::XTEA_decrypt]. Not valid unencrypted message size" << std::endl;
		return false;
	}

	msg.setMessageLength(tmp);
	return true;
}

bool Protocol::RSA_decrypt(RSA* rsa, NetworkMessage& msg)
{
	if(msg.getMessageLength() - msg.getReadPos() != 128)
	{
		std::cout << "Warning: [Protocol::RSA_decrypt]. Not valid packet size" << std::endl;
		return false;
	}

	rsa->decrypt((char*)(msg.getBuffer() + msg.getReadPos()), 128);

	if(msg.GetByte() != 0)
	{
		std::cout << "Warning: [Protocol::RSA_decrypt]. First byte != 0" << std::endl;
		return false;
	}

	return true;
}

uint32_t Protocol::getIP() const
{
	if(getConnection())
		return getConnection()->getIP();

	return 0;
}

uint32_t Protocol::getChecksum(uint8_t *data, size_t len) /* data: Pointer to the data to be summed; len is in bytes */
{
	uint32_t a = 1, b = 0;
	const uint16_t MOD_ADLER=65521;
	while(len > 0)
	{
		size_t tlen = len > 5552 ? 5552 : len;
		len -= tlen;
		do
		{
			a += *data++;
			b += a;
		}
		while(--tlen);
		a %= MOD_ADLER;
		b %= MOD_ADLER;
	}
	return (b << 16) | a;
}

/*uint32_t Protocol::getChecksum(NetworkMessage& msg)
{
    // for 8.3+
    // implementation of adler algorithm as per wikipedia
    // this will just calculate checksum, it still needs to be added
    // preparation
    const uint16_t MOD_ADLER=65521;
    uint8_t* data = ((uint8_t*)msg.getBodyBuffer());
    size_t len = msg.getMessageLength();

    // algo
    uint32_t a = 1, b = 0;

    while (len > 0)
    {
        size_t tlen = len > 5552 ? 5552 : len;
        len -= tlen;
        do
        {
            a += *data++;
            b += a;
        } while (--tlen);

        a %= MOD_ADLER;
        b %= MOD_ADLER;
    }

    return (b << 16) | a;

}*/

void Protocol::addChecksum(NetworkMessage& msg)
{
    // for 8.3+
    // adds 32-bit adler checksum to bytes 2-6 and shifts remaining onwards
    // only call after size header has been added!
	unsigned char *buffer = (unsigned char *)msg.getBuffer();
	int32_t size = msg.getSize();

	uint32_t sum = getChecksum(buffer + 2, size - 2);
	std::cout << "Checksum: " << sum << std::endl;
 	memmove(buffer + 6, buffer + 2, size-2);
	*((uint32_t*)(buffer + 2)) = sum;
	/*memmove(msg.getBodyBuffer() + 6, msg.getBodyBuffer()+2, msg.getMessageLength()+2);
	*((uint32_t*)(msg.getBodyBuffer())) = sum;*/

}
