#pragma once
#include "RobotLib.h"
#include "../RobotController/SensorLib/ArduinoSensorHost.h"
#include <time.h>
#include <map>
#include "Config.h"

// ObjectProximityDetection:
// Detects if an object is near, or is an object is getting closer (Moving towards
// the mower (A dog or person walking up to it))

class ObjectProximityDetection 
{
public:
	enum eObjectMotionResult
	{
		NO_OBJECT         = 0,
		OBJECT_RETREATING = 1,
		OBJECT_STATIONARY = 2,		
		OBJECT_CLOSING    = 3		
	};
	
	
	ObjectProximityDetection(RobotLib *robotLib, Config *config);
	std::pair<eObjectMotionResult, int> scanProximity();
	std::pair<eObjectMotionResult, int> scanProximity(eSensorLocation dir);
private:
	Config *config;
	struct sProximity
	{
		sProximitySensors sensor;
		time_t lastCheck;
		long lastDistanceRaw;
	};
	RobotLib *robotLib;
	ArduinoSensorHost *arduinoHost;
	std::map<uint8_t, sProximity> proximitySensors; // Key is the echoPin
	time_t lastCheck;
	eObjectMotionResult analyzeMotion(sProximity lastReading, ArduinoSensorHost::sSensorReturn currentReading);
};