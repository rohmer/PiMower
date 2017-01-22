#pragma once

#include "Database.h"
#include <time.h>
#include "../RobotController/SensorLib/SensorLib.h"

class SensorEvents
{
public:
	static bool insertPositionEvent(sensors_event_t *positionEvent);
};