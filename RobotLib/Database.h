#pragma once
#include "RobotLib.h"
#include <sstream>
#include <string>
#include "SensorEvents.h"
#include <cstdarg>
#include <mutex>

#include <iostream>
#include <Poco/Logger.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/SessionPool.h>
#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>

#define MYSQL_USER "root"
#define MYSQL_PWD  "pirobot"
#define MYSQL_HOST "127.0.0.1"
#define MYSQL_PORT 3306
#define MYSQL_DB   "pirobot"

class RobotLib;

class Database
{
public:
	static Database& getInstance()
	{
		if (!init)
		{
			Database::initDB();
			init = true;
		}
		static Database instance;
		return instance;
	}
	static bool execSql(std::string sqlStmt);
	bool insertPositionEvent(sensors_event_t *event);
	static std::mutex dbMutex;

	static Poco::Data::Session getDBSession();
	static void initDB();
	~Database();

private:
	static bool init;
	Database();
	static Poco::Data::SessionPool *sessionPool;
	static bool createPositionTable();
	static bool createConfigTable();
	static bool createScheduleTable();
	static bool createStateTable();
	static bool createMapTable();
	static bool createLogTable();
	static bool createEventTable();

	static bool tableExists(std::string tableName);

public:
	Database(Database const&)		= delete;
	void operator=(Database const&)	= delete;
};
