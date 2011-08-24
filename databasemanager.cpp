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
#include "enums.h"
#include <iostream>

#include "databasemanager.h"
#include "tools.h"

#include "ban.h"

#include "configmanager.h"
extern ConfigManager g_config;

bool DatabaseManager::optimizeTables()
{
	Database* db = Database::getInstance();
	DBQuery query;

	switch(db->getDatabaseEngine())
	{
		case DATABASE_ENGINE_MYSQL:
		{
			query << "SELECT `TABLE_NAME` FROM `information_schema`.`TABLES` WHERE `TABLE_SCHEMA` = " << db->escapeString(g_config.getString(ConfigManager::MYSQL_DB)) << " AND `DATA_FREE` > 0;";
			DBResult* result = db->storeQuery(query.str());
			if(!result)
				return false;

			do
			{
				std::string tableName = result->getDataString("TABLE_NAME");
				std::cout << "> Optimizing table " << tableName << "..." << std::flush;

				query.str("");
				query << "OPTIMIZE TABLE `" << tableName << "`;";
				if(db->executeQuery(query.str()))
					std::cout << " [success]" << std::endl;
				else
					std::cout << " [failed]" << std::endl;
			}
			while(result->next());
			db->freeResult(result);
			break;
		}

		case DATABASE_ENGINE_SQLITE:
		{
			if(!db->executeQuery("VACUUM;"))
				return false;

			std::cout << "> Optimized database." << std::endl;
			break;
		}

		default:
		{
			std::cout << "> Optimization is not supported for this database engine." << std::endl;
			break;
		}
	}
	return true;
}

bool DatabaseManager::triggerExists(std::string triggerName)
{
	Database* db = Database::getInstance();
	DBQuery query;

	switch(db->getDatabaseEngine())
	{
		case DATABASE_ENGINE_MYSQL:
			query << "SELECT `name` FROM `sqlite_master` WHERE `type` = 'trigger' AND `name` = " << db->escapeString(triggerName) << ";";
			break;

		case DATABASE_ENGINE_SQLITE:
			query << "SELECT `TRIGGER_NAME` FROM `information_schema`.`TRIGGERS` WHERE `TRIGGER_SCHEMA` = " << db->escapeString(g_config.getString(ConfigManager::SQLITE_DB)) << " AND `TRIGGER_NAME` = " << db->escapeString(triggerName) << ";";
			break;

		default:
			return false;
	}

	DBResult* result = db->storeQuery(query.str());
	if(!result)
		return false;

	db->freeResult(result);
	return true;
}

bool DatabaseManager::tableExists(std::string tableName)
{
	Database* db = Database::getInstance();
	DBQuery query;
	switch(db->getDatabaseEngine())
	{
		case DATABASE_ENGINE_MYSQL:
			query << "SELECT `TABLE_NAME` FROM `information_schema`.`tables` WHERE `TABLE_SCHEMA` = " << db->escapeString(g_config.getString(ConfigManager::MYSQL_DB)) << " AND `TABLE_NAME` = " << db->escapeString(tableName) << ";";
			break;

		case DATABASE_ENGINE_SQLITE:
			query << "SELECT `name` FROM `sqlite_master` WHERE `type` = 'table' AND `name` = " << db->escapeString(tableName) << ";";
			break;

		default:
			return false;
	}

	DBResult* result = db->storeQuery(query.str());
	if(!result)
		return false;

	db->freeResult(result);
	return true;
}

bool DatabaseManager::isDatabaseSetup()
{
	Database* db = Database::getInstance();
	DBQuery query;
	switch(db->getDatabaseEngine())
	{
		case DATABASE_ENGINE_MYSQL:
		{
			query << "SELECT `TABLE_NAME` FROM `information_schema`.`tables` WHERE `TABLE_SCHEMA` = " << db->escapeString(g_config.getString(ConfigManager::MYSQL_DB)) << ";";
			break;
		}

		case DATABASE_ENGINE_SQLITE:
		{
			query.str("SELECT `name` FROM `sqlite_master` WHERE `type` = 'table';");
			break;
		}

		default:
			return false;
	}

	DBResult* result = db->storeQuery(query.str());
	if(!result)
		return false;

	db->freeResult(result);
	return true;
}

uint32_t DatabaseManager::getDatabaseVersion()
{
	if(!tableExists("server_config"))
		return 0;

	int32_t version = 0;
	getDatabaseConfig("db_version", version);
	return version;
}

uint32_t DatabaseManager::updateDatabase()
{
	/*
	Database* db = Database::getInstance();
	DBQuery query;

	switch(getDatabaseVersion())
	{
		case 0:
		{
			std::cout << "> Updating database to version 1" << std::endl;
			if(db->getDatabaseEngine() == DATABASE_ENGINE_MYSQL)
			{
				db->executeQuery("CREATE TABLE IF NOT EXISTS `server_config` (`config` VARCHAR(50) NOT NULL, `value` VARCHAR(256) NOT NULL DEFAULT '', UNIQUE(`config`)) ENGINE = InnoDB;");
				db->executeQuery("CREATE TABLE IF NOT EXISTS `bans2` (`id` INT UNSIGNED NOT NULL AUTO_INCREMENT, `type` TINYINT(1) NOT NULL COMMENT 'this field defines if its ip, account, player, or any else ban', `value` INT UNSIGNED NOT NULL COMMENT 'ip, player guid, account number', `param` INT UNSIGNED NOT NULL DEFAULT 4294967295 COMMENT 'mask', `active` TINYINT(1) NOT NULL DEFAULT 1, `expires` INT UNSIGNED NOT NULL DEFAULT 0, `added` INT UNSIGNED NOT NULL, `admin_id` INT UNSIGNED NOT NULL DEFAULT 0, `comment` VARCHAR(1024) NOT NULL DEFAULT '', `reason` INT UNSIGNED NOT NULL DEFAULT 0, `action` INT UNSIGNED NOT NULL DEFAULT 0, `statement` VARCHAR(256) NOT NULL DEFAULT '', PRIMARY KEY (`id`), INDEX `type` (`type`, `value`), INDEX `active` (`active`)) ENGINE = InnoDB;");
			}
			else
			{
				db->executeQuery("CREATE TABLE IF NOT EXISTS `server_config` (`config` VARCHAR(50) NOT NULL, `value` VARCHAR(256) NOT NULL DEFAULT '', UNIQUE(`config`));");
				db->executeQuery("CREATE TABLE IF NOT EXISTS `bans2` (`id` INTEGER NOT NULL, `type` UNSIGNED INTEGER NOT NULL, `value` UNSIGNED INTEGER NOT NULL, `param` UNSIGNED INTEGER NOT NULL DEFAULT 4294967295, `active` UNSIGNED INTEGER NOT NULL DEFAULT 1, `expires` UNSIGNED INTEGER NOT NULL DEFAULT 0, `added` UNSIGNED INTEGER NOT NULL, `admin_id` UNSIGNED INTEGER NOT NULL DEFAULT 0, `comment` VARCHAR(1024) NOT NULL DEFAULT '', `reason` UNSIGNED INTEGER NOT NULL DEFAULT 0, `action` UNSIGNED INTEGER NOT NULL DEFAULT 0, `statement` VARCHAR(256) NOT NULL DEFAULT '', PRIMARY KEY (`id`));");
				db->executeQuery("CREATE INDEX bans_index_type ON bans2(type, value);");
				db->executeQuery("CREATE INDEX bans_index_active ON bans2(active);");
			}

			DBResult* result = db->storeQuery("SELECT * FROM `bans`;");
			if(result)
			{
				do
				{
					switch(result->getDataInt("type"))
					{
						case BAN_IPADDRESS:
							query << "INSERT INTO `bans2` (`type`, `value`, `param`, `active`, `expires`, `added`, `admin_id`, `comment`, `reason`, `action`) VALUES (1, " << result->getDataInt("ip") << ", " << result->getDataInt("mask") << ", " << (result->getDataInt("time") <= time(NULL) ? 0 : 1) << ", " << result->getDataInt("time") << ", 0, " << result->getDataInt("banned_by") << ", " << db->escapeString(result->getDataString("comment")) << ", " << result->getDataInt("reason_id") << ", " << result->getDataInt("action_id") << ");";
							break;

						case NAMELOCK_PLAYER:
							query << "INSERT INTO `bans2` (`type`, `value`, `active`, `expires`, `added`, `admin_id`, `comment`, `reason`, `action`) VALUES (2, " << result->getDataInt("player") << ", " << (result->getDataInt("time") <= time(NULL) ? 0 : 1) << ", 0, " << result->getDataInt("time") << ", " << result->getDataInt("banned_by") << ", " << db->escapeString(result->getDataString("comment")) << ", " << result->getDataInt("reason_id") << ", " << result->getDataInt("action_id") << ");";
							break;

						case BAN_ACCOUNT:
							query << "INSERT INTO `bans2` (`type`, `value`, `active`, `expires`, `added`, `admin_id`, `comment`, `reason`, `action`) VALUES (3, " << result->getDataInt("player") << ", " << (result->getDataInt("time") <= time(NULL) ? 0 : 1) << ", " << result->getDataInt("time") << ", 0, " << result->getDataInt("banned_by") << ", " << db->escapeString(result->getDataString("comment")) << ", " << result->getDataInt("reason_id") << ", " << result->getDataInt("action_id") << ");";
							break;

						case NOTATION_ACCOUNT:
						case DELETE_ACCOUNT:
							query << "INSERT INTO `bans2` (`type`, `value`, `active`, `expires`, `added`, `admin_id`, `comment`, `reason`, `action`) VALUES (" << result->getDataInt("type") << ", " << result->getDataInt("player") << ", " << (result->getDataInt("time") <= time(NULL) ? 0 : 1) << ", 0, " << result->getDataInt("time") << ", " << result->getDataInt("banned_by") << ", " << db->escapeString(result->getDataString("comment")) << ", " << result->getDataInt("reason_id") << ", " << result->getDataInt("action_id") << ");";
							break;
					}
				}
				while(result->next());
				db->freeResult(result);
			}

			db->executeQuery("DROP TABLE `bans`;");
			if(db->getDatabaseEngine() == DATABASE_ENGINE_MYSQL)
				db->executeQuery("RENAME TABLE `bans2` TO `bans`;");
			else
				db->executeQuery("ALTER TABLE `bans2` RENAME TO `bans`;");

			db->executeQuery("INSERT INTO `server_config` VALUES ('db_version', 1);");
			break;
		}

		default: break;
	}
	*/
	return 0;
}

bool DatabaseManager::getDatabaseConfig(std::string config, int32_t &value)
{
	Database* db = Database::getInstance();
	DBQuery query;
	query << "SELECT `value` FROM `server_config` WHERE `config` = " << db->escapeString(config) << ";";
	DBResult* result = db->storeQuery(query.str());
	if(!result)
		return false;

	value = atoi(result->getDataString("value").c_str());
	db->freeResult(result);
	return true;
}

bool DatabaseManager::getDatabaseConfig(std::string config, std::string &value)
{
	Database* db = Database::getInstance();
	DBQuery query;
	query << "SELECT `value` FROM `server_config` WHERE `config` = " << db->escapeString(config) << ";";
	DBResult* result = db->storeQuery(query.str());
	if(!result)
		return false;

	value = result->getDataString("value");
	db->freeResult(result);
	return true;
}

void DatabaseManager::registerDatabaseConfig(std::string config, int32_t value)
{
	Database* db = Database::getInstance();
	DBQuery query;

	int32_t tmp;
	if(!getDatabaseConfig(config, tmp))
		query << "INSERT INTO `server_config` VALUES (" << db->escapeString(config) << ", '" << value << "');";
	else
		query << "UPDATE `server_config` SET `value` = '" << value << "' WHERE `config` = " << db->escapeString(config) << ";";

	db->executeQuery(query.str());
}

void DatabaseManager::registerDatabaseConfig(std::string config, std::string value)
{
	Database* db = Database::getInstance();
	DBQuery query;

	std::string tmp;
	if(!getDatabaseConfig(config, tmp))
		query << "INSERT INTO `server_config` VALUES (" << db->escapeString(config) << ", " << db->escapeString(value) << ");";
	else
		query << "UPDATE `server_config` SET `value` = " << db->escapeString(value) << " WHERE `config` = " << db->escapeString(config) << ";";

	db->executeQuery(query.str());
}

void DatabaseManager::checkEncryption()
{
	int32_t currentValue = g_config.getNumber(ConfigManager::PASSWORD_TYPE);
	int32_t oldValue = 0;
	if(getDatabaseConfig("encryption", oldValue))
	{
		if(currentValue == oldValue)
			return;

		if(oldValue != PASSWORD_TYPE_PLAIN)
		{
			std::string oldName;
			if(oldValue == PASSWORD_TYPE_MD5)
				oldName = "md5";
			else if(oldValue == PASSWORD_TYPE_SHA1)
				oldName = "sha1";
			else
				oldName = "plain";

			g_config.setNumber(ConfigManager::PASSWORD_TYPE, oldValue);
			std::cout << "> WARNING: Unsupported password hashing switch! Change back passwordType in config.lua to \"" << oldName << "\"!" << std::endl;
			return;
		}

		switch(currentValue)
		{
			case PASSWORD_TYPE_MD5:
			{
				Database* db = Database::getInstance();
				DBQuery query;
				if(db->getDatabaseEngine() != DATABASE_ENGINE_MYSQL)
				{
					DBResult* result = db->storeQuery("SELECT `id`, `password`, `key` FROM `accounts`;");
					if(result)
					{
						do
						{
							query << "UPDATE `accounts` SET `password` = " << db->escapeString(transformToMD5(result->getDataString("password"))) << ", `key` = " << db->escapeString(transformToMD5(result->getDataString("key"))) << " WHERE `id` = " << result->getDataInt("id") << ";";
							db->executeQuery(query.str());
						}
						while(result->next());
						db->freeResult(result);
					}
				}
				else
					db->executeQuery("UPDATE `accounts` SET `password` = MD5(`password`), `key` = MD5(`key`);");

				std::cout << "> Password type has been updated to MD5." << std::endl;
				break;
			}

			case PASSWORD_TYPE_SHA1:
			{
				Database* db = Database::getInstance();
				DBQuery query;
				if(db->getDatabaseEngine() != DATABASE_ENGINE_MYSQL)
				{
					DBResult* result = db->storeQuery("SELECT `id`, `password`, `key` FROM `accounts`;");
					if(result)
					{
						do
						{
							query << "UPDATE `accounts` SET `password` = " << db->escapeString(transformToSHA1(result->getDataString("password"))) << ", `key` = " << db->escapeString(transformToSHA1(result->getDataString("key"))) << " WHERE `id` = " << result->getDataInt("id") << ";";
							db->executeQuery(query.str());
						}
						while(result->next());
						db->freeResult(result);
					}
				}
				else
					db->executeQuery("UPDATE `accounts` SET `password` = SHA1(`password`), `key` = SHA1(`key`);");

				std::cout << "> Password type has been updated to SHA1." << std::endl;
				break;
			}

			default: break;
		}
	}
	else if(g_config.getBoolean(ConfigManager::ACCOUNT_MANAGER))
	{
		switch(currentValue)
		{
			case PASSWORD_TYPE_MD5:
			{
				Database* db = Database::getInstance();
				DBQuery query;
				query << "UPDATE `accounts` SET `password` = " << db->escapeString(transformToMD5("1")) << " WHERE `id` = 1 AND `password` = '1';";
				db->executeQuery(query.str());
				break;
			}

			case PASSWORD_TYPE_SHA1:
			{
				Database* db = Database::getInstance();
				DBQuery query;
				query << "UPDATE `accounts` SET `password` = " << db->escapeString(transformToSHA1("1")) << " WHERE `id` = 1 AND `password` = '1';";
				db->executeQuery(query.str());
				break;
			}

			default: break;
		}
	}
	registerDatabaseConfig("encryption", currentValue);
}

void DatabaseManager::checkTriggers()
{
	/*
	Database* db = Database::getInstance();
	switch(db->getDatabaseEngine())
	{
	}
	*/
}
