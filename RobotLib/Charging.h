#pragma once
#include "Behavior.h"

class Charging : BehaviorBase
{
public:
	Charging(RobotLib* robotLib);
	~Charging() override
	{
	}
	
	uint8_t run() override;
};
	