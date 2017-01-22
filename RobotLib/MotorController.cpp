#include "MotorController.h"

MotorController::MotorController(RobotLib *robotLib, 
	uint8_t leftMotorChannel, 
	uint8_t rightMotorChannel, 
	uint8_t bladeChannel)
{
	this->robotLib = robotLib;
	this->leftMotorChannel = leftMotorChannel;
	this->rightMotorChannel = rightMotorChannel;
	this->bladeChannel = bladeChannel;
	pca9685 = reinterpret_cast<PCA9685 *>(robotLib->getDeviceManager()->getByName("PCA9685"));
	pca9685->pca9685PWMFreq(PCAFREQ);	
}

void MotorController::SetSpeed(int leftMotorSpeedPct, int rightMotorSpeedPct, int bladeSpeedPct)
{
	if (leftMotorSpeedPct < -100)
	{
		leftMotorSpeedPct = -100;
	}
	if (leftMotorSpeedPct > 100)
	{
		leftMotorSpeedPct = 100;
	}
	if (rightMotorSpeedPct < -100)
	{
		rightMotorSpeedPct = -100;
	}
	if (rightMotorSpeedPct > 100)
	{
		rightMotorSpeedPct = 100;
	}
	if (bladeSpeedPct < 0)
	{
		bladeSpeedPct = 0;
	}
	if (bladeSpeedPct > 100)
	{
		bladeSpeedPct = 100;
	}
	
	// Set the values to 1500 = stop, 1250=full rev, 1750=full forward
	int leftMotorSpeedAbs = MOTOR_STOP + ((leftMotorSpeedPct / 100) * 250);
	int rightMotorSpeedAbs = MOTOR_STOP + ((rightMotorSpeedPct/ 100) * 250);
	int bladeSpeedAbs = MOTOR_STOP + ((rightMotorSpeedPct / 100) * 250);
	pca9685->pca9685SetPin(leftMotorChannel, leftMotorSpeedPct);
	pca9685->pca9685SetPin(rightMotorChannel, rightMotorSpeedAbs);
}

void MotorController::AllStop()
{
	for (int a = 0; a <= 15; a++)
		pca9685->pca9685SetPin(a, MOTOR_STOP);
}
