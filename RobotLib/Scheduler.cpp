#include "Scheduler.h"

Scheduler::Scheduler(RobotLib *robotLib)
{
	this->robotLib = robotLib;	
}

void Scheduler::setDOWTime(eDOW dayOfWeek, 
	uint8_t hourStart, 
	uint8_t minStart, 
	uint8_t hourStop, 
	uint8_t minuteStop,
	uint8_t mowingSessions)
{
	Poco::Data::Session session = Database::getDBSession();
	Poco::Data::Statement stmt(session);
	
	
	stmt << "INSERT INTO Schedule(?,?,?,?,?,?)", 
		Poco::Data::Keywords::bind(dayOfWeek),
		Poco::Data::Keywords::bind(hourStart),
		Poco::Data::Keywords::bind(minStart),
		Poco::Data::Keywords::bind(hourStop),
		Poco::Data::Keywords::bind(minuteStop),
		Poco::Data::Keywords::bind(mowingSessions);
	
	if (stmt.execute()!=0)
		robotLib->LogError("Failed to insert schedule entry");
}

void Scheduler::clearSchedule()
{
	Poco::Data::Session session = Database::getDBSession();
	
	session << "DELETE from Schedule";		
}

void Scheduler::clearSchedule(eDOW dayOfWeek)
{
	Poco::Data::Session session = Database::getDBSession();
	Poco::Data::Statement stmt(session);
	
	
	stmt << "DELETE FROM Schedule WHERE DayOfWeek=?", 
		Poco::Data::Keywords::bind(dayOfWeek);
		
	if (stmt.execute() != 0)
		robotLib->LogError("Failed to insert schedule entry");	
}

bool Scheduler::legalMowingTime(uint8_t numberOfSessionsComplete)
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Poco::Data::Session session = Database::getDBSession();
	Poco::Data::Statement stmt(session);
	
	
	stmt << "SELECT * FROM Schedule WHERE DayOfWeek=? AND "\
		"StartHour<=? AND StartMinute<=? AND" \
		"EndHour>=? AND EndMinute>=? AND mowingSessions>?",		
		Poco::Data::Keywords::bind(now->tm_wday),
		Poco::Data::Keywords::bind(now->tm_hour),
		Poco::Data::Keywords::bind(now->tm_min),
		Poco::Data::Keywords::bind(now->tm_hour),
		Poco::Data::Keywords::bind(now->tm_min),
		Poco::Data::Keywords::bind(numberOfSessionsComplete);
	
	
	{
		std::unique_lock<std::mutex> lock(Database::dbMutex);
		while (!stmt.done())
		{
			return true;
		}
	}
	return false;	
}