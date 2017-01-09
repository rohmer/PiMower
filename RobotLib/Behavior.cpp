#include "Behavior.h"

void BehaviorBase::startBehavior()
{
	time_t t = time(0);
	behaviorStartTime = localtime(&t);
	std::stringstream ss;
	ss << "Starting behavior: " << behaviorName;
	robotLib->Log(ss.str());
}