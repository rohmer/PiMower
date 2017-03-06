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
#include "RobotEvents.h"
#include "Point.h"

enum eMotionResult
{
	SUCCESS,			// Did whatever was asked of the controller
	BUMPER_FRONT,		// Bumper hit something and we stopped before
	BUMPER_BACK,		// we got that far
	NON_GRASS,			// We were cutting and found some non-grass
	ERROR				// Some sort of catastrophic error
};

class MotionController
{
public:
	MotionController(RobotLib *robotLib);
	~MotionController();
	eMotionResult rotateToHeading(int heading);
	eMotionResult travelDistance(int inchesToTravel, bool forward, bool cutting);
	float inchesPerSecond();
	void allStop();
	void motionStop();
	
private:
	Point getCurrentMapLocation(Point initialPoint, int heading, float distanceTraveledInches);
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
	int distancePerWheelRotation;
};
