#pragma once
#include "RobotLib.h"
#include "Database.h"
#include <time.h>

/*
	Scheduler is fairly simple, there are basically just 
	a few parameters:
	  A) Times we can mow
	  B) Time between mowing sessions
	  C) Number of times we will mow per session (Charging between)
	  
	  For example:
	  10am-5pm legal mowing, monday->friday
	  2pm-5pm legal mowing saturday
	  No mowing sunday
	  
	  Mow 2 times per day we mow
	  48 hours between mowing session
*/

class Scheduler
{
public:
	enum eDOW
	{
		Sunday    = 0,
		Monday    = 1,
		Tuesday   = 2,
		Wedensday = 3,
		Thursday  = 4,
		Friday    = 5,
		Saturday  = 6
	};
	
	Scheduler(RobotLib *robotLib);
	bool legalMowingTime(uint8_t numberOfSessionsComplete);
	void setDOWTime(eDOW dayOfWeek, uint8_t hourStart, uint8_t minStart, uint8_t hourStop, uint8_t minuteStop, uint8_t mowingSessions);
	void clearSchedule();
	void clearSchedule(eDOW dayOfWeek);
	
private:
	RobotLib *robotLib;
	
	struct sMowingRecord
	{
		eDOW dayOfWeek;
		uint8_t hourStart, minuteStart, hourEnd, minuteEnd;
	};
	
};