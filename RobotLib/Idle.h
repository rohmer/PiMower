#pragma once
#include "Behavior.h"
#include "../RobotController/SensorLib/BQ34Z100G1.h"

class Idle : Behavior
{
public:
	Idle(RobotLib* robotLib);
	~Idle() override;
	
	uint8_t run() override;
	
private:
	BQ34Z100G1 *batterySensor;
};

