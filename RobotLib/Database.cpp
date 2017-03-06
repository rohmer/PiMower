#include "Database.h"
std::mutex Database::dbMutex;
Poco::Data::SessionPool *Database::sessionPool;

Database::Database()
{
	initDB();
}

Poco::Data::Session Database::getDBSession()
{
	return sessionPool->get();
}

void Database::initDB()
{
	try
	{
		Poco::Data::SQLite::Connector::registerConnector();		
		sessionPool = new Poco::Data::SessionPool("SQLite", DB_LOCATION);
		Poco::Data::Session  dbSession("SQLite", DB_LOCATION);
		// Check for all our tables
		if (!tableExists("Position"))
			createPositionTable();
		if (!tableExists("Config"))
			createConfigTable();
		if (!tableExists("Schedule"))
			createScheduleTable();
		if (!tableExists("State"))
			createStateTable();
		if (!tableExists("LawnMap"))
			createMapTable();
		if (!tableExists("Log"))
			createLogTable();
		if (!tableExists("Events"))
			createEventTable();

	}
	catch (std::exception &e)
	{
		std::stringstream ss;
		ss << "Exception caught: " << e.what() << std::endl;
		Poco::Logger &logger = Poco::Logger::get("RobotLib");
		logger.fatal(ss.str());		
	}	
}

bool Database::tableExists(std::string tableName)
{
	Poco::Data::Session dbSession = getDBSession();
	Poco::Data::Statement select(dbSession);
	std::string name;
	select << "SELECT name FROM sqlite_master WHERE name=? and type='table'", 
		Poco::Data::Keywords::bind(tableName),
		Poco::Data::Keywords::into(name);
	while (!select.done())
	{		
		select.execute();
		if (name == tableName)
			return true;
	}
	return false;
}

bool Database::createLogTable()
{
	std::string sql = "CREATE TABLE Log("\
		"timestamp DATETIME NOT NULL, "\
		"severity INT NOT NULL, "\
		"message TEXT, "\
		"sessionID CHAR(36))";
	return execSql(sql);
}

bool Database::createEventTable()
{
	std::string sql = "CREATE TABLE Events("\
		"timestamp DATETIME NOT NULL, "\
		"eventType INT NOT NULL, "\
		"eventValue0 FLOAT,"\
		"eventValue1 FLOAT,"\
		"eventValue2 FLOAT,"\
		"eventValue3 FLOAT,"\
		"eventValue4 FLOAT,"\
		"SessionID CHAR(36) PRIMARY KEY NOT NULL)";
	return execSql(sql);
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
		"BatteryPctToStartCharge INT, " \
		"MapScale INT, "\
		"EncoderTicksPerRevolution INT," \
		"ErrorLEDPin INT)";
		
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
	{		
		std::unique_lock<std::mutex> lock(this->dbMutex);
		try
		{
			Poco::Data::Session session = getDBSession();
			session << sqlStmt, Poco::Data::Keywords::now;
			return true;
		}
		catch (std::exception &e)
		{
			std::stringstream ss;
			ss << "Exception caught: " << e.what() << std::endl;
			Poco::Logger &logger = Poco::Logger::get("RobotLib");
			logger.fatal(ss.str());		
			return false;
		}	
	}
}

bool Database::insertPositionEvent(sensors_event_t *event)
{
	Guid sessionID = RobotLib::getSessionID();
	return SensorEvents::insertPositionEvent(sessionID, event);
}

Database::~Database()
{		
}

