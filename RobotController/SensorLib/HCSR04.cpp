#include "HCSR04.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPi.h"

/* HC-SR04 Ultrasonic Range Finder */

HCSR04::HCSR04(RobotLib *robotLib) :
	SensorBase(robotLib)
{	
	initialized = false;	
	inputPin = 0;
	triggerPin = 0;
	shutdown = false;
}

HCSR04::HCSR04(RobotLib *robotLib, uint8_t triggerPin, uint8_t inputPin)
	: SensorBase(robotLib)
{
	if (robotLib->getEmulator())
	{
		return;
	}
	this->triggerPin = triggerPin;
	this->inputPin = inputPin;
	pinMode(triggerPin, OUTPUT);
	pinMode(inputPin, INPUT);
	// Default to 400cm
	setMaxDistanceCM(400);	
	addSensor(inputPin);
	shutdown = false;
	initialized = true;
}

HCSR04::HCSR04(RobotLib *robotLib,
	uint8_t triggerPin,
	uint8_t inputPin, 
	bool backgroundPoling,
	uint16_t pollingInterval) :
		SensorBase(robotLib)
{	
	if (robotLib->getEmulator())
	{
		return;
	}
	this->triggerPin = triggerPin;
	this->inputPin = inputPin;
	pinMode(triggerPin, OUTPUT);
	pinMode(inputPin, OUTPUT);
	// Default to 400cm
	setMaxDistanceCM(400);	
	this->pollingInterval = pollingInterval;
	this->shutdown = backgroundPolling;
	initialized = true;
	if (backgroundPolling)
	{
		pollingThread = std::thread(startPollingThread, this);
	}
}

void HCSR04::setBackgroundPolling(bool enabled)
{
	if (enabled && !backgroundPolling)
	{
		shutdown = false;
		backgroundPolling = true;
		pollingThread = std::thread(startPollingThread, this);
		return;
	}
	if (!enabled)
	{
		backgroundPolling = false;
		shutdown = true;
		pollingThread.join();
	}
}

HCSR04::~HCSR04()
{
	shutdown = true;
	if (backgroundPolling)
	{
		// Join so we dont shutdown unitl the thread is shutdown
		pollingThread.join();
	}
}

void HCSR04::startPollingThread(HCSR04 *hcsr04)
{
	hcsr04->bgPollingThread();
}

void HCSR04::setMaxDistanceCM(uint16_t centimeters)
{
	maxDistance = centimeters * 58;
}

void HCSR04::setMaxDistanceInches(uint16_t inches)
{
	maxDistance = inches * 147.32;
}

void HCSR04::pollDevice()
{
	if (!initialized)
	{
		std::stringstream ss;
		ss << "HC-SR04 is not initialized, inputPin=" << inputPin << " triggerPin=" << triggerPin << " both must be set and > 0";
		return;
	}
	
	int a = 0;
	while (a < sensorResult.size())
	{
		delay(10);
		digitalWrite(triggerPin, 1);
		delay(10);
		digitalWrite(triggerPin, 0);
	
		/*long now = micros();
		volatile long startTime = 0, endTime = 0;
		while (digitalRead(inputPin) == 0 && micros() - now < maxDistance && !shutdown)
		{
			startTime = micros();
			while (digitalRead(inputPin) == 1 && !shutdown)
			{		
			}
			
			endTime = micros();
		}
		*/
		long travelTimeUsec = 0; // = endTime - startTime;
		if (travelTimeUsec != 0)
		{
			sensorResult[a] = 10000*((travelTimeUsec / 1000000.0) * 340.29) / 2;		
		}
		a++;
	} 
}

bool HCSR04::getEvent(sensors_event_t *event)
{
	if (!initialized)
	{
		std::stringstream ss;
		ss << "HC-SR04 is not initialized, inputPin=" << inputPin << " triggerPin=" << triggerPin << " both must be set and > 0";
		robotLib->Log(ss.str());
		return false;
	}
	
	if (sensorResult.size() == 0)
	{
		robotLib->LogWarn("No sensors defined, define one first with addSensor()");
		return false;
	}
	if(!backgroundPolling)
		pollDevice();
		
	event->distanceCM = sensorResult[0];
	event->distanceIN = sensorResult[0]/2.54;
	
	return true;
}

bool HCSR04::getEvent(int sensorNum, sensors_event_t *event)
{
	if (!initialized)
	{
		std::stringstream ss;
		ss << "HC-SR04 is not initialized, inputPin=" << inputPin << " triggerPin=" << triggerPin << " both must be set and > 0";
		robotLib->Log(ss.str());
		return false;
	}
	
	if (sensorResult.size() == 0)
	{
		robotLib->LogWarn("No sensors defined, define one first with addSensor()");
		return false;
	}
	if (sensorResult.size() < sensorNum)
	{
		std::stringstream ss;
		ss << sensorResult.size() << " sensors defined, " << sensorNum << " was requested";
		robotLib->LogWarn(ss.str());
		return false;
	}
	if (!backgroundPolling)
		pollDevice();
		
	event->distanceCM = sensorResult[sensorNum];
	event->distanceIN = sensorResult[sensorNum] / 2.54;
	
	return true;
}

void HCSR04::bgPollingThread()
{
	while (!shutdown)
	{
		pollDevice();
		delay(pollingInterval);
	}	
}

void HCSR04::setTriggerPin(uint8_t triggerPin)
{
	this->triggerPin = triggerPin;
	pinMode(triggerPin, OUTPUT);
}

uint8_t HCSR04::getTriggerPin()
{
	return triggerPin;
}

void HCSR04::addSensor(uint8_t inputPin)
{
	bool contains = false;
	for (int a = 0; a < sensorResult.size(); a++)
		if (sensorResult[a] == inputPin)
			contains = true;
	if (contains)
	{
		std::stringstream ss;
		ss << "Input pin: " << inputPin << " previously defined, not redefining";
		robotLib->LogWarn(ss.str());
		return;
	}
	sensorResult.emplace_back(inputPin);
	pinMode(inputPin, INPUT);
}

uint8_t HCSR04::getInputPin()
{
	return inputPin;
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(HCSR04);