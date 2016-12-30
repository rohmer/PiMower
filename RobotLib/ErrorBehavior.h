#pragma once
#include "Behavior.h"

// Robot has encountered an error condition
class ErrorBehavior : public Behavior
{
public:
	ErrorBehavior(RobotLib* robotLib);
	virtual bool takeControl();
	virtual void action();
};
