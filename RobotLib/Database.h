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
#include <Poco/Data/SQLite/Connector.h>

#define DB_LOCATION "/usr/local/Robot/robot.db"

class RobotLib;

class Database
{
public:
	static Database& getInstance()
	{
		static Database instance;
		return instance;
	}		
	bool execSql(std::string sqlStmt);				
	bool insertPositionEvent(sensors_event_t *event);	
	static std::mutex dbMutex;
	
	static Poco::Data::Session getDBSession();
	
	~Database();
	
private:
	Database();	
	static Poco::Data::SessionPool *sessionPool;
	void initDB();
	bool createPositionTable();
	bool createConfigTable();
	bool createScheduleTable();
	bool createStateTable();
	bool createMapTable();
	bool createLogTable();
	bool createEventTable();
		
	bool tableExists(std::string tableName);
	
public:
	Database(Database const&)		= delete;
	void operator=(Database const&)	= delete;
};
