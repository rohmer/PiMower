#pragma once
#include "Behavior.h"

// robot is idle (not driving around or charging)
class StandbyBehavior : public Behavior
{
	public:
		StandbyBehavior(RobotLib* robotLib);
		virtual bool takeControl();
		virtual void action();
};

