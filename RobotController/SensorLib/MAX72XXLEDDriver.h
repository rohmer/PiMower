#pragma once
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
#include "wiringPiSPI.h"
#include "DeviceBase.h"
#include <map>
#include <utility>
#include "MAX72XXDefines.h"

/* Driver for a MAXIM 72XX Driver chip running LEDs */
class MAX72XXLEDDriver : public DeviceBase
{
public:
	typedef enum LEDBehavior
	{
		Off,
		On,
		Blink
	} LED_BEHAVIOR_T;
	MAX72XXLEDDriver(RobotLib *robotLib);
	MAX72XXLEDDriver(RobotLib *robotLib, int8_t SID, int8_t SCLK, int8_t A0, int8_t RST, int8_t CS, uint8_t spiChannel);
	~MAX72XXLEDDriver();

	void initialize(int8_t SID,
		int8_t SCLK,
		int8_t A0,
		int8_t RST,
		int8_t CS,
		uint8_t spiChannel);

	device_type_t getDeviceType() override
	{
		return device_type_t::DEVICETYPE_OUTPUT;
	}
	std::string getDeviceName() override
	{
		return "Maxim 72XX LED Driver";
	}
	std::string getDeviceDescription() override
	{
		return "Driver for LEDs running on a Maxim 72XX SPI multiplexer";
	}
	static device_status_t getDeviceStatus(RobotLib *robotLib)
	{
		// We cant really autodetect this
		return device_status_t::DEVICE_UNKNOWN;
	}
	void addLED(std::string ledName, uint8_t row, uint8_t col);					// Adds an LED for polling
	void addLED(std::string ledName,
		uint8_t row,
		uint8_t col,
		LED_BEHAVIOR_T behavior,
		uint8_t blinkIterval);
	void clear();
	void controlLED(uint8_t row, uint8_t col, bool powerMode);
private:
	uint8_t sid, sclk, a0, rst, cs;
	bool status[64];
	uint8_t spiFD;
	void startDriverThread(MAX72XXLEDDriver *maxDriver);
	void driverThread();
	bool initialized;
	bool shutdown = false;
	std::map<std::string, std::pair <uint8_t, uint8_t>> ledMapping;
	std::map<std::pair <uint8_t, uint8_t>, LED_BEHAVIOR_T> ledBehavior;
	std::map<std::pair <uint8_t, uint8_t>, uint8_t> ledBlinkInterval;
	std::map<std::pair <uint8_t, uint8_t>, uint8_t> blinkCountdown;
};