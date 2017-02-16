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
	SQLite::Database db(DB_LOCATION, SQLite::OPEN_READWRITE);
	SQLite::Statement stmt(db, "INSERT INTO Schedule(?,?,?,?,?,?)");
	stmt.bind(1, dayOfWeek);
	stmt.bind(2, hourStart);
	stmt.bind(3, minStart);
	stmt.bind(4, hourStop); 
	stmt.bind(5, minuteStop);
	stmt.bind(6, mowingSessions);
	
	if (stmt.exec() != 0)
		robotLib->LogError("Failed to insert schedule entry");
}

void Scheduler::clearSchedule()
{
	SQLite::Database db(DB_LOCATION, SQLite::OPEN_READWRITE);
	if (!db.exec("DELETE from Schedule"))
		robotLib->LogError("Failed to truncate schedule");	
}

void Scheduler::clearSchedule(eDOW dayOfWeek)
{
	SQLite::Database db(DB_LOCATION, SQLite::OPEN_READWRITE);
	SQLite::Statement stmt(db, "DELETE FROM Schedule WHERE DayOfWeek=?");
	stmt.bind(1, dayOfWeek);
	if (stmt.exec()<0)
		robotLib->LogError("Failed to truncate schedule");	
}

bool Scheduler::legalMowingTime(uint8_t numberOfSessionsComplete)
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	SQLite::Database db(DB_LOCATION, SQLite::OPEN_READWRITE);
	SQLite::Statement stmt(db, "SELECT * FROM Schedule WHERE DayOfWeek=? AND "\
		"StartHour<=? AND StartMinute<=? AND" \
		"EndHour>=? AND EndMinute>=? AND mowingSessions>?");
	stmt.bind(1, now->tm_wday);
	stmt.bind(2, now->tm_hour);
	stmt.bind(3, now->tm_min);
	stmt.bind(4, now->tm_hour);
	stmt.bind(5, now->tm_min);
	stmt.bind(6, numberOfSessionsComplete);
	
	while (stmt.executeStep())
	{
		return true;
	}
	return false;	
}