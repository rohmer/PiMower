#include "ObjectProximityDetection.h"

ObjectProximityDetection::ObjectProximityDetection(RobotLib *robotLib, Config *config)
{
	if (robotLib->getEmulator())
		return;
	this->robotLib = robotLib;
	this->config = config;
	arduinoHost = new ArduinoSensorHost(robotLib, config->getArduinoHost().i2caddr);
	for (int a = 0; a < config->getArduinoHost().proximitySensors.size(); a++)
	{		
		sProximity psensor;
		psensor.sensor = config->getArduinoHost().proximitySensors[a];
		arduinoHost->addProximitySensor(psensor.sensor.triggerPin, psensor.sensor.echoPin);
		psensor.lastCheck = -1;
		psensor.lastDistanceRaw = -1;
		proximitySensors.emplace(psensor.sensor.echoPin, psensor);
	}
}

// Return is if the object is moving and closer or further
// second is the raw distance in inches
// This returns the values for the CLOSEST object
std::pair<ObjectProximityDetection::sProximityResult, int> ObjectProximityDetection::scanProximity()
{
	std::vector<ArduinoSensorHost::sSensorReturn> sensorValues=arduinoHost->getSensorValues();
	std::map<uint8_t, sProximity>::iterator it;
	int shortestDistanceInches = 9999;
	sProximityResult result;
	result.motionResult = NO_OBJECT;		
	for (int a = 0; a < sensorValues.size(); a++)
	{
		it = proximitySensors.find(sensorValues[a].proximityValue.echoPin);
		if (it != proximitySensors.end())
		{			
			sProximity sensor = proximitySensors[sensorValues[a].proximityValue.echoPin];		
			if (sensor.lastCheck == -1 || sensor.lastDistanceRaw == -1)
			{
				sensor.lastCheck = sensorValues[a].proximityValue.pingTime;
				sensor.lastDistanceRaw = sensorValues[a].proximityValue.rawRange;
			}
			else
			{
				if (sensorValues[a].proximityValue.rawRange != 0)
				{
					// Convert to inches
					int inches = round(sensorValues[a].proximityValue.rawRange / 146);
					if (inches < shortestDistanceInches)
					{
						result.motionResult = analyzeMotion(sensor, sensorValues[a]);
						result.direction = sensor.sensor.location;
					}					
				}
				sensor.lastCheck = sensorValues[a].proximityValue.pingTime;
				sensor.lastDistanceRaw = sensorValues[a].proximityValue.rawRange;
			}
		}
	}
	return std::make_pair(result, shortestDistanceInches);
}

// Mower speed is inches/sec + = forward, - = backward
// Return is if the object is moving and closer or further
// second is the raw distance in inches
// This returns the values for the CLOSEST object
std::pair<ObjectProximityDetection::sProximityResult, int> ObjectProximityDetection::scanProximity(eSensorLocation dir)
{
	std::vector<ArduinoSensorHost::sSensorReturn> sensorValues = arduinoHost->getSensorValues();
	std::map<uint8_t, sProximity>::iterator it;
	int shortestDistanceInches = 9999;
	sProximityResult result;
	result.motionResult = NO_OBJECT;
	
	for (int a = 0; a < sensorValues.size(); a++)
	{
		it = proximitySensors.find(sensorValues[a].proximityValue.echoPin);
		if (it != proximitySensors.end())
		{			
			sProximity sensor = proximitySensors[sensorValues[a].proximityValue.echoPin];		
			if (sensor.sensor.location == dir)
			{
				if (sensor.lastCheck == -1 || sensor.lastDistanceRaw == -1)
				{
					sensor.lastCheck = sensorValues[a].proximityValue.pingTime;
					sensor.lastDistanceRaw = sensorValues[a].proximityValue.rawRange;
				}
				else
				{
					if (sensorValues[a].proximityValue.rawRange != 0)
					{
						// Convert to inches
						int inches = round(sensorValues[a].proximityValue.rawRange / 146);
						if (inches < shortestDistanceInches)
						{
							result.motionResult = analyzeMotion(sensor, sensorValues[a]);
							result.direction = sensor.sensor.location;
						}					
					}
				}
			}
			sensor.lastCheck = sensorValues[a].proximityValue.pingTime;
			sensor.lastDistanceRaw = sensorValues[a].proximityValue.rawRange;			
		}
	}
	return std::make_pair(result, shortestDistanceInches);
}
// Need to think about this, need the time of each of the pings actually.  Might have
// to send that from the arduino

ObjectProximityDetection::eObjectMotionResult 
	ObjectProximityDetection::analyzeMotion(sProximity lastReading, 
	ArduinoSensorHost::sSensorReturn currentReading)
{
	float proximityTollerance = config->getArduinoHost().proximityTollerance;
	int tolleranceFactor;
	if (lastReading.lastDistanceRaw > currentReading.proximityValue.rawRange)
	{
		tolleranceFactor = lastReading.lastDistanceRaw*(proximityTollerance/100);
	}
	else
	{
		tolleranceFactor = currentReading.proximityValue.rawRange*(proximityTollerance/100);
	}
	long tolleranceRange = round(lastReading.lastDistanceRaw*(tolleranceFactor));
	if(currentReading.proximityValue.rawRange<lastReading.lastCheck+tolleranceRange ||
		currentReading.proximityValue.rawRange>lastReading.lastCheck-tolleranceRange)
	{
		return OBJECT_STATIONARY;
	}
	if (currentReading.proximityValue.rawRange < lastReading.lastCheck)
	{
		return OBJECT_CLOSING;
	}
	return OBJECT_RETREATING;	
}