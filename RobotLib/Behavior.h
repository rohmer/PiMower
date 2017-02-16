#pragma once
#include "RobotLib.h"
#include "States.h"
#include <ctime>
#include <sstream>

class Behavior
{
public:
	Behavior(RobotLib *robotLib, std::string behaviorName)
	{
		this->robotLib = robotLib;
		this->behaviorName = behaviorName;
	}
	;		
	
	virtual ~Behavior()
	{
	}
		
	virtual uint8_t run()
	{
	}
		
	
	std::string getBehaviorName();
	
protected:
	RobotLib* robotLib;
	std::string behaviorName;
	struct tm *behaviorStartTime;
};