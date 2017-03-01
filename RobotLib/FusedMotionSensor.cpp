#include "FusedMotionSensor.h"
#include "../3rdParty/wiringPi/wiringPi/wiringPi.h"

FusedMotionSensor::FusedMotionSensor(RobotLib *robotLib)
{
	this->robotLib = robotLib;
	// Lets get all our Sensors
	config = robotLib->getConfig();
	opd = new ObjectProximityDetection(robotLib, config);
	bumperSensors=config->getBumperSensors();
	piCamera = new PiCamera(robotLib);
	
	motionSensorThread = std::thread(startSensorThread, this);
	imagingThread = std::thread(startImageThread, this);
	motorController = robotLib->getMotorController();
}

FusedMotionSensor::~FusedMotionSensor()
{
	this->shutdown = true;
	robotLib->Log("Shutting down FusedMotionSensor");
	try
	{
		motionSensorThread.join();
	}
	catch (std::system_error &e)
	{
		robotLib->LogException(e);
	}
	robotLib->Log("FusedMotionSensor shutdown");	
}

void FusedMotionSensor::startSensorThread(FusedMotionSensor *fms)
{
	fms->sensorManagerThread();	
}

void FusedMotionSensor::startImageThread(FusedMotionSensor *fms)
{
	fms->imageManagerThread();
}

void FusedMotionSensor::imageManagerThread()
{
	robotLib->Log("Starting imageManagerThread");
	while (!shutdown)
	{
		currentOnGrass=piCamera->isGrass();
		delay(200);
	}
	robotLib->Log("imageManagerThread shutdown");
}

std::pair<bool, eSensorLocation> FusedMotionSensor::checkBumpers()
{
	std::pair<bool, eSensorLocation> returnValue;
	for (int a = 0; a < bumperSensors.size(); a++)
	{
		if (digitalRead(bumperSensors[a].gpioPin) == HIGH)
		{
			return std::make_pair(true, bumperSensors[a].location);
		}
	}
	return std::make_pair(false, eSensorLocation::FRONT);		// Location doesnt matter, as we didnt fire
}

// TODO: This mess cries out for a statemachine
void FusedMotionSensor::sensorManagerThread()
{
	robotLib->Log("Starting sensorManagerThread");
	while (!shutdown)
	{
		if (!currentOnGrass)
		{
			currentResult.resultTime = time(NULL);
			currentResult.location = eSensorLocation::FRONT;
			currentResult.result = fmsResultType::NOT_GRASS;  // We arent on grass
		}
		std::pair<bool, eSensorLocation> bumperReturn = checkBumpers();
		if (bumperReturn.first)
		{
			// A bumper hit
			currentResult.resultTime = time(NULL);
			currentResult.location = bumperReturn.second;
			currentResult.result = fmsResultType::HARD_RESULT;		// Bumpers only fire on hard results			
		}
		else
		{
			// Need to check proximity sensors			
			std::pair <ObjectProximityDetection::sProximityResult,int> opsResult=opd->scanProximity();
			ObjectProximityDetection::sProximityResult spr = opsResult.first;				
			if (spr.motionResult != ObjectProximityDetection::eObjectMotionResult::NO_OBJECT)
			{
				currentResult.result = fmsResultType::CLEAR;
				currentResult.resultTime = time(NULL);
			}
			else
			{
				// If an object is getting closer, no matter what the direction notate it				
				if (spr.motionResult == ObjectProximityDetection::eObjectMotionResult::OBJECT_CLOSING)
				{
					currentResult.result = fmsResultType::OBJECT_DETECTED;
					currentResult.resultTime = time(NULL);		
					currentResult.location = spr.direction;
				}
				else
				{
					// We are moving forward and its in front of us, and its inside 96 inches
					if (spr.direction == eSensorLocation::FRONT && motorController->currentMotion() == eTravelDirection::FORWARD && opsResult.second < 96)
					{
						currentResult.result = fmsResultType::OBJECT_DETECTED;						
						currentResult.resultTime = time(NULL);
						currentResult.location = spr.direction;
					}
					else
					{
					// We are moving backward and its behind us, and its inside 60 inches
						if (spr.direction == eSensorLocation::BACK && motorController->currentMotion() == eTravelDirection::BACKWARD && opsResult.second < 60)
						{
							currentResult.result = fmsResultType::OBJECT_DETECTED;
							currentResult.resultTime = time(NULL);
							currentResult.location = spr.direction;										
						}
						else
						{
							// We are inside of 3 feet from an object, lets consider it detected
							if (opsResult.second < 36)
							{
								currentResult.result = fmsResultType::OBJECT_DETECTED;
								currentResult.resultTime = time(NULL);
								currentResult.location = spr.direction;
							}
							else
							{
								// All other situations are clear
								currentResult.result = fmsResultType::CLEAR;
								currentResult.resultTime = time(NULL);
								currentResult.location = spr.direction;
							}														
						} 
					}
				}
			}
		}
		
		
		delay(50);
	}
}