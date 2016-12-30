#pragma once
#include "Behavior.h"

// Robot is charging
class ChargingBehavior : public Behavior
{
public:
	ChargingBehavior(RobotLib* robotLib);
	virtual bool takeControl();
	virtual void action();
};
