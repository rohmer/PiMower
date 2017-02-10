#include "Charging.h"

Charging::Charging(RobotLib *robotLib)
	: BehaviorBase(robotLib, "Charging")
{
	
}

// Charging has only one exit point, that we start mowing
// Mowing = return val 1
// TODO: Create the UI stuff to update during all of the different
//		 behaviors
uint8_t Charging::run()
{
	
	return 1;
}