#pragma once
#include "Behavior.h"

class Charging : BehaviorBase
{
	public:
		Charging(RobotLib* robotLib, std::string behaviorName);
		~Charging() override
		{
		}
	
};
	