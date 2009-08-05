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
#include "otpch.h"
#include <iostream>
#include <libxml/xmlmemory.h>

#include "items.h"
#include "condition.h"
#include "weapons.h"

#include "configmanager.h"
#include "spells.h"

extern Spells* g_spells;
extern ConfigManager g_config;

uint32_t Items::dwMajorVersion = 0;
uint32_t Items::dwMinorVersion = 0;
uint32_t Items::dwBuildNumber = 0;

ItemType::ItemType()
{
	group = ITEM_GROUP_NONE;
	type = ITEM_TYPE_NONE;
	stackable = useable = alwaysOnTop = lookThrough = pickupable = rotable = hasHeight = forceSerialize = false;
	blockSolid = blockProjectile = blockPathFind = allowPickupable = false;
	moveable = true;
	alwaysOnTopOrder = 0;
	rotateTo = 0;

	wieldInfo = 0;
	minReqLevel = 0;
	minReqMagicLevel = 0;

	runeMagLevel = runeLevel = 0;

	speed = id = 0;
	clientId = 100;
	maxItems = 8; //maximum size if this is a container
	weight = 0; //weight of the item, e.g. throwing distance depends on it
	showCount = true;
	weaponType = WEAPON_NONE;
	slotPosition = SLOTP_HAND | SLOTP_AMMO;
	wieldPosition = SLOT_HAND;
	ammoType = AMMO_NONE;
	ammoAction = AMMOACTION_NONE;
	shootType = (ShootType_t)0;
	magicEffect = NM_ME_NONE;
	attack = extraAttack = 0;
	defense = extraDefense = 0;
	attackSpeed = 0;
	armor = 0;
	decayTo = -1;
	decayTime = 0;
	stopTime = false;
	corpseType = RACE_NONE;
	fluidSource = FLUID_NONE;
	clientCharges = false;
	allowDistRead = false;

	isVertical = isHorizontal = isHangable = false;
	lightLevel = lightColor = 0;

	maxTextLen = 0;
	canReadText = canWriteText = false;
	writeOnceItemId = 0;

	transformEquipTo = transformDeEquipTo = 0;
	showDuration = showCharges = showAttributes = false;
	charges	= 0;
	hitChance = maxHitChance = breakChance = -1;
	shootRange = 1;

	condition = NULL;
	combatType = COMBAT_NONE;

	replaceable = true;
	worth = 0;

	bedPartnerDir = NORTH;
	transformToOnUse[PLAYERSEX_MALE] = 0;
	transformToOnUse[PLAYERSEX_FEMALE] = 0;
	transformToFree = 0;
	levelDoor = 0;

	for(int32_t i = CHANGE_PRE_FIRST; i < CHANGE_LAST; ++i)
		floorChange[i] = false;
}

ItemType::~ItemType()
{
	delete condition;
}

void Items::clear()
{
	//TODO: clear items?
	moneyMap.clear();
	randomizationMap.clear();
	reverseItemMap.clear();
}

bool Items::reload()
{
	//TODO: reload items?
	/*for(ItemMap::iterator it = items.begin(); it != items.end(); ++it)
		delete it->second->condition;

	clear();
	return loadFromXml();*/
	return false;
}

int32_t Items::loadFromOtb(std::string file)
{
	FileLoader f;
	if(!f.openFile(file.c_str(), false, true))
		return f.getError();

	uint32_t type;
	NODE node = f.getChildNode(NO_NODE, type);

	PropStream props;
	if(f.getProps(node,props))
	{
		//4 byte flags
		//attributes
		//0x01 = version data
		uint32_t flags;
		if(!props.GET_ULONG(flags))
			return ERROR_INVALID_FORMAT;

		attribute_t attr;
		if(!props.GET_VALUE(attr))
			return ERROR_INVALID_FORMAT;

		if(attr == ROOT_ATTR_VERSION)
		{
			datasize_t datalen = 0;
			if(!props.GET_VALUE(datalen))
				return ERROR_INVALID_FORMAT;

			if(datalen != sizeof(VERSIONINFO))
				return ERROR_INVALID_FORMAT;

			VERSIONINFO *vi;
			if(!props.GET_STRUCT(vi))
				return ERROR_INVALID_FORMAT;

			Items::dwMajorVersion = vi->dwMajorVersion; //items otb format file version
			Items::dwMinorVersion = vi->dwMinorVersion; //client version
			Items::dwBuildNumber = vi->dwBuildNumber; //revision
		}
	}

	if(Items::dwMajorVersion == 0xFFFFFFFF)
		std::cout << "[Warning - Items::loadFromOtb] items.otb using generic client version." << std::endl;
	else if(Items::dwMajorVersion < 3)
	{
		std::cout << "[Error - Items::loadFromOtb] Old version detected, a newer version of items.otb is required." << std::endl;
		return ERROR_INVALID_FORMAT;
	}
	else if(Items::dwMajorVersion > 3)
	{
		std::cout << "[Error - Items::loadFromOtb] New version detected, an older version of items.otb is required." << std::endl;
		return ERROR_INVALID_FORMAT;
	}
	else if(Items::dwMinorVersion != CLIENT_VERSION_850)
	{
		std::cout << "[Error - Items::loadFromOtb] Another (client) version of items.otb is required." << std::endl;
		return ERROR_INVALID_FORMAT;
	}

	node = f.getChildNode(node, type);
	while(node != NO_NODE)
	{
		PropStream props;
		if(!f.getProps(node,props))
			return f.getError();

		flags_t flags;
		ItemType* iType = new ItemType();
		iType->group = (itemgroup_t)type;
		switch(type)
		{
			case ITEM_GROUP_CONTAINER:
				iType->type = ITEM_TYPE_CONTAINER;
				break;
			case ITEM_GROUP_DOOR:
				//not used
				iType->type = ITEM_TYPE_DOOR;
				break;
			case ITEM_GROUP_MAGICFIELD:
				//not used
				iType->type = ITEM_TYPE_MAGICFIELD;
				break;
			case ITEM_GROUP_TELEPORT:
				//not used
				iType->type = ITEM_TYPE_TELEPORT;
				break;
			case ITEM_GROUP_NONE:
			case ITEM_GROUP_GROUND:
			case ITEM_GROUP_SPLASH:
			case ITEM_GROUP_FLUID:
			case ITEM_GROUP_CHARGES:
			case ITEM_GROUP_DEPRECATED:
				break;
			default:
				return ERROR_INVALID_FORMAT;
		}

		//read 4 byte flags
		if(!props.GET_VALUE(flags))
			return ERROR_INVALID_FORMAT;

		iType->blockSolid = hasBitSet(FLAG_BLOCK_SOLID, flags);
		iType->blockProjectile = hasBitSet(FLAG_BLOCK_PROJECTILE, flags);
		iType->blockPathFind = hasBitSet(FLAG_BLOCK_PATHFIND, flags);
		iType->hasHeight = hasBitSet(FLAG_HAS_HEIGHT, flags);
		iType->useable = hasBitSet(FLAG_USEABLE, flags);
		iType->pickupable = hasBitSet(FLAG_PICKUPABLE, flags);
		iType->moveable = hasBitSet(FLAG_MOVEABLE, flags);
		iType->stackable = hasBitSet(FLAG_STACKABLE, flags);

		iType->alwaysOnTop = hasBitSet(FLAG_ALWAYSONTOP, flags);
		iType->isVertical = hasBitSet(FLAG_VERTICAL, flags);
		iType->isHorizontal = hasBitSet(FLAG_HORIZONTAL, flags);
		iType->isHangable = hasBitSet(FLAG_HANGABLE, flags);
		iType->allowDistRead = hasBitSet(FLAG_ALLOWDISTREAD, flags);
		iType->rotable = hasBitSet(FLAG_ROTABLE, flags);
		iType->canReadText = hasBitSet(FLAG_READABLE, flags);
		iType->clientCharges = hasBitSet(FLAG_CLIENTCHARGES, flags);
		iType->lookThrough = hasBitSet(FLAG_LOOKTHROUGH, flags);

		attribute_t attrib;
		datasize_t datalen = 0;
		while(props.GET_VALUE(attrib))
		{
			//size of data
			if(!props.GET_VALUE(datalen))
			{
				delete iType;
				return ERROR_INVALID_FORMAT;
			}

			switch(attrib)
			{
				case ITEM_ATTR_SERVERID:
				{
					if(datalen != sizeof(uint16_t))
						return ERROR_INVALID_FORMAT;

					uint16_t serverid;
					if(!props.GET_USHORT(serverid))
						return ERROR_INVALID_FORMAT;

					if(serverid > 20000 && serverid < 20100)
						serverid = serverid - 20000;

					iType->id = serverid;
					break;
				}
				case ITEM_ATTR_CLIENTID:
				{
					if(datalen != sizeof(uint16_t))
						return ERROR_INVALID_FORMAT;

					uint16_t clientid;
					if(!props.GET_USHORT(clientid))
						return ERROR_INVALID_FORMAT;

					iType->clientId = clientid;
					break;
				}
				case ITEM_ATTR_SPEED:
				{
					if(datalen != sizeof(uint16_t))
						return ERROR_INVALID_FORMAT;

					uint16_t speed;
					if(!props.GET_USHORT(speed))
						return ERROR_INVALID_FORMAT;

					iType->speed = speed;
					break;
				}
				case ITEM_ATTR_LIGHT2:
				{
					if(datalen != sizeof(lightBlock2))
						return ERROR_INVALID_FORMAT;

					lightBlock2* lb2;
					if(!props.GET_STRUCT(lb2))
						return ERROR_INVALID_FORMAT;

					iType->lightLevel = lb2->lightLevel;
					iType->lightColor = lb2->lightColor;
					break;
				}
				case ITEM_ATTR_TOPORDER:
				{
					if(datalen != sizeof(uint8_t))
						return ERROR_INVALID_FORMAT;

					uint8_t v;
					if(!props.GET_UCHAR(v))
						return ERROR_INVALID_FORMAT;

					iType->alwaysOnTopOrder = v;
					break;
				}
				default:
				{
					//skip unknown attributes
					if(!props.SKIP_N(datalen))
						return ERROR_INVALID_FORMAT;
					break;
				}
			}
		}

		reverseItemMap[iType->clientId] = iType->id;
		// store the found item
		items.addElement(iType, iType->id);
		node = f.getNextNode(node, type);
	}

	return ERROR_NONE;
}

bool Items::loadFromXml()
{
	xmlDocPtr itemDoc = xmlParseFile(getFilePath(FILE_TYPE_OTHER, "items/items.xml").c_str()),
		paletteDoc = xmlParseFile(getFilePath(FILE_TYPE_OTHER, "items/randomization.xml").c_str());
	if(!itemDoc)
	{
		std::cout << "[Warning - Items::loadFromXml] Cannot load items file." << std::endl;
		std::cout << getLastXMLError() << std::endl;
		return false;
	}

	if(!paletteDoc)
	{
		std::cout << "[Warning - Items::loadFromXml] Cannot load randomization file." << std::endl;
		std::cout << getLastXMLError() << std::endl;
		return false;
	}

	xmlNodePtr itemNode, paletteNode, itemRoot = xmlDocGetRootElement(itemDoc), paletteRoot = xmlDocGetRootElement(paletteDoc);
	if(xmlStrcmp(itemRoot->name,(const xmlChar*)"items"))
	{
		xmlFreeDoc(itemDoc);
		xmlFreeDoc(paletteDoc);

		std::cout << "[Warning - Items::loadFromXml] Malformed items file." << std::endl;
		return false;
	}

	if(xmlStrcmp(paletteRoot->name,(const xmlChar*)"randomization"))
	{
		xmlFreeDoc(itemDoc);
		xmlFreeDoc(paletteDoc);

		std::cout << "[Warning - Items::loadFromXml] Malformed randomization file." << std::endl;
		return false;
	}

	int32_t intValue, id = 0, endId = 0, fromId = 0, toId = 0;
	IntegerVec intVector, endIntVector;
	std::string strValue, endStrValue;
	StringVec strVector;

	itemNode = itemRoot->children;
	while(itemNode)
	{
		if(xmlStrcmp(itemNode->name,(const xmlChar*)"item") == 0)
		{
			if(readXMLInteger(itemNode, "id", intValue))
				parseItemNode(itemNode, intValue);
			else if(readXMLString(itemNode, "fromid", strValue) && readXMLString(itemNode, "toid", endStrValue))
			{
				intVector = vectorAtoi(explodeString(strValue, ";"));
				endIntVector = vectorAtoi(explodeString(endStrValue, ";"));
				if(intVector[0] && endIntVector[0] && intVector.size() == endIntVector.size())
				{
					size_t size = intVector.size();
					for(size_t i = 0; i < size; ++i)
					{
						parseItemNode(itemNode, intVector[i]);
						while(intVector[i] < endIntVector[i])
						{
							intVector[i]++;
							parseItemNode(itemNode, intVector[i]);
						}
					}
				}
				else
					std::cout << "[Warning - Items::loadFromXml] Malformed entry (from: \"" << strValue << "\", to: \"" << endStrValue << "\")" << std::endl;
			}
			else
				std::cout << "[Warning - Items::loadFromXml] No itemid found" << std::endl;
		}

		itemNode = itemNode->next;
	}

	xmlFreeDoc(itemDoc);
	for(uint32_t i = 0; i < Item::items.size(); ++i) //lets do some checks...
	{
		const ItemType* it = Item::items.getElement(i);
		if(!it)
			continue;

		//check bed items
		if((it->transformToFree != 0 || it->transformToOnUse[PLAYERSEX_FEMALE] != 0 || it->transformToOnUse[PLAYERSEX_MALE] != 0) && it->type != ITEM_TYPE_BED)
			std::cout << "[Warning - Items::loadFromXml] Item " << it->id << " is not set as a bed-type." << std::endl;
	}

	paletteNode = paletteRoot->children;
	while(paletteNode)
	{
		if(!xmlStrcmp(paletteNode->name, (const xmlChar*)"config"))
		{
			if(readXMLInteger(paletteNode, "chance", intValue) || readXMLInteger(paletteNode, "defaultChance", intValue))
			{
				if(intValue > 100)
				{
					intValue = 100;
					std::cout << "[Warning - Items::loadFromXml] Randomize chance cannot be higher than 100." << std::endl;
				}

				m_randomizationChance = intValue;
			}
		}
		else if(!xmlStrcmp(paletteNode->name, (const xmlChar*)"palette"))
		{
			if(readXMLString(paletteNode, "randomize", strValue))
			{
				std::vector<int32_t> idList = vectorAtoi(explodeString(strValue, ";"));
				if(idList.size() >= 2)
				{
					if(idList[0] < idList[1])
					{
						fromId = idList[0];
						toId = idList[1];
					}
					else
						std::cout << "[Warning - Items::loadFromXml] Randomize min cannot be higher than max." << std::endl;
				}

				int32_t chance;
				if(readXMLInteger(paletteNode, "chance", intValue))
				{
					if(intValue > 100)
					{
						intValue = 100;
						std::cout << "[Warning: Items::loadRandomization] Randomize chance cannot be higher than 100." << std::endl;
					}

					chance = intValue;
				}
				else
					chance = getRandomizationChance();

				if(readXMLInteger(paletteNode, "itemid", id))
					parseRandomizationBlock(id, fromId, toId, chance);
				else if(readXMLInteger(paletteNode, "fromid", id) && readXMLInteger(paletteNode, "toid", endId))
				{
					parseRandomizationBlock(id, fromId, toId, chance);
					while(id < endId)
						parseRandomizationBlock(++id, fromId, toId, chance);
				}
			}
		}

		paletteNode = paletteNode->next;
	}

	xmlFreeDoc(paletteDoc);
	return true;
}

void Items::parseItemNode(xmlNodePtr itemNode, uint32_t id)
{
	int32_t intValue;
	std::string strValue;

	if(id > 20000 && id < 20100)
	{
		id = id - 20000;

		ItemType* iType = new ItemType();
		iType->id = id;
		items.addElement(iType, iType->id);
	}

	ItemType& it = Item::items.getItemType(id);
	if(!it.name.empty() && (!readXMLString(itemNode, "override", strValue) || !booleanString(strValue)))
		std::cout << "[Warning - Items::loadFromXml] Duplicate registered item with id " << id << std::endl;

	if(readXMLString(itemNode, "name", strValue))
		it.name = strValue;

	if(readXMLString(itemNode, "article", strValue))
		it.article = strValue;

	if(readXMLString(itemNode, "plural", strValue))
		it.pluralName = strValue;

	xmlNodePtr itemAttributesNode = itemNode->children;
	while(itemAttributesNode)
	{
		if(readXMLString(itemAttributesNode, "key", strValue))
		{
			std::string tmpStrValue = asLowerCaseString(strValue);
			if(tmpStrValue == "type")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
				{
					tmpStrValue = asLowerCaseString(strValue);
					if(tmpStrValue == "container")
					{
						it.type = ITEM_TYPE_CONTAINER;
						it.group = ITEM_GROUP_CONTAINER;
					}
					else if(tmpStrValue == "key")
						it.type = ITEM_TYPE_KEY;
					else if(tmpStrValue == "magicfield")
						it.type = ITEM_TYPE_MAGICFIELD;
					else if(tmpStrValue == "depot")
						it.type = ITEM_TYPE_DEPOT;
					else if(tmpStrValue == "mailbox")
						it.type = ITEM_TYPE_MAILBOX;
					else if(tmpStrValue == "trashholder")
						it.type = ITEM_TYPE_TRASHHOLDER;
					else if(tmpStrValue == "teleport")
						it.type = ITEM_TYPE_TELEPORT;
					else if(tmpStrValue == "door")
						it.type = ITEM_TYPE_DOOR;
					else if(tmpStrValue == "bed")
						it.type = ITEM_TYPE_BED;
					else
						std::cout << "[Warning - Items::loadFromXml] Unknown type " << strValue << std::endl;
				}
			}
			else if(tmpStrValue == "name")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
					it.name = strValue;
			}
			else if(tmpStrValue == "article")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
					it.article = strValue;
			}
			else if(tmpStrValue == "plural")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
					it.pluralName = strValue;
			}
			else if(tmpStrValue == "description")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
					it.description = strValue;
			}
			else if(tmpStrValue == "runespellname")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
					it.runeSpellName = strValue;
			}
			else if(tmpStrValue == "weight")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.weight = intValue / 100.f;
			}
			else if(tmpStrValue == "showcount")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.showCount = (intValue != 0);
			}
			else if(tmpStrValue == "armor")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.armor = intValue;
			}
			else if(tmpStrValue == "defense")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.defense = intValue;
			}
			else if(tmpStrValue == "extradefense" || tmpStrValue == "extradef")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.extraDefense = intValue;
			}
			else if(tmpStrValue == "attack")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.attack = intValue;
			}
			else if(tmpStrValue == "extraattack" || tmpStrValue == "extraatk")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.extraAttack = intValue;
			}
			else if(tmpStrValue == "attackspeed")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.attackSpeed = intValue;
			}
			else if(tmpStrValue == "rotateto")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.rotateTo = intValue;
			}
			else if(tmpStrValue == "moveable" || tmpStrValue == "movable")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.moveable = (intValue != 0);
			}
			else if(tmpStrValue == "blockprojectile")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.blockProjectile = (intValue != 0);
			}
			else if(tmpStrValue == "allowpickupable")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.allowPickupable = (intValue != 0);
			}
			else if(tmpStrValue == "floorchange")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
				{
					tmpStrValue = asLowerCaseString(strValue);
					if(tmpStrValue == "down")
						it.floorChange[CHANGE_DOWN] = true;
					else if(tmpStrValue == "north")
						it.floorChange[CHANGE_NORTH] = true;
					else if(tmpStrValue == "south")
						it.floorChange[CHANGE_SOUTH] = true;
					else if(tmpStrValue == "west")
						it.floorChange[CHANGE_WEST] = true;
					else if(tmpStrValue == "east")
						it.floorChange[CHANGE_EAST] = true;
					else if(tmpStrValue == "northex")
						it.floorChange[CHANGE_NORTH_EX] = true;
					else if(tmpStrValue == "southex")
						it.floorChange[CHANGE_SOUTH_EX] = true;
					else if(tmpStrValue == "westex")
						it.floorChange[CHANGE_WEST_EX] = true;
					else if(tmpStrValue == "eastex")
						it.floorChange[CHANGE_EAST_EX] = true;
				}
			}
			else if(tmpStrValue == "corpsetype")
			{
				tmpStrValue = asLowerCaseString(strValue);
				if(readXMLString(itemAttributesNode, "value", strValue))
				{
					tmpStrValue = asLowerCaseString(strValue);
					if(tmpStrValue == "venom")
						it.corpseType = RACE_VENOM;
					else if(tmpStrValue == "blood")
						it.corpseType = RACE_BLOOD;
					else if(tmpStrValue == "undead")
						it.corpseType = RACE_UNDEAD;
					else if(tmpStrValue == "fire")
						it.corpseType = RACE_FIRE;
					else if(tmpStrValue == "energy")
						it.corpseType = RACE_ENERGY;
					else
						std::cout << "[Warning - Items::loadFromXml] Unknown corpseType " << strValue << std::endl;
				}
			}
			else if(tmpStrValue == "containersize")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.maxItems = intValue;
			}
			else if(tmpStrValue == "fluidsource")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
				{
					tmpStrValue = asLowerCaseString(strValue);
					FluidTypes_t fluid = getFluidType(tmpStrValue);
					if(fluid != FLUID_NONE)
						it.fluidSource = fluid;
					else
						std::cout << "[Warning - Items::loadFromXml] Unknown fluidSource " << strValue << std::endl;
				}
			}
			else if(tmpStrValue == "writeable" || tmpStrValue == "writable")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.canWriteText = (intValue != 0);
					it.canReadText = (intValue != 0);
				}
			}
			else if(tmpStrValue == "readable")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.canReadText = (intValue != 0);
			}
			else if(tmpStrValue == "maxtextlen" || tmpStrValue == "maxtextlength")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.maxTextLen = intValue;
			}
			else if(tmpStrValue == "writeonceitemid")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.writeOnceItemId = intValue;
			}
			else if(tmpStrValue == "worth")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					if(moneyMap.find(intValue) != moneyMap.end())
						std::cout << "[Warning - Items::loadFromXml] Duplicated money item " << id << " with worth " << intValue << "!" << std::endl;
					else
					{
						moneyMap[intValue] = id;
						it.worth = intValue;
					}
				}
			}
			else if(tmpStrValue == "forceserialize" || tmpStrValue == "forceserialization" || tmpStrValue == "forcesave")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.forceSerialize = (intValue != 0);
			}
			else if(tmpStrValue == "leveldoor")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.levelDoor = intValue;
			}
			else if(tmpStrValue == "weapontype")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
				{
					tmpStrValue = asLowerCaseString(strValue);
					if(tmpStrValue == "sword")
						it.weaponType = WEAPON_SWORD;
					else if(tmpStrValue == "club")
						it.weaponType = WEAPON_CLUB;
					else if(tmpStrValue == "axe")
						it.weaponType = WEAPON_AXE;
					else if(tmpStrValue == "shield")
						it.weaponType = WEAPON_SHIELD;
					else if(tmpStrValue == "distance")
						it.weaponType = WEAPON_DIST;
					else if(tmpStrValue == "wand" || tmpStrValue == "rod")
						it.weaponType = WEAPON_WAND;
					else if(tmpStrValue == "ammunition")
						it.weaponType = WEAPON_AMMO;
					else if(tmpStrValue == "fist")
						it.weaponType = WEAPON_FIST;
					else
						std::cout << "[Warning - Items::loadFromXml] Unknown weaponType " << strValue << std::endl;
				}
			}
			else if(tmpStrValue == "slottype")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
				{
					tmpStrValue = asLowerCaseString(strValue);
					if(tmpStrValue == "head")
					{
						it.slotPosition |= SLOTP_HEAD;
						it.wieldPosition = SLOT_HEAD;
					}
					else if(tmpStrValue == "body")
					{
						it.slotPosition |= SLOTP_ARMOR;
						it.wieldPosition = SLOT_ARMOR;
					}
					else if(tmpStrValue == "legs")
					{
						it.slotPosition |= SLOTP_LEGS;
						it.wieldPosition = SLOT_LEGS;
					}
					else if(tmpStrValue == "feet")
					{
						it.slotPosition |= SLOTP_FEET;
						it.wieldPosition = SLOT_FEET;
					}
					else if(tmpStrValue == "backpack")
					{
						it.slotPosition |= SLOTP_BACKPACK;
						it.wieldPosition = SLOT_BACKPACK;
					}
					else if(tmpStrValue == "two-handed")
					{
						it.slotPosition |= SLOTP_TWO_HAND;
						it.wieldPosition = SLOT_TWO_HAND;
					}
					else if(tmpStrValue == "necklace")
					{
						it.slotPosition |= SLOTP_NECKLACE;
						it.wieldPosition = SLOT_NECKLACE;
					}
					else if(tmpStrValue == "ring")
					{
						it.slotPosition |= SLOTP_RING;
						it.wieldPosition = SLOT_RING;
					}
					else if(tmpStrValue == "ammo")
						it.wieldPosition = SLOT_AMMO;
					else if(tmpStrValue == "hand")
						it.wieldPosition = SLOT_HAND;
					else
						std::cout << "[Warning - Items::loadFromXml] Unknown slotType " << strValue << std::endl;
				}
			}
			else if(tmpStrValue == "ammotype")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
				{
					it.ammoType = getAmmoType(strValue);
					if(it.ammoType == AMMO_NONE)
						std::cout << "[Warning - Items::loadFromXml] Unknown ammoType " << strValue << std::endl;
				}
			}
			else if(tmpStrValue == "shoottype")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
				{
					ShootType_t shoot = getShootType(strValue);
					if(shoot != NM_SHOOT_UNK)
						it.shootType = shoot;
					else
						std::cout << "[Warning - Items::loadFromXml] Unknown shootType " << strValue << std::endl;
				}
			}
			else if(tmpStrValue == "effect")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
				{
					MagicEffectClasses effect = getMagicEffect(strValue);
					if(effect != NM_ME_UNK)
						it.magicEffect = effect;
					else
						std::cout << "[Warning - Items::loadFromXml] Unknown effect " << strValue << std::endl;
				}
			}
			else if(tmpStrValue == "range")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.shootRange = intValue;
			}
			else if(tmpStrValue == "stopduration")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.stopTime = (intValue != 0);
			}
			else if(tmpStrValue == "decayto")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.decayTo = intValue;
			}
			else if(tmpStrValue == "transformequipto")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.transformEquipTo = intValue;
			}
			else if(tmpStrValue == "transformdeequipto")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.transformDeEquipTo = intValue;
			}
			else if(tmpStrValue == "duration")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.decayTime = std::max((int32_t)0, intValue);
			}
			else if(tmpStrValue == "showduration")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.showDuration = (intValue != 0);
			}
			else if(tmpStrValue == "charges")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.charges = intValue;
			}
			else if(tmpStrValue == "showcharges")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.showCharges = (intValue != 0);
			}
			else if(tmpStrValue == "showattributes")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.showAttributes = (intValue != 0);
			}
			else if(tmpStrValue == "breakchance")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.breakChance = std::max(0, std::min(100, intValue));
			}
			else if(tmpStrValue == "ammoaction")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
				{
					AmmoAction_t ammo = getAmmoAction(strValue);
					if(ammo != AMMOACTION_NONE)
						it.ammoAction = ammo;
					else
						std::cout << "[Warning - Items::loadFromXml] Unknown ammoAction " << strValue << std::endl;
				}
			}
			else if(tmpStrValue == "hitchance")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.hitChance = std::max(0, std::min(100, intValue));
			}
			else if(tmpStrValue == "maxhitchance")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.maxHitChance = std::max(0, std::min(100, intValue));
			}
			else if(tmpStrValue == "preventloss")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.preventLoss = (intValue != 0);
			}
			else if(tmpStrValue == "preventdrop")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.preventDrop = (intValue != 0);
			}
			else if(tmpStrValue == "invisible")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.invisible = (intValue != 0);
			}
			else if(tmpStrValue == "speed")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.speed = intValue;
			}
			else if(tmpStrValue == "healthgain")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.regeneration = true;
					it.abilities.healthGain = intValue;
				}
			}
			else if(tmpStrValue == "healthticks")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.regeneration = true;
					it.abilities.healthTicks = intValue;
				}
			}
			else if(tmpStrValue == "managain")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.regeneration = true;
					it.abilities.manaGain = intValue;
				}
			}
			else if(tmpStrValue == "manaticks")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.regeneration = true;
					it.abilities.manaTicks = intValue;
				}
			}
			else if(tmpStrValue == "manashield")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.manaShield = (intValue != 0);
			}
			else if(tmpStrValue == "skillsword")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.skills[SKILL_SWORD] = intValue;
			}
			else if(tmpStrValue == "skillaxe")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.skills[SKILL_AXE] = intValue;
			}
			else if(tmpStrValue == "skillclub")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.skills[SKILL_CLUB] = intValue;
			}
			else if(tmpStrValue == "skilldist")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.skills[SKILL_DIST] = intValue;
			}
			else if(tmpStrValue == "skillfish")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.skills[SKILL_FISH] = intValue;
			}
			else if(tmpStrValue == "skillshield")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.skills[SKILL_SHIELD] = intValue;
			}
			else if(tmpStrValue == "skillfist")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.skills[SKILL_FIST] = intValue;
			}
			else if(tmpStrValue == "maxhealthpoints" || tmpStrValue == "maxhitpoints")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.stats[STAT_MAXHEALTH] = intValue;
			}
			else if(tmpStrValue == "maxhealthpercent" || tmpStrValue == "maxhitpointspercent")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.statsPercent[STAT_MAXHEALTH] = intValue;
			}
			else if(tmpStrValue == "maxmanapoints")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.stats[STAT_MAXMANA] = intValue;
			}
			else if(tmpStrValue == "maxmanapercent" || tmpStrValue == "maxmanapointspercent")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.statsPercent[STAT_MAXMANA] = intValue;
			}
			else if(tmpStrValue == "soulpoints")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.stats[STAT_SOUL] = intValue;
			}
			else if(tmpStrValue == "soulpercent" || tmpStrValue == "soulpointspercent")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.statsPercent[STAT_SOUL] = intValue;
			}
			else if(tmpStrValue == "magiclevelpoints" || tmpStrValue == "magicpoints")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.stats[STAT_MAGICLEVEL] = intValue;
			}
			else if(tmpStrValue == "magiclevelpercent" || tmpStrValue == "magicpointspercent")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.statsPercent[STAT_MAGICLEVEL] = intValue;
			}
			else if(tmpStrValue == "absorbpercentall")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					for(uint32_t i = COMBAT_FIRST; i <= COMBAT_LAST; i++)
						it.abilities.absorbPercent[i] += intValue;
				}
			}
			else if(tmpStrValue == "absorbpercentelements")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.absorbPercent[COMBAT_ENERGYDAMAGE] += intValue;
					it.abilities.absorbPercent[COMBAT_FIREDAMAGE] += intValue;
					it.abilities.absorbPercent[COMBAT_EARTHDAMAGE] += intValue;
					it.abilities.absorbPercent[COMBAT_ICEDAMAGE] += intValue;
				}
			}
			else if(tmpStrValue == "absorbpercentmagic")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.absorbPercent[COMBAT_ENERGYDAMAGE] += intValue;
					it.abilities.absorbPercent[COMBAT_FIREDAMAGE] += intValue;
					it.abilities.absorbPercent[COMBAT_EARTHDAMAGE] += intValue;
					it.abilities.absorbPercent[COMBAT_ICEDAMAGE] += intValue;
					it.abilities.absorbPercent[COMBAT_HOLYDAMAGE] += intValue;
					it.abilities.absorbPercent[COMBAT_DEATHDAMAGE] += intValue;
				}
			}
			else if(tmpStrValue == "absorbpercentenergy")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.absorbPercent[COMBAT_ENERGYDAMAGE] += intValue;
			}
			else if(tmpStrValue == "absorbpercentfire")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.absorbPercent[COMBAT_FIREDAMAGE] += intValue;
			}
			else if(tmpStrValue == "absorbpercentpoison" ||	tmpStrValue == "absorbpercentearth")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.absorbPercent[COMBAT_EARTHDAMAGE] += intValue;
			}
			else if(tmpStrValue == "absorbpercentice")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.absorbPercent[COMBAT_ICEDAMAGE] += intValue;
			}
			else if(tmpStrValue == "absorbpercentholy")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.absorbPercent[COMBAT_HOLYDAMAGE] += intValue;
			}
			else if(tmpStrValue == "absorbpercentdeath")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.absorbPercent[COMBAT_DEATHDAMAGE] += intValue;
			}
			else if(tmpStrValue == "absorbpercentlifedrain")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.absorbPercent[COMBAT_LIFEDRAIN] += intValue;
			}
			else if(tmpStrValue == "absorbpercentmanadrain")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.absorbPercent[COMBAT_MANADRAIN] += intValue;
			}
			else if(tmpStrValue == "absorbpercentdrown")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.absorbPercent[COMBAT_DROWNDAMAGE] += intValue;
			}
			else if(tmpStrValue == "absorbpercentphysical")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.absorbPercent[COMBAT_PHYSICALDAMAGE] += intValue;
			}
			else if(tmpStrValue == "absorbpercenthealing")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.absorbPercent[COMBAT_HEALING] += intValue;
			}
			else if(tmpStrValue == "absorbpercentundefined")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.abilities.absorbPercent[COMBAT_UNDEFINEDDAMAGE] += intValue;
			}
			else if(tmpStrValue == "suppressshock" || tmpStrValue == "suppressenergy")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_ENERGY;
			}
			else if(tmpStrValue == "suppressburn" || tmpStrValue == "suppressfire")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_FIRE;
			}
			else if(tmpStrValue == "suppresspoison" || tmpStrValue == "suppressearth")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_POISON;
			}
			else if(tmpStrValue == "suppressfreeze" || tmpStrValue == "suppressice")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_FREEZING;
			}
			else if(tmpStrValue == "suppressdazzle" || tmpStrValue == "suppressholy")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_DAZZLED;
			}
			else if(tmpStrValue == "suppresscurse" || tmpStrValue == "suppressdeath")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_CURSED;
			}
			else if(tmpStrValue == "suppressdrown")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_DROWN;
			}
			else if(tmpStrValue == "suppressphysical")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_PHYSICAL;
			}
			else if(tmpStrValue == "suppresshaste")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_HASTE;
			}
			else if(tmpStrValue == "suppressparalyze")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_PARALYZE;
			}
			else if(tmpStrValue == "suppressdrunk")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_DRUNK;
			}
			else if(tmpStrValue == "suppressregeneration")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_REGENERATION;
			}
			else if(tmpStrValue == "suppresssoul")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_SOUL;
			}
			else if(tmpStrValue == "suppressoutfit")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_OUTFIT;
			}
			else if(tmpStrValue == "suppressinvisible")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_INVISIBLE;
			}
			else if(tmpStrValue == "suppressinfight")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_INFIGHT;
			}
			else if(tmpStrValue == "suppressexhaust")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_EXHAUST;
			}
			else if(tmpStrValue == "suppressmuted")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_MUTED;
			}
			else if(tmpStrValue == "suppresspacified")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_PACIFIED;
			}
			else if(tmpStrValue == "suppresslight")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_LIGHT;
			}
			else if(tmpStrValue == "suppressattributes")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_ATTRIBUTES;
			}
			else if(tmpStrValue == "suppressmanashield")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue) && intValue != 0)
					it.abilities.conditionSuppressions |= CONDITION_MANASHIELD;
			}
			else if(tmpStrValue == "field")
			{
				it.group = ITEM_GROUP_MAGICFIELD;
				it.type = ITEM_TYPE_MAGICFIELD;
				CombatType_t combatType = COMBAT_NONE;
				ConditionDamage* conditionDamage = NULL;

				if(readXMLString(itemAttributesNode, "value", strValue))
				{
					tmpStrValue = asLowerCaseString(strValue);
					if(tmpStrValue == "fire")
					{
						conditionDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_FIRE, false, 0);
						combatType = COMBAT_FIREDAMAGE;
					}
					else if(tmpStrValue == "energy")
					{
						conditionDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_ENERGY, false, 0);
						combatType = COMBAT_ENERGYDAMAGE;
					}
					else if(tmpStrValue == "earth" || tmpStrValue == "poison")
					{
						conditionDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_POISON, false, 0);
						combatType = COMBAT_EARTHDAMAGE;
					}
					else if(tmpStrValue == "ice" || tmpStrValue == "freezing")
					{
						conditionDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_FREEZING, false, 0);
						combatType = COMBAT_ICEDAMAGE;
					}
					else if(tmpStrValue == "holy" || tmpStrValue == "dazzled")
					{
						conditionDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_DAZZLED, false, 0);
						combatType = COMBAT_HOLYDAMAGE;
					}
					else if(tmpStrValue == "death" || tmpStrValue == "cursed")
					{
						conditionDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_CURSED, false, 0);
						combatType = COMBAT_DEATHDAMAGE;
					}
					else if(tmpStrValue == "drown")
					{
						conditionDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_DROWN, false, 0);
						combatType = COMBAT_DROWNDAMAGE;
					}
					else if(tmpStrValue == "physical")
					{
						conditionDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_PHYSICAL, false, 0);
						combatType = COMBAT_PHYSICALDAMAGE;
					}
					else
						std::cout << "[Warning - Items::loadFromXml] Unknown field value " << strValue << std::endl;

					if(combatType != COMBAT_NONE)
					{
						it.combatType = combatType;
						it.condition = conditionDamage;
						uint32_t ticks = 0;
						int32_t damage = 0, start = 0, count = 1;

						xmlNodePtr fieldAttributesNode = itemAttributesNode->children;
						while(fieldAttributesNode)
						{
							if(readXMLString(fieldAttributesNode, "key", strValue))
							{
								tmpStrValue = asLowerCaseString(strValue);
								if(tmpStrValue == "ticks")
								{
									if(readXMLInteger(fieldAttributesNode, "value", intValue))
										ticks = std::max(0, intValue);
								}

								if(tmpStrValue == "count")
								{
									if(readXMLInteger(fieldAttributesNode, "value", intValue))
										count = std::max(1, intValue);
								}

								if(tmpStrValue == "start")
								{
									if(readXMLInteger(fieldAttributesNode, "value", intValue))
										start = std::max(0, intValue);
								}

								if(tmpStrValue == "damage")
								{
									if(readXMLInteger(fieldAttributesNode, "value", intValue))
									{
										damage = -intValue;
										if(start > 0)
										{
											std::list<int32_t> damageList;
											ConditionDamage::generateDamageList(damage, start, damageList);

											for(std::list<int32_t>::iterator it = damageList.begin(); it != damageList.end(); ++it)
												conditionDamage->addDamage(1, ticks, -*it);

											start = 0;
										}
										else
											conditionDamage->addDamage(count, ticks, damage);
									}
								}
							}

							fieldAttributesNode = fieldAttributesNode->next;
						}

						if(conditionDamage->getTotalDamage() > 0)
							it.condition->setParam(CONDITIONPARAM_FORCEUPDATE, true);
					}
				}
			}
			else if(tmpStrValue == "elementphysical")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.elementDamage = intValue;
					it.abilities.elementType = COMBAT_PHYSICALDAMAGE;
				}
			}
			else if(tmpStrValue == "elementfire")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.elementDamage = intValue;
					it.abilities.elementType = COMBAT_FIREDAMAGE;
				}
			}
			else if(tmpStrValue == "elementenergy")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.elementDamage = intValue;
					it.abilities.elementType = COMBAT_ENERGYDAMAGE;
				}
			}
			else if(tmpStrValue == "elementearth")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.elementDamage = intValue;
					it.abilities.elementType = COMBAT_EARTHDAMAGE;
				}
			}
			else if(tmpStrValue == "elementice")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.elementDamage = intValue;
					it.abilities.elementType = COMBAT_ICEDAMAGE;
				}
			}
			else if(tmpStrValue == "elementholy")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.elementDamage = intValue;
					it.abilities.elementType = COMBAT_HOLYDAMAGE;
				}
			}
			else if(tmpStrValue == "elementdeath")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.elementDamage = intValue;
					it.abilities.elementType = COMBAT_DEATHDAMAGE;
				}
			}
			else if(tmpStrValue == "elementlifedrain")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.elementDamage = intValue;
					it.abilities.elementType = COMBAT_LIFEDRAIN;
				}
			}
			else if(tmpStrValue == "elementmanadrain")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.elementDamage = intValue;
					it.abilities.elementType = COMBAT_MANADRAIN;
				}
			}
			else if(tmpStrValue == "elementhealing")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.elementDamage = intValue;
					it.abilities.elementType = COMBAT_HEALING;
				}
			}
			else if(tmpStrValue == "elementundefined")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.abilities.elementDamage = intValue;
					it.abilities.elementType = COMBAT_UNDEFINEDDAMAGE;
				}
			}
			else if(tmpStrValue == "replaceable" || tmpStrValue == "replacable")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.replaceable = (intValue != 0);
			}
			else if(tmpStrValue == "partnerdirection")
			{
				if(readXMLString(itemAttributesNode, "value", strValue))
					it.bedPartnerDir = getDirection(strValue);
			}
			else if(tmpStrValue == "maletransformto")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.transformToOnUse[PLAYERSEX_MALE] = intValue;
					ItemType& ot = getItemType(intValue);
					if(ot.transformToFree == 0)
						ot.transformToFree = it.id;

					if(it.transformToOnUse[PLAYERSEX_FEMALE] == 0)
						it.transformToOnUse[PLAYERSEX_FEMALE] = intValue;
				}
			}
			else if(tmpStrValue == "femaletransformto")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
				{
					it.transformToOnUse[PLAYERSEX_FEMALE] = intValue;
					ItemType& ot = getItemType(intValue);
					if(ot.transformToFree == 0)
						ot.transformToFree = it.id;

					if(it.transformToOnUse[PLAYERSEX_MALE] == 0)
						it.transformToOnUse[PLAYERSEX_MALE] = intValue;
				}
			}
			else if(tmpStrValue == "transformto")
			{
				if(readXMLInteger(itemAttributesNode, "value", intValue))
					it.transformToFree = intValue;
			}
			else
				std::cout << "[Warning - Items::loadFromXml] Unknown key value " << strValue << std::endl;
		}

		itemAttributesNode = itemAttributesNode->next;
	}

	if(it.pluralName.empty() && !it.name.empty())
	{
		it.pluralName = it.name;
		if(it.showCount)
			it.pluralName += "s";
	}
}

void Items::parseRandomizationBlock(int32_t id, int32_t fromId, int32_t toId, int32_t chance)
{
	RandomizationMap::iterator it = randomizationMap.find(id);
	if(it != randomizationMap.end())
	{
		std::cout << "[Warning - Items::parseRandomizationBlock] Duplicated item with id: " << id << std::endl;
		return;
	}

	RandomizationBlock rand;
	rand.chance = chance;
	rand.fromRange = fromId;
	rand.toRange = toId;

	randomizationMap[id] = rand;
}

uint16_t Items::getRandomizedItem(uint16_t id)
{
	if(!g_config.getBool(ConfigManager::RANDOMIZE_TILES))
		return id;

	RandomizationBlock randomize = getRandomization(id);
	if(randomize.chance > 0 && random_range(0, 100) <= randomize.chance)
		id = random_range(randomize.fromRange, randomize.toRange);

	return id;
}

ItemType& Items::getItemType(int32_t id)
{
	ItemType* iType = items.getElement(id);
	if(iType)
		return *iType;

	#ifdef __DEBUG__
	std::cout << "[Warning - Items::getItemType] Unknown itemtype with id " << id << ", using defaults." << std::endl;
	#endif
	static ItemType dummyItemType; // use this for invalid ids
	return dummyItemType;
}

const ItemType& Items::getItemType(int32_t id) const
{
	if(ItemType* iType = items.getElement(id))
		return *iType;

	static ItemType dummyItemType; // use this for invalid ids
	return dummyItemType;
}

const ItemType& Items::getItemIdByClientId(int32_t spriteId) const
{
	uint32_t i = 100;
	ItemType* iType;
	do
	{
		if((iType = items.getElement(i)) && iType->clientId == spriteId)
			return *iType;

		i++;
	}
	while(iType);

	static ItemType dummyItemType; // use this for invalid ids
	return dummyItemType;
}

int32_t Items::getItemIdByName(const std::string& name)
{
	if(!name.empty())
	{
		uint32_t i = 100;
		ItemType* iType = NULL;
		do
		{
			if((iType = items.getElement(i)) && !strcasecmp(name.c_str(), iType->name.c_str()))
				return i;

			i++;
		}
		while(iType);
	}

	return -1;
}
