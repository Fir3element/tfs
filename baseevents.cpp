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
#include <libxml/xmlmemory.h>

#include "baseevents.h"
#include "tools.h"

bool BaseEvents::loadFromXml()
{
	std::string scriptsName = getScriptBaseName();
	if(m_loaded)
	{
		std::cout << "[Error - BaseEvents::loadFromXml] " << scriptsName << " interface already loaded!" << std::endl;
		return false;
	}

	if(getInterface().loadFile(getFilePath(FILE_TYPE_OTHER, std::string(scriptsName + "/lib/" + scriptsName + ".lua"))) == -1)
		std::cout << "[Warning - BaseEvents::loadFromXml] Cannot load " << scriptsName << "/lib/" << scriptsName << ".lua" << std::endl;

	xmlDocPtr doc = xmlParseFile(getFilePath(FILE_TYPE_OTHER, std::string(scriptsName + "/" + scriptsName + ".xml")).c_str());
	if(!doc)
	{
		std::cout << "[Warning - BaseEvents::loadFromXml] Cannot open " << scriptsName << ".xml file." << std::endl;
		std::cout << getLastXMLError() << std::endl;
		return false;
	}

	xmlNodePtr p, root = xmlDocGetRootElement(doc);
	if(xmlStrcmp(root->name,(const xmlChar*)scriptsName.c_str()))
	{
		std::cout << "[Error - BaseEvents::loadFromXml] Malformed " << scriptsName << ".xml file." << std::endl;
		xmlFreeDoc(doc);
		return false;
	}

	std::string scriptsPath = getFilePath(FILE_TYPE_OTHER, std::string(scriptsName + "/scripts/"));
	p = root->children;
	while(p)
	{
		parseEventNode(p, scriptsPath, false);
		p = p->next;
	}

	xmlFreeDoc(doc);
	m_loaded = true;
	return m_loaded;
}

bool BaseEvents::parseEventNode(xmlNodePtr p, std::string scriptsPath, bool override)
{
	Event* event = getEvent((const char*)p->name);
	if(!event)
		return false;

	if(!event->configureEvent(p))
	{
		std::cout << "[Warning - BaseEvents::loadFromXml] Cannot configure an event" << std::endl;
		delete event;
		event = NULL;
		return false;
	}

	bool success = false;
	std::string strValue, tmpStrValue;
	if(readXMLString(p, "event", strValue))
	{
		tmpStrValue = asLowerCaseString(strValue);
		if(tmpStrValue == "script")
		{
			bool file = readXMLString(p, "value", strValue);
			if(!file)
				parseXMLContentString(p->children, strValue);
			else
				strValue = scriptsPath + strValue;

			success = event->checkScript(strValue, file) && event->loadScript(strValue, file);
		}
		else if(tmpStrValue == "buffer")
		{
			if(!readXMLString(p, "value", strValue))
				parseXMLContentString(p->children, strValue);

			success = event->checkBuffer(strValue) && event->loadBuffer(strValue);
		}
		else if(tmpStrValue == "function")
		{
			if(readXMLString(p, "value", strValue))
				success = event->loadFunction(strValue);
		}
	}
	else if(readXMLString(p, "script", strValue))
	{
		bool file = asLowerCaseString(strValue) != "cdata";
		if(!file)
			parseXMLContentString(p->children, strValue);
		else
			strValue = scriptsPath + strValue;

		success = event->checkScript(strValue, file) && event->loadScript(strValue, file);
	}
	else if(readXMLString(p, "buffer", strValue))
	{
		if(asLowerCaseString(strValue) == "cdata")
			parseXMLContentString(p->children, strValue);

		success = event->checkBuffer(strValue) && event->loadBuffer(strValue);
	}
	else if(readXMLString(p, "function", strValue))
		success = event->loadFunction(strValue);
	else if(parseXMLContentString(p->children, strValue) && event->checkBuffer(strValue))
		success = event->loadBuffer(strValue);

	if(!override && readXMLString(p, "override", strValue) && booleanString(strValue))
		override = true;

	if(success && !registerEvent(event, p, override) && event)
	{
		delete event;
		event = NULL;
	}

	return success;
}

bool BaseEvents::reload()
{
	m_loaded = false;
	clear();
	return loadFromXml();
}

Event::Event(const Event* copy)
{
	m_scriptInterface = copy->m_scriptInterface;
	m_scripted = copy->m_scripted;
	m_scriptId = copy->m_scriptId;
	m_scriptData = copy->m_scriptData;
}

bool Event::loadBuffer(const std::string& buffer)
{
	if(!m_scriptInterface || m_scriptData != "")
	{
		std::cout << "[Error - Event::loadScriptFile] m_scriptInterface == NULL, scriptData != \"\"" << std::endl;
		return false;
	}

	m_scripted = EVENT_SCRIPT_BUFFER;
	m_scriptData = buffer;
	return true;
}

bool Event::checkBuffer(const std::string& buffer)
{
	return true; //TODO
}

bool Event::loadScript(const std::string& script, bool file)
{
	if(!m_scriptInterface || m_scriptId != 0)
	{
		std::cout << "[Error - Event::loadScript] m_scriptInterface == NULL, scriptId = " << m_scriptId << std::endl;
		return false;
	}

	int32_t result = -1;
	if(!file)
	{
		std::string script_ = script, tmp = "function " + getScriptEventName();
		trimString(script_);
		if(script_.find(tmp) == std::string::npos)
		{
			std::stringstream scriptstream;
			scriptstream << tmp << "(" << getScriptEventParams() << ")" << std::endl << script_ << std::endl << "end";
			script_ = scriptstream.str();
		}

		result = m_scriptInterface->loadBuffer(script_);
	}
	else
		result = m_scriptInterface->loadFile(script);

	if(result == -1)
	{
		std::cout << "[Warning - Event::loadScript] Cannot load script (" << script << ")" << std::endl;
		std::cout << m_scriptInterface->getLastError() << std::endl;
		return false;
	}

	int32_t id = m_scriptInterface->getEvent(getScriptEventName());
	if(id == -1)
	{
		std::cout << "[Warning - Event::loadScript] Event " << getScriptEventName() << " not found (" << script << ")" << std::endl;
		return false;
	}

	m_scripted = EVENT_SCRIPT_TRUE;
	m_scriptId = id;
	return true;
}

bool Event::checkScript(const std::string& script, bool file)
{
	return true; //TODO
}

CallBack::CallBack()
{
	m_scriptId = 0;
	m_scriptInterface = NULL;
	m_loaded = false;
}

bool CallBack::loadCallBack(LuaScriptInterface* _interface, std::string name)
{
	if(!_interface)
	{
		std::cout << "Failure: [CallBack::loadCallBack] m_scriptInterface == NULL" << std::endl;
		return false;
	}

	m_scriptInterface = _interface;
	int32_t id = m_scriptInterface->getEvent(name);
	if(id == -1)
	{
		std::cout << "Warning: [CallBack::loadCallBack] Event " << name << " not found." << std::endl;
		return false;
	}

	m_callbackName = name;
	m_scriptId = id;
	m_loaded = true;
	return true;
}
