#pragma once
#include <vector>
#include <sstream>
#include <errno.h>
#include <string.h>
#include <cmath>
#include <thread>
#include "SensorBase.h"
#include "../../RobotLib/DeviceRegistry.h"
#include "SensorBase.h"
#include <vector>
#include "wiringPi.h"
#include "DeviceBase.h"
#include <map>
#include <utility>

/* Driver for A simple LED(s) connected to GPIO  */
class GPIOLED : public DeviceBase
{
public:
	typedef enum LEDBehavior
	{
		Off,
		On,
		Blink
	} LED_BEHAVIOR_T;
	GPIOLED(RobotLib *robotLib);
	GPIOLED(RobotLib *robotLib, std::string ledName, uint8_t triggerPin);
	~GPIOLED();	
	device_type_t getDeviceType() override
	{
		return device_type_t::DEVICETYPE_OUTPUT;
	}
	std::string getDeviceName() override
	{
		return "GPIO LED Driver";
	}
	std::string getDeviceDescription() override
	{
		return "Driver for LEDs running on GPIO";
	}
	static device_status_t getDeviceStatus(RobotLib *robotLib) 
	{
		// We cant really autodetect this
		return device_status_t::DEVICE_UNKNOWN;
	}		
	void setTriggerPin(std::string ledName, uint8_t triggerPin);
	uint8_t getTriggerPin(std::string ledName);
	void addLED(std::string ledName, uint8_t triggerPin);					// Adds an LED for polling
	void addLED(std::string ledName, uint8_t triggerPin, LED_BEHAVIOR_T behavior, uint8_t blinkIterval);
			
private:
	void startDriverThread(GPIOLED *gpioLed);
	void driverThread();
	uint8_t triggerPin;
	bool initialized;
	bool shutdown = false;
	uint16_t pollingInterval;
	std::thread pollingThread;		
	std::map<std::string, uint8_t> ledMapping;
	std::map<uint8_t, LED_BEHAVIOR_T> ledBehavior;
	std::map<uint8_t, uint8_t> ledBlinkInterval;
	std::map<uint8_t, uint8_t> blinkCountdown;
};