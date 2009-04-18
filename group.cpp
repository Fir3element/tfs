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
#include "group.h"

#include "tools.h"
#include <iostream>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

Group Groups::defGroup = Group();

void Groups::clear()
{
	for(GroupsMap::iterator it = groupsMap.begin(); it != groupsMap.end(); ++it)
		delete it->second;

	groupsMap.clear();
}

bool Groups::reload()
{
	clear();
	return loadFromXml();
}

bool Groups::loadFromXml()
{
	xmlDocPtr doc = xmlParseFile(getFilePath(FILE_TYPE_XML, "groups.xml").c_str());
	if(!doc)
	{
		std::cout << "[Warning - Groups::loadFromXml] Cannot load groups file." << std::endl;
		std::cout << getLastXMLError() << std::endl;
		return false;
	}

	xmlNodePtr p, root = xmlDocGetRootElement(doc);
	if(xmlStrcmp(root->name,(const xmlChar*)"groups"))
	{
		std::cout << "[Error - Groups::loadFromXml] Malformed groups file." << std::endl;
		xmlFreeDoc(doc);
		return false;
	}

	std::string strValue;
	int32_t intValue;
	int64_t int64Value;

	p = root->children;
	while(p)
	{
		if(xmlStrcmp(p->name, (const xmlChar*)"group"))
		{
			p = p->next;
			continue;
		}

		if(!readXMLInteger(p, "id", intValue))
		{
			std::cout << "Missing group id." << std::endl;
			p = p->next;
			continue;
		}

		Group* group = new Group(intValue);
		if(readXMLString(p, "name", strValue))
		{
			group->setFullName(strValue);
			group->setName(asLowerCaseString(strValue));
		}

		if(readXMLInteger64(p, "flags", int64Value))
			group->setFlags(int64Value);

		if(readXMLInteger64(p, "customFlags", int64Value))
			group->setCustomFlags(int64Value);

		if(readXMLInteger(p, "access", intValue))
			group->setAccess(intValue);

		if(readXMLInteger(p, "violationAccess", intValue))
			group->setViolationAccess(intValue);

		if(readXMLInteger(p, "depotLimit", intValue))
			group->setDepotLimit(intValue);

		if(readXMLInteger(p, "maxVips", intValue))
			group->setMaxVips(intValue);

		if(readXMLInteger(p, "outfit", intValue))
			group->setOutfit(intValue);

		groupsMap[group->getId()] = group;
		p = p->next;
	}

	xmlFreeDoc(doc);
	return true;
}

Group* Groups::getGroup(uint32_t groupId)
{
	GroupsMap::iterator it = groupsMap.find(groupId);
	if(it != groupsMap.end())
		return it->second;

	std::cout << "[Warning - Groups::getGroup] Group " << groupId << " not found." << std::endl;
	return NULL;
}

int32_t Groups::getGroupId(const std::string& name)
{
	for(GroupsMap::iterator it = groupsMap.begin(); it != groupsMap.end(); ++it)
	{
		if(!strcasecmp(it->second->getName().c_str(), name.c_str()))
			return it->first;
	}

	return -1;
}

uint32_t Group::getDepotLimit(bool premium) const
{
	if(m_depotLimit > 0)
		return m_depotLimit;

	return (premium ? 2000 : 1000);
}

uint32_t Group::getMaxVips(bool premium) const
{
	if(m_maxVips > 0)
		return m_maxVips;

	return (premium ? 100 : 20);
}
