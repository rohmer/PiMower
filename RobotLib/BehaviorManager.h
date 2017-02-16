#pragma once
#include "RobotLib.h"
#include "Behavior.h"
#include "Charging.h"
#include "States.h"
#include <map>

class BehaviorManager
{
	BehaviorManager(RobotLib *robotLib);
	~BehaviorManager();
	void behaviorLoop();
	
private:
	void stateChange(states_t newState);
	
	bool wasInMowingPeriod = false;
	uint8_t mowingSessions;	
	RobotLib *robotLib;
	std::map<states_t, Behavior *> behaviors;
	Scheduler *scheduler;
	states_t currentState;
};