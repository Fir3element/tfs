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

#include <iostream>

#include "database.h"
#include "databasepgsql.h"

#include "configmanager.h"
extern ConfigManager g_config;

/** DatabasePgSQL definitions */

DatabasePgSQL::DatabasePgSQL()
{
	// load connection parameters
	std::stringstream dns;
	dns << "host='" << g_config.getString(ConfigManager::SQL_HOST) << "' dbname='" << g_config.getString(ConfigManager::SQL_DB) << "' user='" << g_config.getString(ConfigManager::SQL_USER) << "' password='" << g_config.getString(ConfigManager::SQL_PASS) << "' port='" << g_config.getNumber(ConfigManager::SQL_PORT) << "'";

	m_handle = PQconnectdb(dns.str().c_str());
	m_connected = PQstatus(m_handle) == CONNECTION_OK;
	if(!m_connected)
		std::cout << "Failed to estabilish PostgreSQL database connection: " << PQerrorMessage(m_handle) << std::endl;
}

DatabasePgSQL::~DatabasePgSQL()
{
	PQfinish(m_handle);
}

bool DatabasePgSQL::getParam(DBParam_t param)
{
	switch(param)
	{
		case DBPARAM_MULTIINSERT:
			return true;

		default:
			break;
	}

	return false;
}

bool DatabasePgSQL::beginTransaction()
{
	return executeQuery("BEGIN");
}

bool DatabasePgSQL::rollback()
{
	return executeQuery("ROLLBACK");
}

bool DatabasePgSQL::commit()
{
	return executeQuery("COMMIT");
}

bool DatabasePgSQL::executeQuery(const std::string& query)
{
	if(!m_connected)
		return false;

	#ifdef __SQL_QUERY_DEBUG__
	std::cout << "PGSQL QUERY: " << query << std::endl;
	#endif

	// executes query
	PGresult* res = PQexec(m_handle, _parse(query).c_str());
	ExecStatusType stat = PQresultStatus(res);
	if(stat != PGRES_COMMAND_OK && stat != PGRES_TUPLES_OK)
	{
		std::cout << "PQexec(): " << query << ": " << PQresultErrorMessage(res) << std::endl;
		PQclear(res);
		return false;
	}

	// everything went fine
	PQclear(res);
	return true;
}

DBResult* DatabasePgSQL::storeQuery(const std::string& query)
{
	if(!m_connected)
		return NULL;

	#ifdef __SQL_QUERY_DEBUG__
	std::cout << "PGSQL QUERY: " << query << std::endl;
	#endif

	// executes query
	PGresult* res = PQexec(m_handle, _parse(query).c_str());
	ExecStatusType stat = PQresultStatus(res);
	if(stat != PGRES_COMMAND_OK && stat != PGRES_TUPLES_OK)
	{
		std::cout << "PQexec(): " << query << ": " << PQresultErrorMessage(res) << std::endl;
		PQclear(res);
		return false;
	}

	// everything went fine
	DBResult* results = new PgSQLResult(res);
	return verifyResult(results);
}

std::string DatabasePgSQL::escapeString(const std::string& s)
{
	// remember to quote even empty string!
	if(!s.size())
		return std::string("''");

	// the worst case is 2n + 1
	int32_t error;
	char* output = new char[(s.length() * 2) + 1];
	// quotes escaped string and frees temporary buffer
	PQescapeStringConn(m_handle, output, s.c_str(), s.length(), reinterpret_cast<int32_t*>(&error));

	std::string r = std::string("'");
	r += output;
	r += "'";

	delete[] output;
	return r;
}

std::string DatabasePgSQL::escapeBlob(const char *s, uint32_t length)
{
	// remember to quote even empty stream!
	if(!s)
		return std::string("''");

	// quotes escaped string and frees temporary buffer
	size_t len;
	char* output = (char*)PQescapeByteaConn(m_handle, (uint8_t*)s, length, &len);

	std::string r = std::string("E'");
	r += output;
	r += "'";

	PQfreemem(output);
	return r;
}

std::string DatabasePgSQL::_parse(const std::string& s)
{
	std::string query = "";

	bool inString = false;
	for(uint32_t a = 0; a < s.length(); a++)
	{
		uint8_t ch = s[a];
		if(ch == '\'')
		{
			if(inString && s[a + 1] != '\'')
				inString = false;
			else
				inString = true;
		}

		if(ch == '`' && !inString)
			ch = '"';

		query += ch;
	}

	return query;
}

void DatabasePgSQL::freeResult(DBResult* res)
{
	if(res)
	{
		delete (PgSQLResult*)res;
		res = NULL;
	}
	else
		std::cout << "[Warning - DatabasePgSQL::freeResult] Trying to free already freed result." << std::endl;
}

/** PgSQLResult definitions */

int32_t PgSQLResult::getDataInt(const std::string& s)
{
	return atoi(PQgetvalue(m_handle, m_cursor, PQfnumber(m_handle, s.c_str())));
}

int64_t PgSQLResult::getDataLong(const std::string& s)
{
	return ATOI64(PQgetvalue(m_handle, m_cursor, PQfnumber(m_handle, s.c_str())));
}

std::string PgSQLResult::getDataString(const std::string& s)
{
	return std::string(PQgetvalue(m_handle, m_cursor, PQfnumber(m_handle, s.c_str())));
}

const char* PgSQLResult::getDataStream(const std::string& s, uint64_t& size)
{
	std::string buf = PQgetvalue(m_handle, m_cursor, PQfnumber(m_handle, s.c_str()));
	uint8_t* temp = PQunescapeBytea( (const uint8_t*)buf.c_str(), (size_t*)&size);

	char* value = new char[buf.size()];
	strcpy(value, (char*)temp);

	PQfreemem(temp);
	return value;
}

bool PgSQLResult::next()
{
	if(m_cursor >= m_rows)
		return false;

	m_cursor++;
	return true;
}

PgSQLResult::PgSQLResult(PGresult* results)
{
	m_handle = results;
	m_cursor = -1;
	m_rows = PQntuples(m_handle) - 1;
}
