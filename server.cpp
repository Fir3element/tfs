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
#if defined __WINDOWS__ || defined WIN32
#include <winerror.h>
#endif

#include "server.h"
#include "connection.h"
#include "outputmessage.h"

bool ServicePort::add(Service_ptr newService)
{
	for(ServiceVec::const_iterator it = m_services.begin(); it != m_services.end(); ++it)
	{
		if((*it)->isSingleSocket())
			return false;
	}

	m_services.push_back(newService);
	return true;
}

void ServicePort::open(uint16_t port)
{
	m_serverPort = port;
	try
	{
		m_acceptor = new boost::asio::ip::tcp::acceptor(m_io_service, boost::asio::ip::tcp::endpoint(
			boost::asio::ip::address(boost::asio::ip::address_v4(INADDR_ANY)), m_serverPort), false);
	}
	catch(boost::system::system_error& error)
	{
		std::cout << "> ERROR: Can bind only one socket to a specific port (" << m_serverPort << ")." << std::endl;
		std::cout << "The exact error was: " << error.what() << std::endl;
	}

	accept();
}

void ServicePort::close()
{
	if(m_acceptor)
	{
		if(m_acceptor->is_open())
		{
			boost::system::error_code error;
			m_acceptor->close(error);
			if(error)
				PRINT_ASIO_ERROR("Closing listen socket");

		}

		delete m_acceptor;
		m_acceptor = NULL;
	}
}

void ServicePort::accept()
{
	if(!m_acceptor)
	{
#ifdef __DEBUG_NET__
		std::cout << "[Error - ServerPort::accept] NULL m_acceptor." << std::endl;
#endif
		return;
	}

	if(Connection* connection = ConnectionManager::getInstance()->createConnection(m_io_service, shared_from_this()))
		m_acceptor->async_accept(connection->getHandle(), boost::bind(&ServicePort::handle, this, connection,
			boost::asio::placeholders::error));
}

void ServicePort::handle(Connection* connection, const boost::system::error_code& error)
{
	if(!error)
	{
		if(m_services.empty())
		{
#ifdef __DEBUG_NET__
			std::cout << "[Error - ServerPort::handle] No services running!" << std::endl;
#endif
			return;
		}

		if(m_services.front()->isSingleSocket())
			connection->handle(m_services.front()->makeProtocol(connection));
		else
			connection->accept();

#ifdef __DEBUG_NET_DETAIL__
		std::cout << "handle - OK" << std::endl;
#endif
		accept();
	}
	else if(error != boost::asio::error::operation_aborted)
	{
		m_listenErrors++;
		close();

		std::cout << "[Warning - ServerPort::handle] Listener error occured, total " << m_listenErrors << "." << std::endl;
		open(m_serverPort);
	}
#ifdef __DEBUG_NET__
	else
		std::cout << "[Error - ServerPort::handle] Operation aborted." << std::endl;
#endif
}

Protocol* ServicePort::makeProtocol(bool checksum, NetworkMessage& msg) const
{
	uint8_t protocolId = msg.GetByte();
	for(ServiceVec::const_iterator it = m_services.begin(); it != m_services.end(); ++it)
	{
		Service_ptr service = (*it);
		if(checksum && service->hasChecksum() && protocolId == service->getProtocolId())
			return service->makeProtocol(NULL);
		else if(!service->hasChecksum())
			return service->makeProtocol(NULL);
	}

	return NULL;
}

void ServiceManager::stop()
{
	for(AcceptorsMap::iterator it = m_acceptors.begin(); it != m_acceptors.end(); ++it)
		m_io_service.post(boost::bind(&ServicePort::close, it->second.get()));

	OutputMessagePool::getInstance()->stop();
}

std::list<uint16_t> ServiceManager::getPorts() const
{
	std::list<uint16_t> ports;
	for(AcceptorsMap::const_iterator it = m_acceptors.begin(); it != m_acceptors.end(); ++it)
		ports.push_back(it->first);

	ports.unique();
	return ports;
}
