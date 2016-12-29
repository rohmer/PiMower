#pragma once
#include "RobotLib.h"
#include "../3rdParty/SQLite/sqlite3.h"
#include <sstream>
#include <string>
#include "../3rdParty/SQLiteC++/include/SQLiteCpp/Database.h"
#include "SensorEvents.h"

#define DB_LOCATION "/usr/local/Robot/robot.db"

class RobotLib;

class Database
{
	public:
		Database(RobotLib &robotLib);		
		static bool execSql(std::string sqlStmt);				
		bool insertGPSEvent(sensors_gps event);
			
		static RobotLib *getRobotLib()
		{
			return robotLib;
		}
		~Database();
	
	private:
		static void initDB();
		static bool createPositionTable();
		
		static RobotLib *robotLib;
		static bool initialized;		
};
