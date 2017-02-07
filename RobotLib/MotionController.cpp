#include "MotionController.h"

MotionController::MotionController(RobotLib *robotLib, Config *config)
{
	this->robotLib = robotLib;
	this->config = config;
	gpsManager = new GPSManager(this->robotLib);
	sPWMController pwmConfig = config->getPWMControllerConfig();
	motorController = new MotorController(robotLib,
		config,
		pwmConfig.leftDriveChannel,
		pwmConfig.rightDriveChannel,
		pwmConfig.bladeChannel);
	proximityDet = new ObjectProximityDetection(robotLib, config);
	initialize();
}

MotionController::~MotionController()
{
	delete(gpsManager);
	delete(motorController);
	delete(odometer);
	if (location)
		delete(location);
}

void MotionController::initialize()
{
	// To start with lets get our location, velocity vectors and heading/pitch/roll
	location = new sensors_event_t();
	location=gpsManager->getLocation();	
	
	// Initialize the structures for the sensors
	for (int a = 0; a < config->getBumperSensors().size(); a++)
	{
		bumperSensors.push_back(config->getBumperSensors()[a]);	
		pinMode(config->getBumperSensors()[a].gpioPin, INPUT);
	}
	
	std::pair<uint8_t, uint8_t> encoderPins = config->getMotorEncoderPins();	
	odometer = new LS7366R(robotLib, encoderPins.first, encoderPins.second);
}

eMotionResult MotionController::rotateToHeading(int heading)
{
	motorController->SetSpeed(0, 0);
	int currentHeading = gpsManager->getHeading();
	if (currentHeading == -1)
	{
		robotLib->LogError("Gyro is unavailable, motion controls disabled");		
		motorController->AllStop();
	}
	bool clockwise = false;
	int potentialHeading = currentHeading + 180;	// Clockwise is +. counter -
	if (potentialHeading > 360)
	{
		if (heading > currentHeading && heading < 360)
			clockwise = true;
		else
			if (potentialHeading - 360 < 180)
				clockwise = true;
	}
	
	if (clockwise)
	{
		motorController->SetSpeed(config->getRotationRPM(), (-1)*config->getRotationRPM());
	}
	else
	{
		motorController->SetSpeed((-1)*config->getRotationRPM(), config->getRotationRPM());
	}

	//TODO: Set this to handle accceleration to speed over time
	while (currentHeading != heading)
	{
		// Ease the turn as we get closer to the heading
		if (abs(currentHeading - heading) < 10 && abs(currentHeading - heading) >5)
		{
			if (clockwise)
			{
				motorController->SetSpeed(config->getRotationRPM() * 0.5, (-1)*config->getRotationRPM() * 0.5);
			}
			else
			{
				motorController->SetSpeed((-1)*config->getRotationRPM() * 0.5, config->getRotationRPM() * 0.5);
			}
		}
		else
		{
			if (abs(currentHeading - heading) <= 5)
			{
				if (clockwise)
				{
					motorController->SetSpeed(config->getRotationRPM() * 0.25, (-1)*config->getRotationRPM() * 0.25);
				}
				else
				{
					motorController->SetSpeed((-1)*config->getRotationRPM() * 0.25, config->getRotationRPM() * 0.25);
				}	
			}
		
			else
			{
				if (clockwise)
				{
					motorController->SetSpeed(config->getRotationRPM() * 0.25, (-1)*config->getRotationRPM());
				}
				else
				{
					motorController->SetSpeed((-1)*config->getRotationRPM() * 0.25, config->getRotationRPM());
				}	
			}
		}
		for (int a = 0; a < bumperSensors.size(); a++)
		{
			if (digitalRead(bumperSensors[a].gpioPin) == HIGH)
			{
				std::stringstream ss;
				ss << "Collision detected on: ";
				if (bumperSensors[a].location == eSensorLocation::FRONT)
				{					
					ss << " Front Bumper";
					robotLib->Log(ss.str());
					motorController->SetSpeed(0, 0);
					return eMotionResult::BUMPER_FRONT;
				}
				else
				{
					ss << " Rear Bumper";
					robotLib->Log(ss.str());
					motorController->SetSpeed(0, 0);
					return eMotionResult::BUMPER_BACK;
				}
			}
		}
		delay(10);		
		currentHeading = gpsManager->getHeading();
	}
	// Stop motors, the next behavior will move us forward or reverse as needed
	motorController->SetSpeed(0, 0);
	
	// Store in DB the location info
	gpsManager->getLocation();
}

eMotionResult MotionController::travelDistance(int inchesToTravel,bool forward)
{
	// First find the odometer
	std::pair<long, long> initialOdVal = odometer->readCounters();
	// Need to add physical charistics node to config (Mainly the size of the tire)
	// to figure out what the travel distance will be.
	
	float wheelDiameter = config->getDriveWheelDiameter();
	float driveRatio = config->getDriveGearRatio();
	
	// So, now we find out how far each rotation of the motor translates to
	// linear travel
	// which is circumferance*driveRatio
	int distancePerRotation = wheelDiameter * 2 * 3.14159265*driveRatio;
	
	int revolutionsToTravel = std::round((float)inchesToTravel / distancePerRotation);
	
	// RevolutionsToTravel represents how many turns of the motors we need
	int rpm;
	if (forward)
		rpm = config->getForwardRPM();
	else
		rpm = config->getReverseRPM();
	int acceleration = config->getNormalAcceleation();
	int currentRPM = 0;
	long currentOdVal = initialOdVal.first;
	while (currentOdVal < (initialOdVal.first + revolutionsToTravel))
	{
		if (currentRPM < rpm)
		{
			currentRPM += rpm / acceleration;
			if (currentRPM > rpm)
				currentRPM = rpm;
		}
		if (forward)
			motorController->SetSpeed(currentRPM, currentRPM);
		else
			motorController->SetSpeed(currentRPM*-1, currentRPM*-1);
		for (int a = 0; a < bumperSensors.size(); a++)
		{
			if (digitalRead(bumperSensors[a].gpioPin) == HIGH)
			{
				std::stringstream ss;
				ss << "Collision detected on: ";
				if (bumperSensors[a].location == eSensorLocation::FRONT)
				{					
					ss << " Front Bumper";
					robotLib->Log(ss.str());
					motorController->SetSpeed(0, 0);
					return eMotionResult::BUMPER_FRONT;
				}
				else
				{
					ss << " Rear Bumper";
					robotLib->Log(ss.str());
					motorController->SetSpeed(0, 0);
					return eMotionResult::BUMPER_BACK;
				}
			}
		}
		
	}
	// Store in DB the location info
	gpsManager->getLocation();
}

float MotionController::inchesPerSecond()
{
	float wheelDiameter = config->getDriveWheelDiameter();
	float driveRatio = config->getDriveGearRatio();	
	float distancePerRotation = wheelDiameter * 2 * 3.14159265*driveRatio;
	return (distancePerRotation / 60);	
}