#include "Charging.h"

Charging::Charging(RobotLib *robotLib, GPSManager *gpsManager, MotionController *motionController, Scheduler *scheduler)
	: Behavior(robotLib, gpsManager, motionController, "Charging")
{
	this->scheduler = scheduler;
	currentSensor = (INA219 *)robotLib->getDeviceManager()->getByName("INA219");
	batterySensor = (BQ34Z100G1*)robotLib->getDeviceManager()->getByName("BQ34Z100G1");
}

Charging::~Charging()
{
}

// Charging has only three exit points, idle or charging, or ready
// Idle = return val 1
// Ready = 2
// Otherwise - stay 0, meaning our behavior doesnt change
uint8_t Charging::run()
{
	if (currentSensor->getBusVoltage_V() > 1)
	{
		// We are docked, set our current location to X=0, Y=0
		robotLib->setCurrentXLoc(0);
		robotLib->setCurrentYLoc(0);
		if (batterySensor->getPctRemaining() >= 99)
		{
			return 2;
		}
		return 0;
	}
	return 1;
}