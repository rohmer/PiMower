#pragma once
#include "RobotLib.h"
#include "States.h"
#include <ctime>
#include <sstream>
#include "MotionController.h"

class Behavior
{
public:
	Behavior(RobotLib *robotLib,
		GPSManager *gpsManager,
		MotionController *motionController,
		std::string behaviorName)
	{
		this->robotLib = robotLib;
		this->gpsManager = gpsManager;
		this->motionController = motionController;
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
	GPSManager *gpsManager;
	std::string behaviorName;
	MotionController *motionController;
	struct tm *behaviorStartTime;
};
