#include "Database.h"
RobotLib *Database::robotLib;
bool Database::initialized;	

Database::Database(RobotLib *robotLib)
{
	this->robotLib = robotLib;
	initialized = false;
	initDB();
}

void Database::initDB()
{
	try
	{
		SQLite::Database db(DB_LOCATION, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		// Check for all our tables
		if (!db.tableExists("Position"))
			createPositionTable();
		if (!db.tableExists("Config"))
			createConfigTable();
		if (!db.tableExists("Schedule"))
			createScheduleTable();
		if (!db.tableExists("State"))
			createStateTable();
		if (!db.tableExists("LawnMap"))
			createMapTable();

	}
	catch (std::exception &e)
	{
		robotLib->LogException(e);
	}
	
	robotLib->Log("Database Initialized");
}

bool Database::createMapTable()
{
	std::string sql = "CREATE TABLE LawnMap("\
		"X INT NOT NULL, "\
		"Y INT NOT NULL, "\
		"Latitude FLOAT, "\
		"Longitude FLOAT, " \
		"Blocking BOOLEAN, " \
		"Contents INT)";
	return execSql(sql);
}

bool Database::createStateTable()
{
	std::string sql = "CREATE TABLE State("\
		"sessionID CHAR(36) PRIMARY KEY NOT NULL,"\
		"State INT,"\
		"Timestamp DATETIME)";
	return execSql(sql);
}

bool Database::createScheduleTable()
{
	std::string sql = "CREATE TABLE Schedule("\
		"DayOfWeek INT," \
		"StartHour INT," \
		"StartMinute INT," \
		"EndHour INT, "\
		"EndMinute INT, " \
		"MowingSessions INT)";
	return execSql(sql);
}

bool Database::createConfigTable()
{
	std::string sql = "CREATE TABLE Config(" \
		"LogLevel INT," \
		"DriveWheelDiameter REAL, "\
		"DriveGearRatio REAL, " \
		"DriveMotorMaxRPM INT, " \
		"PWMI2C INT, " \
		"LeftDriveChanel INT, " \
		"RightDriveChannel INT, " \
		"BladeChannel INT, " \
		"ArduinoHostI2C INT, " \
		"ProximityTollerance REAL, " \
		"NormalOperationRPM INT, " \
		"NormalReverseRPM INT, " \
		"NormalRotationalRPM INT, " \
		"ObjectForwardRPM INT, " \
		"ObjectReverseRPM INT, " \
		"AccelNormal INT, " \
		"AccelRotational INT, " \
		"EncoderLeft INT, " \
		"EncoderRight INT, " \
		"BatteryPctToStartCharge INT)";
		
	if (!execSql(sql))
		return false;
	
	sql = "CREATE TABLE Sensors(" \
		"SensorType INT, " \
		"TriggerPin INT, " \
		"EchoPin INT, " \
		"Location CHAR(5), " \
		"Name CHAR(32))";
	return execSql(sql);	
}

bool Database::createPositionTable()
{
	std::string sql = "CREATE TABLE Position("	\
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