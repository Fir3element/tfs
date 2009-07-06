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

#ifndef __ENUMS__
#define __ENUMS__

#include <string>
#include <list>

enum DatabaseEngine_t
{
	DATABASE_ENGINE_NONE = 0,
	DATABASE_ENGINE_MYSQL = 1,
	DATABASE_ENGINE_SQLITE = 2,
	DATABASE_ENGINE_POSTGRESQL = 3,
	DATABASE_ENGINE_ODBC = 4
};

enum PasswordType_t
{
	PASSWORD_TYPE_PLAIN = 0,
	PASSWORD_TYPE_MD5 = 1,
	PASSWORD_TYPE_SHA1 = 2
};

enum GuildLevel_t
{
	GUILDLEVEL_MEMBER = 1,
	GUILDLEVEL_VICE = 2,
	GUILDLEVEL_LEADER = 3
};

enum OperatingSystem_t
{
	CLIENTOS_LINUX = 0x01,
	CLIENTOS_WINDOWS = 0x02
};

enum Channels_t
{
	CHANNEL_GUILD = 0x00,
	//CHANNEL_STAFF = 0x01,
	//CHANNEL_COUNSELOR = 0x02,
	CHANNEL_RVR = 0x03,
	CHANNEL_GAMECHAT = 0x04,
	CHANNEL_TRADE = 0x05,
	CHANNEL_RLCHAT = 0x06,
	CHANNEL_TRADEROOK = 0x07,
	CHANNEL_PARTY = 0x08,
	CHANNEL_HELP = 0x09,
	CHANNEL_DEFAULT = 0xFFFF - 1, //internal usage only, there is no such channel but it means that message was writen on default channel
	CHANNEL_PRIVATE = 0xFFFF
};

enum ViolationAction_t
{
	ACTION_NOTATION = 0,
	ACTION_NAMEREPORT,
	ACTION_BANISHMENT,
	ACTION_BANREPORT,
	ACTION_BANFINAL,
	ACTION_BANREPORTFINAL,
	ACTION_STATEMENT,
	ACTION_DELETION
};

enum RaceType_t
{
	RACE_NONE	= 0,
	RACE_VENOM 	= 1,
	RACE_BLOOD	= 2,
	RACE_UNDEAD	= 3,
	RACE_FIRE	= 4,
	RACE_ENERGY	= 5
};

enum CombatType_t
{
	COMBAT_FIRST		= 0,
	COMBAT_NONE		= COMBAT_FIRST,
	COMBAT_PHYSICALDAMAGE	= 1 << 0,
	COMBAT_ENERGYDAMAGE	= 1 << 1,
	COMBAT_EARTHDAMAGE	= 1 << 2,
	COMBAT_FIREDAMAGE	= 1 << 3,
	COMBAT_UNDEFINEDDAMAGE	= 1 << 4,
	COMBAT_LIFEDRAIN	= 1 << 5,
	COMBAT_MANADRAIN	= 1 << 6,
	COMBAT_HEALING		= 1 << 7,
	COMBAT_DROWNDAMAGE	= 1 << 8,
	COMBAT_ICEDAMAGE	= 1 << 9,
	COMBAT_HOLYDAMAGE	= 1 << 10,
	COMBAT_DEATHDAMAGE      = 1 << 11,
	COMBAT_LAST		= COMBAT_DEATHDAMAGE
};

enum CombatParam_t
{
	COMBATPARAM_COMBATTYPE = 1,
	COMBATPARAM_EFFECT = 2,
	COMBATPARAM_DISTANCEEFFECT = 3,
	COMBATPARAM_BLOCKEDBYSHIELD = 4,
	COMBATPARAM_BLOCKEDBYARMOR = 5,
	COMBATPARAM_TARGETCASTERORTOPMOST = 6,
	COMBATPARAM_CREATEITEM = 7,
	COMBATPARAM_AGGRESSIVE = 8,
	COMBATPARAM_DISPEL = 9,
	COMBATPARAM_USECHARGES = 10,
	COMBATPARAM_TARGETPLAYERSORSUMMONS = 11
};

enum CallBackParam_t
{
	CALLBACKPARAM_LEVELMAGICVALUE = 1,
	CALLBACKPARAM_SKILLVALUE = 2,
	CALLBACKPARAM_TARGETTILECALLBACK = 3,
	CALLBACKPARAM_TARGETCREATURECALLBACK = 4
};

enum ConditionParam_t
{
	CONDITIONPARAM_OWNER = 1,
	CONDITIONPARAM_TICKS = 2,
	CONDITIONPARAM_OUTFIT = 3,
	CONDITIONPARAM_HEALTHGAIN = 4,
	CONDITIONPARAM_HEALTHTICKS = 5,
	CONDITIONPARAM_MANAGAIN = 6,
	CONDITIONPARAM_MANATICKS = 7,
	CONDITIONPARAM_DELAYED = 8,
	CONDITIONPARAM_SPEED = 9,
	CONDITIONPARAM_LIGHT_LEVEL = 10,
	CONDITIONPARAM_LIGHT_COLOR = 11,
	CONDITIONPARAM_SOULGAIN = 12,
	CONDITIONPARAM_SOULTICKS = 13,
	CONDITIONPARAM_MINVALUE = 14,
	CONDITIONPARAM_MAXVALUE = 15,
	CONDITIONPARAM_STARTVALUE = 16,
	CONDITIONPARAM_TICKINTERVAL = 17,
	CONDITIONPARAM_FORCEUPDATE = 18,
	CONDITIONPARAM_SKILL_MELEE = 19,
	CONDITIONPARAM_SKILL_FIST = 20,
	CONDITIONPARAM_SKILL_CLUB = 21,
	CONDITIONPARAM_SKILL_SWORD = 22,
	CONDITIONPARAM_SKILL_AXE = 23,
	CONDITIONPARAM_SKILL_DISTANCE = 24,
	CONDITIONPARAM_SKILL_SHIELD = 25,
	CONDITIONPARAM_SKILL_FISHING = 26,
	CONDITIONPARAM_STAT_MAXHEALTH = 27,
	CONDITIONPARAM_STAT_MAXMANA = 28,
	CONDITIONPARAM_STAT_SOUL = 29,
	CONDITIONPARAM_STAT_MAGICLEVEL = 30,
	CONDITIONPARAM_STAT_MAXHEALTHPERCENT = 31,
	CONDITIONPARAM_STAT_MAXMANAPERCENT = 32,
	CONDITIONPARAM_STAT_SOULPERCENT = 33,
	CONDITIONPARAM_STAT_MAGICLEVELPERCENT = 34,
	CONDITIONPARAM_SKILL_MELEEPERCENT = 35,
	CONDITIONPARAM_SKILL_FISTPERCENT = 36,
	CONDITIONPARAM_SKILL_CLUBPERCENT = 37,
	CONDITIONPARAM_SKILL_SWORDPERCENT = 38,
	CONDITIONPARAM_SKILL_AXEPERCENT = 39,
	CONDITIONPARAM_SKILL_DISTANCEPERCENT = 40,
	CONDITIONPARAM_SKILL_SHIELDPERCENT = 41,
	CONDITIONPARAM_SKILL_FISHINGPERCENT = 42,
	CONDITIONPARAM_PERIODICDAMAGE = 43,
	CONDITIONPARAM_BUFF = 44,
	CONDITIONPARAM_SUBID = 45
};

enum BlockType_t
{
	BLOCK_NONE = 0,
	BLOCK_DEFENSE,
	BLOCK_ARMOR,
	BLOCK_IMMUNITY
};

enum skills_t
{
	SKILL_FIRST = 0,
	SKILL_FIST = SKILL_FIRST,
	SKILL_CLUB = 1,
	SKILL_SWORD = 2,
	SKILL_AXE = 3,
	SKILL_DIST = 4,
	SKILL_SHIELD = 5,
	SKILL_FISH = 6,
	SKILL__MAGLEVEL = 7,
	SKILL__LEVEL = 8,
	SKILL_LAST = SKILL_FISH,
	SKILL__LAST = SKILL__LEVEL
};

enum stats_t
{
	STAT_FIRST = 0,
	STAT_MAXHEALTH = STAT_FIRST,
	STAT_MAXMANA,
	STAT_SOUL,
	STAT_LEVEL,
	STAT_MAGICLEVEL,
	STAT_LAST = STAT_MAGICLEVEL
};

enum lossTypes_t
{
	LOSS_FIRST = 0,
	LOSS_EXPERIENCE = LOSS_FIRST,
	LOSS_MANA = 1,
	LOSS_SKILLS = 2,
	LOSS_CONTAINERS = 3,
	LOSS_ITEMS = 4,
	LOSS_LAST = LOSS_ITEMS
};

enum formulaType_t
{
	FORMULA_UNDEFINED = 0,
	FORMULA_LEVELMAGIC = 1,
	FORMULA_SKILL = 2,
	FORMULA_VALUE = 3
};

enum ConditionId_t
{
	CONDITIONID_DEFAULT = -1,
	CONDITIONID_COMBAT = 0,
	CONDITIONID_HEAD = 1,
	CONDITIONID_NECKLACE = 2,
	CONDITIONID_BACKPACK = 3,
	CONDITIONID_ARMOR = 4,
	CONDITIONID_RIGHT = 5,
	CONDITIONID_LEFT = 6,
	CONDITIONID_LEGS = 7,
	CONDITIONID_FEET = 8,
	CONDITIONID_RING = 9,
	CONDITIONID_AMMO = 10,
	CONDITIONID_OUTFIT = 11
};

enum PlayerSex_t
{
	PLAYERSEX_FEMALE = 0,
	PLAYERSEX_MALE = 1
};

enum CharacterTypes_t
{
	PLAYER_MALE_1 = 0x80,
	PLAYER_MALE_2 = 0x81,
	PLAYER_MALE_3 = 0x82,
	PLAYER_MALE_4 = 0x83,
	PLAYER_MALE_5 = 0x84,
	PLAYER_MALE_6 = 0x85,
	PLAYER_MALE_7 = 0x86,
	PLAYER_FEMALE_1 = 0x88,
	PLAYER_FEMALE_2 = 0x89,
	PLAYER_FEMALE_3 = 0x8A,
	PLAYER_FEMALE_4 = 0x8B,
	PLAYER_FEMALE_5 = 0x8C,
	PLAYER_FEMALE_6 = 0x8D,
	PLAYER_FEMALE_7 = 0x8E,
};

struct Outfit_t
{
	Outfit_t() {lookHead = lookBody = lookLegs = lookFeet = lookType = lookTypeEx = lookAddons = 0;}
	uint16_t lookType, lookTypeEx;
	uint8_t lookHead, lookBody, lookLegs, lookFeet, lookAddons;
};

struct LightInfo
{
	uint32_t level, color;

	LightInfo() {level = color = 0;}
	LightInfo(uint32_t _level, uint32_t _color):
		level(_level), color(_color) {}
};

struct ShopInfo
{
	uint32_t itemId;
	int32_t subType, buyPrice, sellPrice;
	std::string itemName;

	ShopInfo()
	{
		itemId = 0;
		subType = 1;
		buyPrice = sellPrice = -1;
		itemName = "";
	}
	ShopInfo(uint32_t _itemId, int32_t _subType = 1, int32_t _buyPrice = -1, int32_t _sellPrice = -1,
		const std::string& _itemName = ""): itemId(_itemId), subType(_subType), buyPrice(_buyPrice),
		sellPrice(_sellPrice), itemName(_itemName) {}
};

typedef std::list<ShopInfo> ShopInfoList;
#endif
