#pragma once
#include "RobotLib.h"
#include "GPSManager.h"

class MotionController
{
	MotionController(RobotLib *robotLib);
	
private:
	
	void initialize();
	GPSManager *gpsManager;
	RobotLib *robotLib;
	bool errorState = false;
};
