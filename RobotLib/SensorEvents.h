#pragma once

#include "Database.h"
#include <time.h>
#include "../RobotController/SensorLib/SensorLib.h"

class SensorEvents
{
public:
	static bool insertPosition(sensors_gps positionEvent);
};