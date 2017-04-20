#include "Idle.h"

// Idle is when the mower is just sitting, not docked
// The only options here are:
// 1. Someone does something on the UI (This will manually set the state machine)
// 2. The battery drains to the batteryChargePct, in which case it will seek the dock

Idle::Idle(RobotLib *robotLib, GPSManager *gpsManager, MotionController *motionController)
	: Behavior(robotLib, gpsManager, motionController, "Idle")
{
	batterySensor = (BQ34Z100G1 *)robotLib->getDeviceManager()->getByName("BQ34Z100-G1");
}

Idle::~Idle()
{
	delete(batterySensor);
}

// Return 0 if we stay in Idle
// 1 if we are to dock
uint8_t Idle::run()
{
	if (batterySensor->getPctRemaining() < robotLib->getConfig()->getMinimumBatteryPct())
		return 1;
	return 0;
}