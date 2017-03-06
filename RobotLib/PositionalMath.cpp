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

double PositionalMath::inchesToLat(int inches)
{
	return (1 / (364734 * 12))*inches;
}

double PositionalMath::inchesToLong(int inches)
{
	return (1 / (249527 * 12))*inches;
}

double PositionalMath::latToInches(double lat)
{
	return lat*(364734 * 12);
}

double PositionalMath::longToInches(double lon)
{
	return lon*(249527 * 12);
}