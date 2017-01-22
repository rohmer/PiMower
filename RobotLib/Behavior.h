#pragma once
#include "RobotLib.h"
#include "States.h"
#include <ctime>
#include <sstream>

class BehaviorBase
{
	public:
		BehaviorBase(RobotLib *robotLib, std::string behaviorName);		
		virtual ~BehaviorBase()
		{
		}
		
		virtual states_t run();
		virtual void startBehavior();
		
		std::string getBehaviorName();
	
	protected:
		RobotLib* robotLib;
		std::string behaviorName;
		struct tm *behaviorStartTime;
};