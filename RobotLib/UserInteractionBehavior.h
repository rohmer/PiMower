#pragma once
#include "Behavior.h"

// User is inteacting with the controls
class UserInteractionBehavior : public Behavior
{
	public:
		UserInteractionBehavior(RobotLib* robotLib);
		virtual bool takeControl();
		virtual void action();
};

