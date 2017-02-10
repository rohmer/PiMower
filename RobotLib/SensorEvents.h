#pragma once

#include "Database.h"
#include <time.h>
#include "../RobotController/SensorLib/SensorLib.h"

class SensorEvents
{
public:
	static bool insertPositionEvent(Guid sessionID, sensors_event_t *positionEvent);
};