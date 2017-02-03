#pragma once
#include "RobotLib.h"
#include "GPSManager.h"
#include "Configuration.h"
#include "MotorController.h"
#include "../3rdParty/wiringPi/wiringPi/wiringPi.h"
#include "MotorController.h"
#include "../RobotController/SensorLib/ArduinoSensorHost.h"
#include "ObjectProximityDetection.h"

enum eMotionResult
{
	SUCCESS,			// Did whatever was asked of the controller
	BUMPER_FRONT,		// Bumper hit something and we stopped before
	BUMPER_BACK,		// we got that far
	ERROR				// Some sort of catastrophic error
};

class MotionController
{
	MotionController(RobotLib *robotLib, Configuration *config);
	~MotionController();
	eMotionResult rotateToHeading(int heading);
	eMotionResult travelDistance(int inchesToTravel, bool forward);
	float inchesPerSecond();
	
private:
	std::vector <bumperSensor_s> bumperSensors;
	void initialize();
	GPSManager *gpsManager;
	RobotLib *robotLib;
	Configuration *config;
	MotorController *motorController;
	ObjectProximityDetection *proximityDet;
	LS7366R *odometer;
	bool errorState = false;
	sensors_event_t *location;
};
