#include "Database.h"
RobotLib *Database::robotLib;
bool Database::initialized;	

Database::Database(RobotLib &robotLib)
{
	this->robotLib = &robotLib;
	initialized = false;
	initDB();
}

void Database::initDB()
{
	try
	{
		SQLite::Database db(DB_LOCATION, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		// Check for all our tables
		if (!db.tableExists("POSITION"))
			createPositionTable();
	}
	catch (std::exception &e)
	{
		robotLib->LogException(e);
	}
	
	robotLib->Log("Database Initialized");
}


bool Database::createPositionTable()
{
	std::string sql = "CREATE TABLE position("	\
		"sessionID CHAR(36) PRIMARY KEY NOT NULL," \
		"timestamp INTEGER NOT NULL," \
		"LAT_Degrees REAL," \
		"LAT_Minutes REAL," \
		"LONG_Degrees REAL," \
		"LONG_Minutes REAL," \
		"LAT_Cardinal CHAR(1)," \
		"LONG_Cardinal CHAR(1),"  \
		"Altitude REAL," \
		"GEOID_Height REAL," \
		"Speed_KPH REAL, " \
		"Course REAL, " \
		"MAGVariation REAL," \
		"HDOP, " \
		"FixQuality INT, " \
		"Satellites INT, " \
		"Fix BOOLEAN, " \
		"Heading REAL, " \
		"Pitch REAL, "\
		"Roll REAL, "\
		"AccelX REAL, " \
		"AccelY REAL, "\
		"AccelZ REAL)";		
	
	return execSql(sql);		
}

bool Database::execSql(std::string sqlStmt)
{
	try
	{
		SQLite::Database db(DB_LOCATION, SQLite::OPEN_READWRITE);
		db.exec(sqlStmt);
		return true;
	}
	catch (std::exception &e)
	{
		robotLib->LogException(e);
		return false;
	}	
}

bool Database::insertPositionEvent(sensors_event_t *event)
{
	Guid sessionID = robotLib->getSessionID();
	return SensorEvents::insertPositionEvent(sessionID, event);
}

Database::~Database()
{	
}