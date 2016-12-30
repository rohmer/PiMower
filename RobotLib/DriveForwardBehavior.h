#pragma once
#include "Behavior.h"

// Robot is driving forward and mowing
class DriveForwardBehavior : public Behavior
{
public:
	DriveForwardBehavior(RobotLib* robotLib);
	virtual bool takeControl();
	virtual void action();
};

