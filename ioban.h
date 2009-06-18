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

#ifndef __IOBAN__
#define __IOBAN__
#include "otsystem.h"

#include "enums.h"

enum BanType_t
{
	BANTYPE_IP_BANISHMENT = 1,
	BANTYPE_NAMELOCK = 2,
	BANTYPE_BANISHMENT = 3,
	BANTYPE_NOTATION = 4,
	BANTYPE_DELETION = 5
};

struct Ban
{
	BanType_t type;
	ViolationAction_t action;
	uint32_t id, added, adminid, reason;
	int32_t expires;
	std::string comment, value, param, statement;
};

typedef std::vector<Ban> BansVec;

class IOBan
{
	protected:
		IOBan() {}

	public:
		virtual ~IOBan() {}
		static IOBan* getInstance()
		{
			static IOBan instance;
			return &instance;
		}

		bool isIpBanished(uint32_t ip, uint32_t mask = 0xFFFFFFFF) const;
		bool isNamelocked(uint32_t guid) const;
		bool isNamelocked(std::string name) const;
		bool isBanished(uint32_t account) const;
		bool isDeleted(uint32_t account) const;

		bool addIpBanishment(uint32_t ip, time_t banTime, std::string comment, uint32_t gamemaster,
			uint32_t mask = 0xFFFFFFFF) const;
		bool addNamelock(uint32_t playerId, uint32_t reasonId, ViolationAction_t actionId, std::string comment,
			uint32_t gamemaster, std::string statement = "") const;
		bool addNamelock(std::string name, uint32_t reasonId, ViolationAction_t actionId, std::string comment,
			uint32_t gamemaster, std::string statement = "") const;
		bool addBanishment(uint32_t account, time_t banTime, uint32_t reasonId, ViolationAction_t actionId,
			std::string comment, uint32_t gamemaster, std::string statement = "") const;
		bool addDeletion(uint32_t account, uint32_t reasonId, ViolationAction_t actionId, std::string comment,
			uint32_t gamemaster, std::string statement = "") const;
		bool addNotation(uint32_t account, uint32_t reasonId, ViolationAction_t actionId, std::string comment,
			uint32_t gamemaster, std::string statement = "") const;

		bool removeIpBanishment(uint32_t ip, uint32_t mask = 0xFFFFFFFF) const;
		bool removeNamelock(uint32_t guid) const;
		bool removeNamelock(std::string name) const;
		bool removeBanishment(uint32_t account) const;
		bool removeDeletion(uint32_t account) const;
		bool removeNotations(uint32_t account) const;

		bool getData(uint32_t value, Ban& ban, const std::string& ignore = "4") const;
		std::vector<Ban> getList(BanType_t type, uint32_t value = 0);
		uint32_t getNotationsCount(uint32_t account) const;
		bool clearTemporials() const;
};
#endif
