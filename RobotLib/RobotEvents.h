#pragma once
#include "Config.h"
#include "Database.h"
#include <Poco/Data/Session.h>

// Defines things that can happen to the robot, or the robot does
// Like change speed, heading, request move, complete move

enum eRobotEvent
{
	SPEED_CHANGE            = 1,
	HEADING_CHANGE          = 2,
	HEADING_CHANGE_COMPLETE = 3,
	REQUEST_MOVE            = 4,
	COMPLETE_MOVE           = 5,
	TURN_ON_BLADE           = 6,
	TURN_OFF_BLADE          = 7,
	BUMPER_ACTIVATED		= 8,
	PROXIMITY_DETECTION		= 9
};

class RobotEvents
{
public:
	static void speedChangeEvent(int previousSpeedLeft, int previousSpeedRight, int newSpeedLeft, int newSpeedRight);
	static void headingChangeEvent(float previousHeading, int newHeading);
	static void headingChangedEvent(int newHeading);
	static void requestMoveEvent(int distanceInInches, bool forward);
	static void completeMoveEvent();
	static void turnOnBladeEvent();
	static void turnOffBladeEvent();
	static void bumperActivatedEvent(eSensorLocation bumperLocation);
	static void proximityActivatedEvent(eSensorLocation proximityLocation, float distanceInInches);

private:
	static std::string getUUID();
};
