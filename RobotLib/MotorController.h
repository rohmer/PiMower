#pragma once
#include "RobotLib.h"
#include "../RobotController/SensorLib/PCA9685.h"
#include "SensorManager.h"

#define MOTOR_MIN 1250
#define MOTOR_MAX 1750
#define MOTOR_STOP 1500
#define PCAFREQ 200

enum eTravelDirection
{
	FORWARD,
	BACKWARD,
	LEFT_TURN,
	RIGHT_TURN,
	STOPPED
};

class PCA9685;
class Config;

class MotorController
{
public:
	MotorController(RobotLib *robotLib,
		Config *config);

	void SetSpeed(int leftMotorSpeedPct, int rightMotorSpeedPct,int bladeSpeedPct);
	void SetSpeed(int leftMotorSpeecPct, int rightMotorSpeedPct);

	void AllStop();
	std::pair <int, int> currentDriveMotorRPM();
	eTravelDirection currentMotion();

private:
	RobotLib *robotLib;
	Config *config;
	uint8_t leftMotorChannel, rightMotorChannel, bladeChannel;
	PCA9685 *pca9685;
	uint8_t leftMotorSpeed, rightMotorSpeed, bladeSpeed;
};
