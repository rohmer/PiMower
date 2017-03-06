#include "RobotEvents.h"
#include "RobotLib.h"

std::string RobotEvents::getUUID()
{
	return RobotLib::getSessionIDStr();
}

void RobotEvents::speedChangeEvent(int previousSpeedLeft, int previousSpeedRight, int newSpeedLeft, int newSpeedRight)
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	std::stringstream timeStr;
	int year = now->tm_year + 1900;
	int mon = now->tm_mon + 1;
	int day = now->tm_mday + 1;
	timeStr << year << "-" << mon << "-" << day << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	Poco::Data::Session sess = Database::getDBSession();
	Poco::Data::Statement stmt(sess);
	stmt << "INSERT INTO Events VALUES(?,?,?,?,?,?,0,?)",
		Poco::Data::Keywords::bind(timeStr.str()),
		Poco::Data::Keywords::bind((int)SPEED_CHANGE),
		Poco::Data::Keywords::bind(previousSpeedLeft),
		Poco::Data::Keywords::bind(previousSpeedRight),
		Poco::Data::Keywords::bind(newSpeedLeft),
		Poco::Data::Keywords::bind(newSpeedRight),
		Poco::Data::Keywords::bind(getUUID());
	stmt.executeAsync();
}

void RobotEvents::headingChangeEvent(float previousHeading, int newHeading)
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	std::stringstream timeStr;
	int year = now->tm_year + 1900;
	int mon = now->tm_mon + 1;
	int day = now->tm_mday + 1;
	timeStr << year << "-" << mon << "-" << day << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	Poco::Data::Session sess = Database::getDBSession();
	Poco::Data::Statement stmt(sess);
	stmt << "INSERT INTO Events VALUES(?,?,?,?,0,0,0,?)",
		Poco::Data::Keywords::bind(timeStr.str()),
		Poco::Data::Keywords::bind((int)HEADING_CHANGE),
		Poco::Data::Keywords::bind(previousHeading),
		Poco::Data::Keywords::bind(newHeading),
		Poco::Data::Keywords::bind(getUUID());
	stmt.executeAsync();
}

void RobotEvents::headingChangedEvent(int newHeading)
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	std::stringstream timeStr;
	int year = now->tm_year + 1900;
	int mon = now->tm_mon + 1;
	int day = now->tm_mday + 1;
	timeStr << year << "-" << mon << "-" << day << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	Poco::Data::Session sess = Database::getDBSession();
	Poco::Data::Statement stmt(sess);
	stmt << "INSERT INTO Events VALUES(?,?,?,0,0,0,0,?)",
		Poco::Data::Keywords::bind(timeStr.str()),
		Poco::Data::Keywords::bind((int)HEADING_CHANGE_COMPLETE),
		Poco::Data::Keywords::bind(newHeading),
		Poco::Data::Keywords::bind(getUUID());
	stmt.executeAsync();
}

void RobotEvents::requestMoveEvent(int distanceInInches,bool forward)
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	std::stringstream timeStr;
	int year = now->tm_year + 1900;
	int mon = now->tm_mon + 1;
	int day = now->tm_mday + 1;
	timeStr << year << "-" << mon << "-" << day << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	Poco::Data::Session sess = Database::getDBSession();
	Poco::Data::Statement stmt(sess);
	int f = 1;
	if (!forward)
		f = 0;
	stmt << "INSERT INTO Events VALUES(?,?,?,?,0,0,0,?)",
		Poco::Data::Keywords::bind(timeStr.str()),
		Poco::Data::Keywords::bind((int)REQUEST_MOVE),
		Poco::Data::Keywords::bind(distanceInInches),
		Poco::Data::Keywords::bind(f),
		Poco::Data::Keywords::bind(getUUID());
	stmt.executeAsync();
}

void RobotEvents::completeMoveEvent()
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	std::stringstream timeStr;
	int year = now->tm_year + 1900;
	int mon = now->tm_mon + 1;
	int day = now->tm_mday + 1;
	timeStr << year << "-" << mon << "-" << day << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	Poco::Data::Session sess = Database::getDBSession();
	Poco::Data::Statement stmt(sess);
	stmt << "INSERT INTO Events VALUES(?,?,0,0,0,0,0,?)",
		Poco::Data::Keywords::bind(timeStr.str()),
		Poco::Data::Keywords::bind((int)COMPLETE_MOVE),		
		Poco::Data::Keywords::bind(getUUID());
	stmt.executeAsync();
}

void RobotEvents::turnOnBladeEvent()
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	std::stringstream timeStr;
	int year = now->tm_year + 1900;
	int mon = now->tm_mon + 1;
	int day = now->tm_mday + 1;
	timeStr << year << "-" << mon << "-" << day << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	Poco::Data::Session sess = Database::getDBSession();
	Poco::Data::Statement stmt(sess);
	stmt << "INSERT INTO Events VALUES(?,?,1,0,0,0,0,?)",
		Poco::Data::Keywords::bind(timeStr.str()),
		Poco::Data::Keywords::bind((int)TURN_ON_BLADE),		
		Poco::Data::Keywords::bind(getUUID());
	stmt.executeAsync();
}

void RobotEvents::turnOffBladeEvent()
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	std::stringstream timeStr;
	int year = now->tm_year + 1900;
	int mon = now->tm_mon + 1;
	int day = now->tm_mday + 1;
	timeStr << year << "-" << mon << "-" << day << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	Poco::Data::Session sess = Database::getDBSession();
	Poco::Data::Statement stmt(sess);
	stmt << "INSERT INTO Events VALUES(?,?,1,0,0,0,0,?)",
		Poco::Data::Keywords::bind(timeStr.str()),
		Poco::Data::Keywords::bind((int)TURN_ON_BLADE),
		Poco::Data::Keywords::bind(getUUID());
	stmt.executeAsync();
}

void RobotEvents::bumperActivatedEvent(eSensorLocation bumperLocation)
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	std::stringstream timeStr;
	int year = now->tm_year + 1900;
	int mon = now->tm_mon + 1;
	int day = now->tm_mday + 1;
	timeStr << year << "-" << mon << "-" << day << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	Poco::Data::Session sess = Database::getDBSession();
	Poco::Data::Statement stmt(sess);
	stmt << "INSERT INTO Events VALUES(?,?,?,0,0,0,0,?)",
		Poco::Data::Keywords::bind(timeStr.str()),
		Poco::Data::Keywords::bind((int)BUMPER_ACTIVATED),
		Poco::Data::Keywords::bind((int)bumperLocation),		
		Poco::Data::Keywords::bind(getUUID());
	stmt.executeAsync();
}

void RobotEvents::proximityActivatedEvent(eSensorLocation proximityLocation, float distanceInInches)
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	std::stringstream timeStr;
	int year = now->tm_year + 1900;
	int mon = now->tm_mon + 1;
	int day = now->tm_mday + 1;
	timeStr << year << "-" << mon << "-" << day << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	Poco::Data::Session sess = Database::getDBSession();
	Poco::Data::Statement stmt(sess);
	stmt << "INSERT INTO Events VALUES(?,?,?,?,0,0,0,?)",
		Poco::Data::Keywords::bind(timeStr.str()),
		Poco::Data::Keywords::bind((int)PROXIMITY_DETECTION),
		Poco::Data::Keywords::bind((int)proximityLocation),		
		Poco::Data::Keywords::bind((int)distanceInInches),				
		Poco::Data::Keywords::bind(getUUID());
	stmt.executeAsync();
}
