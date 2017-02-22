#pragma once
#include "RobotLib.h"
#include "../3rdParty/SQLite/sqlite3.h"
#include <sstream>
#include <string>
#include "../3rdParty/SQLiteC++/include/SQLiteCpp/Database.h"
#include "SensorEvents.h"
#include <stdarg.h>

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
	SQLite::Database *getDBHandle()
	{
		return dbHandle;
	}
	
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
		
	SQLite::Database *dbHandle = NULL;
	
public:
	Database(Database const&)		= delete;
	void operator=(Database const&)	= delete;
};
