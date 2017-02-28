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
	
	~Database();
	
private:
	Database();	
	
	void initDB();
	bool createPositionTable();
	bool createConfigTable();
	bool createScheduleTable();
	bool createStateTable();
	bool createMapTable();
	bool createLogTable();
		
	bool tableExists(std::string tableName);
	
public:
	Database(Database const&)		= delete;
	void operator=(Database const&)	= delete;
};
