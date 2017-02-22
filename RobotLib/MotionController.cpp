#include "MotionController.h"
#include "Point.h"
#include "PositionalMath.h"

// TODO: Add mapping to this
MotionController::MotionController(RobotLib *robotLib)
{
	this->robotLib = robotLib;
	this->config = robotLib->getConfig();
	gpsManager = new GPSManager(this->robotLib);
	sPWMController pwmConfig = config->getPWMControllerConfig();
	motorController = robotLib->getMotorController();
	fmSensor = new FusedMotionSensor(robotLib);
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
	float wheelDiameter = config->getDriveWheelDiameter();
	float driveRatio = config->getDriveGearRatio();
	// So, now we find out how far each rotation of the motor translates to
	// linear travel
	// which is circumferance*driveRatio
	distancePerWheelRotation = wheelDiameter * 2 * 3.14159265*driveRatio;

}

void MotionController::allStop()
{
	motorController->AllStop();
}

void MotionController::motionStop()
{
	motorController->SetSpeed(0, 0);
}

eMotionResult MotionController::rotateToHeading(int heading)
{
	motorController->SetSpeed(0, 0);
	Point originalPoint = Point(robotLib->getCurrentXLoc(), robotLib->getCurrentYLoc());
	
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
		fmsResult sensorResult = fmSensor->getCurrentState();
		if (sensorResult.result == fmsResultType::HARD_RESULT)
		{
			std::stringstream ss;
			ss << "Collision detected on: ";
			if (sensorResult.location == eSensorLocation::FRONT)
			{					
				ss << " Front Bumper";
				robotLib->Log(ss.str());
				motorController->SetSpeed(0, 0);				
				robotLib->getMap()->setNode(originalPoint.x, originalPoint.y, map_node_t::BLOCK_BUMP, PositionalMath::decPointFromPos(location));				
				return eMotionResult::BUMPER_FRONT;
			}
			else
			{
				ss << " Rear Bumper";
				robotLib->Log(ss.str());
				motorController->SetSpeed(0, 0);
				robotLib->getMap()->setNode(originalPoint.x, originalPoint.y, map_node_t::BLOCK_BUMP, PositionalMath::decPointFromPos(location));								
				return eMotionResult::BUMPER_BACK;
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

eMotionResult MotionController::travelDistance(int inchesToTravel, bool forward, bool cutting)
{	
	// First find the odometer
	std::pair<long, long> initialOdVal = odometer->readCounters();
	Point originalPoint = Point(robotLib->getCurrentXLoc(), robotLib->getCurrentYLoc());
	Point originalPointAbs = Point(originalPoint.x*config->getMapScale() + (config->getMapScale() * 0.5), 
		originalPoint.y*config->getMapScale() + (config->getMapScale() * 0.5));
	
	int revolutionsToTravel = std::round((float)inchesToTravel / distancePerWheelRotation)*config->getEncoderTicksPerRevolution();
	// We will check the map every time we travel 12 inches to see if we are in a different
	// map sector (Defined as 3x3 feet)
	// RevolutionsToTravel represents how many turns of the motors we need
	
	int heading = gpsManager->getHeading();
	
	int rpm;
	if (forward)
		rpm = config->getForwardRPM();
	else
		rpm = (-1)*config->getReverseRPM();
	int acceleration = config->getNormalAcceleation();
	long currentOdVal = initialOdVal.first;
	location = gpsManager->getLocation();
	int initialRPM = 0;
	int rpmCounter = 0;
	// If we are going in reverse our heading is 180 degrees opposite
	if (!forward)
	{
		heading += 180;
		if (heading >= 360)
			heading -= 360;
	}
	// Now travel loop
	// TODO: Find out the # encoder ticks per full wheel rotation
	while (currentOdVal < (initialOdVal.first + revolutionsToTravel))
	{
		currentOdVal=odometer->readCounters().first;
			
		float distanceTraveled = (currentOdVal - initialOdVal.first)*distancePerWheelRotation/config->getEncoderTicksPerRevolution();
		fmsResult sensorResult = fmSensor->getCurrentState();
		
		// First a hard result, i.e. bumper
		if (sensorResult.result == fmsResultType::HARD_RESULT)
		{
			// Stop
			motorController->SetSpeed(0, 0);
			location=gpsManager->getLocation();
			Point currentPoint = getCurrentMapLocation(originalPoint, heading, distanceTraveled);
			robotLib->getMap()->setNode(currentPoint.x, currentPoint.y, map_node_t::BLOCK_BUMP, PositionalMath::decPointFromPos(location));
			if (sensorResult.location == eSensorLocation::BACK)
				return eMotionResult::BUMPER_BACK;
			return eMotionResult::BUMPER_FRONT;
			
		}
		
		// Now an object detected result
		if (sensorResult.result == fmsResultType::OBJECT_DETECTED)
		{
			// Set the RPM based on direction
			if (forward)
				rpm = config->getObjDetForwardRPM();
			else
				rpm = config->getObjDetReverseRPM();
			rpmCounter = 0;
		}
		
		// We found a non-grass section
		if (sensorResult.result == fmsResultType::NOT_GRASS)
		{
			// First mark map
			Point currentPoint = getCurrentMapLocation(originalPoint, heading, distanceTraveled);
			robotLib->getMap()->setNode(currentPoint.x, currentPoint.y, map_node_t::BLOCK_NOT_GRASS, PositionalMath::decPointFromPos(location));
			// Now if we are cutting, stop and return value
			// TODO: Might want to stop blade
			if (cutting)
			{
				motorController->SetSpeed(0, 0);
				return eMotionResult::NON_GRASS;
			}
			// Otherwise we are traveling and traveling over non-grass is ok
		}
		if (sensorResult.result == fmsResultType::CLEAR)
		{
			// Mark map
			Point currentPoint = getCurrentMapLocation(originalPoint, heading, distanceTraveled);
			robotLib->getMap()->setNode(currentPoint.x, currentPoint.y, map_node_t::BLOCK_NOT_GRASS, PositionalMath::decPointFromPos(location));			
			if (forward)
			{				
				rpm = config->getForwardRPM();
				initialRPM = motorController->currentDriveMotorRPM().first;
			}
			else
			{				
				rpm = config->getReverseRPM();
				initialRPM = motorController->currentDriveMotorRPM().first;
			}
		}
		
		// Now set RPM based on acceleration (And maybe deceleration)
		if (rpm > motorController->currentDriveMotorRPM().first)
		{
			int rpmIncrease = (rpm - initialRPM) / acceleration;
			int setRPM = initialRPM + acceleration*rpmCounter;
			rpmCounter++;
			if (setRPM > rpm)
				setRPM = rpm;
			motorController->SetSpeed(setRPM, setRPM);
		}
		delay(50);
	}	
	// we got there! :)
	// Stop
	motorController->SetSpeed(0, 0);
	return eMotionResult::SUCCESS;
}

Point MotionController::getCurrentMapLocation(Point initialPoint, int heading, float distanceTraveledInches)
{
	Point pt = PositionalMath::getPointByAngleDist(initialPoint, heading, distanceTraveledInches);
	// That gave us # of inches we traveled from the original point, now we need to 
	// convert that to map squares
	int mapSqInch=config->getMapScale();
	if (pt.x < (mapSqInch / 2)) 
		pt.x = 0;
	else
		pt.x = trunc((pt.y - mapSqInch / 2) / mapSqInch) + 1;
	if (pt.y < (mapSqInch / 2)) 
		pt.y = 0;
	else
		pt.y = trunc((pt.y - mapSqInch / 2) / mapSqInch) + 1;
	pt.x += initialPoint.x;
	pt.y += initialPoint.y;
	return pt;
}

float MotionController::inchesPerSecond()
{
	float wheelDiameter = config->getDriveWheelDiameter();
	float driveRatio = config->getDriveGearRatio();	
	float distancePerRotation = wheelDiameter * 2 * 3.14159265*driveRatio;
	return (distancePerRotation / 60);	
}