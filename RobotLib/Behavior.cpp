#include "Behavior.h"

Behavior::Behavior(RobotLib *robotLib, std::string name)
{
	{
		supressed = false;
		enabled = true;
		this->behaviorName = name;
		this->robotLib = robotLib;
	}
}