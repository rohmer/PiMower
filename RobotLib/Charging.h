#pragma once
#include "Behavior.h"
#include "Scheduler.h"
#include "../RobotController/SensorLib/INA219.h"
#include "../RobotController/SensorLib/BQ34Z100G1.h"

class Charging : Behavior
{
public:
	Charging(RobotLib* robotLib, Scheduler *scheduler);
	~Charging() override;
	
	uint8_t run() override;
	
private:
	Scheduler *scheduler;
	INA219 *currentSensor;
	BQ34Z100G1 *batterySensor;
};
	