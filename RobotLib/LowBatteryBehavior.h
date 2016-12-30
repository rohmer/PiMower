#pragma once
#include "Behavior.h"

// Robot is in the field but needs charge
class LowBatteryBehavior : public Behavior
{
public:
	ChargingBehavior(RobotLib* robotLib);
	virtual bool takeControl();
	virtual void action();
};
