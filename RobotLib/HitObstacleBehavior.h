#pragma once
#include "Behavior.h"

// Robot hit obstacle (Bump, sonor, grass detection, etc)
class HitObstacleBehavor: public Behavior
{
public:
	HitObstacleBehavor(RobotLib* robotLib);
	virtual bool takeControl();
	virtual void action();
};
