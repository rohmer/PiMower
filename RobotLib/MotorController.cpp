#include "MotorController.h"

MotorController::MotorController(RobotLib *robotLib, 
	Config *config)	
{
	this->robotLib = robotLib;
	this->config = config;
	this->leftMotorChannel = config->getPWMControllerConfig().leftDriveChannel;;
	this->rightMotorChannel = config->getPWMControllerConfig().rightDriveChannel;
	this->bladeChannel = config->getPWMControllerConfig().bladeChannel;
	pca9685 = reinterpret_cast<PCA9685 *>(robotLib->getDeviceManager()->getByName("PCA9685"));	
	pca9685->pca9685PWMFreq(PCAFREQ);	
	AllStop();
	leftMotorSpeed = 0;
	rightMotorSpeed = 0; 
	bladeSpeed = 0;
}

eTravelDirection MotorController::currentMotion()
{
	if (leftMotorSpeed == 0 && rightMotorSpeed == 0)	
		return eTravelDirection::STOPPED;
	if (leftMotorSpeed == rightMotorSpeed && leftMotorSpeed > 0)
		return eTravelDirection::FORWARD;
	if (leftMotorSpeed == rightMotorSpeed && leftMotorSpeed < 0)
		return eTravelDirection::BACKWARD;
	if (leftMotorSpeed > 0 && leftMotorSpeed > rightMotorSpeed)
		return eTravelDirection::RIGHT_TURN;
	if (rightMotorSpeed > 0 && leftMotorSpeed < rightMotorSpeed)
		return eTravelDirection::LEFT_TURN;
	return eTravelDirection::STOPPED;
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
	leftMotorSpeed = leftMotorSpeedPct;
	rightMotorSpeed = rightMotorSpeedPct;
	bladeSpeed = bladeSpeedPct;
	
	// Set the values to 1500 = stop, 1250=full rev, 1750=full forward
	int leftMotorSpeedAbs = MOTOR_STOP + ((leftMotorSpeedPct / 100) * 250);
	int rightMotorSpeedAbs = MOTOR_STOP + ((rightMotorSpeedPct/ 100) * 250);
	int bladeSpeedAbs = MOTOR_STOP + ((bladeSpeedPct / 100) * 250);
	pca9685->pca9685SetPin(leftMotorChannel, leftMotorSpeedPct);
	pca9685->pca9685SetPin(rightMotorChannel, rightMotorSpeedAbs);
	pca9685->pca9685SetPin(bladeChannel, bladeSpeedAbs);
}

void MotorController::SetSpeed(int leftMotorSpeedPct, int rightMotorSpeedPct)
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
	leftMotorSpeed = leftMotorSpeedPct;
	rightMotorSpeed = rightMotorSpeedPct;
	
	// Set the values to 1500 = stop, 1250=full rev, 1750=full forward
	int leftMotorSpeedAbs = MOTOR_STOP + ((leftMotorSpeedPct / 100) * 250);
	int rightMotorSpeedAbs = MOTOR_STOP + ((rightMotorSpeedPct / 100) * 250);
	pca9685->pca9685SetPin(leftMotorChannel, leftMotorSpeedAbs);
	pca9685->pca9685SetPin(rightMotorChannel, rightMotorSpeedAbs);	
}

void MotorController::AllStop()
{
	for (int a = 0; a <= 15; a++)
		pca9685->pca9685SetPin(a, MOTOR_STOP);
}

std::pair<int,int> MotorController::currentDriveMotorRPM()
{
	int leftRPM = config->getMaxDriveRPM()*config->getDriveGearRatio()*(leftMotorSpeed / 100);
	int rightRPM = config->getMaxDriveRPM()*config->getDriveGearRatio()*(rightMotorSpeed / 100);
	return std::make_pair(leftRPM, rightRPM);
}