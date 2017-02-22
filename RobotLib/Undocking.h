#pragma once
#include "Behavior.h"

// If we are docked, the landing node is 3 feet behind us (180 degrees opposite)

class Undocking : public Behavior
{
public:
	Undocking(RobotLib *robotLib, GPSManager *gpsManager, MotionController *motionController);
	
	uint8_t run() override;
	
private:
	
};