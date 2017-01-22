#include "MotionController.h"

MotionController::MotionController(RobotLib *robotLib)
{
	this->robotLib = robotLib;
	gpsManager = new GPSManager(this->robotLib);
	initialize();
}

void MotionController::initialize()
{
	// To start with lets get our location, velocity vectors and heading/pitch/roll
	sensors_event_t *location = new sensors_event_t();
	location=gpsManager->getLocation();	
}