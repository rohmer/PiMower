#pragma once
#include "RobotLib.h"
#include "RobotStatus.h"
#include <string>

// Abstract superclass for behaviors
class Behavior
{
	public:
		std::string behaviorName;
		bool enabled;
		bool supressed;
		Behavior(RobotLib *robotLib)
		{
			supressed = false;
			enabled = true;
			this->robotLib = robotLib;
		}
		virtual void enable(bool flag)
		{
			if (enabled == true)
			{
				return;
			}
			enabled = flag;
		}
		virtual void surpress()
		{
			supressed = true;
		}
		virtual bool takeControl()
		{
		}
		virtual void action()
		{
		}
	
	protected:
		RobotLib* robotLib;
};