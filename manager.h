////////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////
#ifndef __MANAGER__
#define __MANAGER__
#include "otsystem.h"

#include "protocol.h"
#include "textlogger.h"

enum
{
	MP_MSG_LOGIN = 1,
	MP_MSG_PING = 2,
	MP_MSG_KEEP_ALIVE = 3,
	MP_MSG_LUA = 4,

	MP_MSG_ERROR = 1,
	MP_MSG_HELLO = 2,
	MP_MSG_LOGIN_OK = 3,
	MP_MSG_LOGIN_FAILED = 4,
	MP_MSG_PING = 5,
	MP_MSG_OUTPUT = 6
};

class ProtocolManager;
class NetworkMessage;

class Manager
{
	public:
		virtual ~Manager() {}
		static Manager* getInstance()
		{
			static Manager instance;
			return &instance;
		}

		bool addConnection(ProtocolManager* client);
		bool acceptConnection(ProtocolManager* client);
		void removeConnection(ProtocolManager* client);

		bool allow(uint32_t ip) const;
		void output(const std::string& message);

	protected:
		Manager() {}

		typedef std::map<ProtocolManager*, bool> ConnectionMap;
		ConnectionMap m_connections;
};


class ProtocolManager : public Protocol
{
	public:
#ifdef __ENABLE_SERVER_DIAGNOSTIC__
		static uint32_t protocolManagerCount;
#endif
		virtual void onRecvFirstMessage(NetworkMessage& msg);

		ProtocolManager(Connection_ptr connection): Protocol(connection)
		{
			m_state = NO_CONNECTED;
			m_loginTries = m_lastCommand = 0;
			m_startTime = time(NULL);
#ifdef __ENABLE_SERVER_DIAGNOSTIC__
			protocolManagerCount++;
#endif
		}
		virtual ~ProtocolManager()
		{
#ifdef __ENABLE_SERVER_DIAGNOSTIC__
			protocolManagerCount--;
#endif
		}

		enum {protocolId = 0xFD};
		enum {isSingleSocket = false};
		enum {hasChecksum = false};
		static const char* protocolName() {return "manager protocol";}

		void output(const std::string& message);

	protected:
		enum ProtocolState_t
		{
			NO_CONNECTED,
			NO_LOGGED_IN,
			LOGGED_IN,
		};

		virtual void parsePacket(NetworkMessage& msg);
		virtual void deleteProtocolTask();

	private:
		void addLogLine(LogType_t type, std::string message);

		int32_t m_loginTries;
		ProtocolState_t m_state;
		uint32_t m_lastCommand, m_startTime;
};
#endif
