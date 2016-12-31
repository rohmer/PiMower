#include "GPIOLED.h"

GPIOLED::GPIOLED(RobotLib *robotLib) : DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	initialized = false;
	if (robotLib->getEmulator())
		return;

}

GPIOLED::GPIOLED(RobotLib *robotLib, std::string ledName, uint8_t triggerPin) : DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	ledMapping.emplace(std::make_pair(ledName, triggerPin));
	ledBehavior.emplace(std::make_pair(triggerPin, LED_BEHAVIOR_T::Off));
	shutdown = false;	
	startDriverThread(this);
	initialized = true;
	if (robotLib->getEmulator())
		return;

	pinMode(triggerPin, OUTPUT);
}

GPIOLED::~GPIOLED()
{
	shutdown = true;
}

void GPIOLED::startDriverThread(GPIOLED *gpioLED)
{
	gpioLED->driverThread();
}

void GPIOLED::driverThread()
{
	std::map<std::string, uint8_t>::iterator ledIterator;
	while (!shutdown)
	{
		for (ledIterator = ledMapping.begin(); ledIterator != ledMapping.end(); ledIterator++)
		{
			int pin = ledIterator->second;
			LED_BEHAVIOR_T behavior = ledBehavior[pin];
			if (behavior == LED_BEHAVIOR_T::Off)
			{
				if (digitalRead(pin) != LOW)
				{
					digitalWrite(pin, LOW);
				}
			}
			if (behavior == LED_BEHAVIOR_T::On)
			{
				if (digitalRead(pin) == LOW)
				{
					digitalWrite(pin, HIGH);
				}
			}
			if (behavior == LED_BEHAVIOR_T::Blink)
			{
				if (blinkCountdown[pin])
				{
					blinkCountdown[pin]--;
					if (blinkCountdown[pin] <= 0)
					{
						if (digitalRead(pin) == LOW)
						{
							digitalWrite(pin, HIGH);
						}
						else
						{
							digitalWrite(pin, LOW);
						}
					}
					if (!ledBlinkInterval[pin])
					{
						ledBlinkInterval[pin] = 2;
					}
					if (ledBlinkInterval[pin] > 10)
					{
						ledBlinkInterval[pin] = 10;
					}
					blinkCountdown[pin] = 500 / ledBlinkInterval[pin];
				}
			}
		}
		delayMicroseconds(1000);
	}
}

void GPIOLED::addLED(std::string ledName, uint8_t triggerPin)
{
	ledMapping.emplace(ledName, triggerPin);
	pinMode(triggerPin, OUTPUT);
	digitalWrite(triggerPin, LOW);
	ledBehavior.emplace(triggerPin, LED_BEHAVIOR_T::Off);
	if (!initialized)
	{
		shutdown = false;	
		startDriverThread(this);
		initialized = true;
	}
}

void GPIOLED::addLED(std::string ledName, uint8_t triggerPin, LED_BEHAVIOR_T behavior, uint8_t blinkInterval)
{
	ledMapping.emplace(ledName, triggerPin);
	pinMode(triggerPin, OUTPUT);
	if (behavior == LED_BEHAVIOR_T::Off)
	{
		digitalWrite(triggerPin, LOW);
		ledBehavior.emplace(triggerPin, LED_BEHAVIOR_T::Off);
		return;
	}
	if (behavior == LED_BEHAVIOR_T::On)
	{
		digitalWrite(triggerPin, HIGH);
		ledBehavior.emplace(triggerPin, LED_BEHAVIOR_T::On);
		return;
	}
	
	// Deal with blinking
	if (blinkInterval <= 0)
		blinkInterval = 1;
	if (blinkInterval > 10)
		blinkInterval = 10;
	ledBlinkInterval.emplace(triggerPin, blinkInterval);
	blinkCountdown.emplace(triggerPin, 500 / ledBlinkInterval[triggerPin]);
	digitalWrite(triggerPin, HIGH);
	ledBehavior.emplace(triggerPin, behavior);
	if (!initialized)
	{
		shutdown = false;	
		startDriverThread(this);
		initialized = true;
	}
}

void GPIOLED::setTriggerPin(std::string ledName, uint8_t triggerPin)
{
	if (ledMapping[ledName])
	{
		ledMapping[ledName] = triggerPin;
		return;
	}
	std::stringstream ss;
	ss << "LED Named: " << " ledName has not been created, use addLED first";
	robotLib->Log(ss.str());
}

uint8_t GPIOLED::getTriggerPin(std::string ledName)
{
	if (ledMapping[ledName])
	{
		return ledMapping[ledName];
	}
	std::stringstream ss;
	ss << "LED Named: " << " ledName has not been created, use addLED first";
	robotLib->Log(ss.str());
	return 0;
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(GPIOLED);