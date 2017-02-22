#include "PositionalMath.h"

Point PositionalMath::getPointByAngleDist(Point startingPoint, float direction, float distance)
{
	double sinVal = sin(direction);
	// Y component
	float opposite = distance*sinVal;
	// X component figured by pythagorean theorem
	float adjacent = sqrt((distance*distance) - (opposite*opposite));
	return (Point((int)trunc(adjacent), (int)trunc(opposite)));
}

std::pair<double, double> PositionalMath::decPointFromPos(sensors_event_t *location)
{
	double lat = location->gps.latitude.degrees + location->gps.latitude.minutes / 60;
	if (location->gps.latitude.cardinal == 'S')
		lat *= -1;
	double lon = location->gps.longitude.degrees + location->gps.longitude.minutes / 60;
	if (location->gps.longitude.cardinal == 'W')
		lon *= -1;
	return std::make_pair(lat, lon);
}