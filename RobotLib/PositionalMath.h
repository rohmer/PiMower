#pragma once
#include "Point.h"
#include <math.h>
#include <tgmath.h>
#include "../RobotController/SensorLib/SensorLib.h"

class PositionalMath
{
public:
	static Point getPointByAngleDist(Point startingPoint, float direction, float distance);
	static std::pair<double, double> decPointFromPos(sensors_event_t *location);
	static double inchesToLat(int inches);
	static double inchesToLong(int inches);
	static double latToInches(double lat);
	static double longToInches(double lat);
};
