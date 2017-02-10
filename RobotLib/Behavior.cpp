#include "Behavior.h"

std::string BehaviorBase::getBehaviorName()
{
	return behaviorName;
}


uint8_t BehaviorBase::run()
{
	time_t t = time(0);
	behaviorStartTime = localtime(&t);
	std::stringstream ss;
	ss << "Starting behavior: " << behaviorName;
	robotLib->Log(ss.str());
}