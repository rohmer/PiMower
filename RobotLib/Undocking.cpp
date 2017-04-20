#include "Undocking.h"

Undocking::Undocking(RobotLib *robotLib, GPSManager *gpsManager, MotionController *motionController)
	: Behavior(robotLib, gpsManager, motionController, "Undocking")
{
}

// Undocking has 2 things that can happen
// 0 - We undock successfully (i.e. travel 3 feet in reverse)
// 1 - We bump into something, at which case we will redock and set an error state

uint8_t Undocking::run()
{
	// Make sure the blade is disengaged and we are stopped to start with, not sure
	// how we couldnt be, but be sure
	motionController->allStop();
	eMotionResult res = motionController->travelDistance(36, false, false);
	if (res == eMotionResult::SUCCESS)
	{
		return 0;
	}
}