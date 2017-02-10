#pragma once
#include "RobotLib.h"
#include "ObjectProximityDetection.h"
#include "../RobotController/SensorLib/PiCamera.h"
#include <thread>
#include <vector>
#include <utility>
#include <time.h>

// This class combines bumper, proximity and optical grass detection to return
// where we are.

// This is spawned as a thread and polled for the latest values

enum fmsResultType
{
	NOT_GRASS,				// We arent on grass according to optical sensor
	HARD_RESULT,			// We hit something, we are not on grass, etc
	OBJECT_DETECTED,		// We noticed something via proximity, but arent at it yet
	CLEAR					// No issues, on grass, nothing in range
};

struct fmsResult
{
	fmsResultType result;
	eSensorLocation location;	
	time_t resultTime;
};

class FusedMotionSensor
{
public:
	FusedMotionSensor(RobotLib *robotLib);
	~FusedMotionSensor();
	fmsResult getCurrentState()
	{
		return currentResult;
	}
	
private:	
	RobotLib *robotLib;
	Config *config;
	std::thread motionSensorThread;
	std::thread imagingThread;
	bool shutdown = false;
	PiCamera *piCamera;	
	ObjectProximityDetection *opd;
	std::vector <sBumperSensor> bumperSensors;
	MotorController *motorController;
	bool currentOnGrass;
	
	void sensorManagerThread();	
	void imageManagerThread();
	static void startSensorThread(FusedMotionSensor *fms);
	static void startImageThread(FusedMotionSensor *fms);
	std::pair<bool, eSensorLocation> checkBumpers();
	fmsResult currentResult;
};


