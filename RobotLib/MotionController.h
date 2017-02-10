#pragma once
#include "RobotLib.h"
#include "GPSManager.h"
#include "Config.h"
#include "MotorController.h"
#include "../3rdParty/wiringPi/wiringPi/wiringPi.h"
#include "MotorController.h"
#include "../RobotController/SensorLib/ArduinoSensorHost.h"
#include "ObjectProximityDetection.h"
#include "../RobotController/SensorLib/LS7366R.h"
#include "FusedMotionSensor.h"

enum eMotionResult
{
	SUCCESS,			// Did whatever was asked of the controller
	BUMPER_FRONT,		// Bumper hit something and we stopped before
	BUMPER_BACK,		// we got that far
	ERROR				// Some sort of catastrophic error
};

class MotionController
{
	MotionController(RobotLib *robotLib, Config *config);
	~MotionController();
	eMotionResult rotateToHeading(int heading);
	eMotionResult travelDistance(int inchesToTravel, bool forward);
	float inchesPerSecond();
	
private:
	std::vector <sBumperSensor> bumperSensors;
	void initialize();
	GPSManager *gpsManager;
	RobotLib *robotLib;
	Config *config;
	MotorController *motorController;
	FusedMotionSensor *fmSensor;
	LS7366R *odometer;
	bool errorState = false;
	sensors_event_t *location;
};
