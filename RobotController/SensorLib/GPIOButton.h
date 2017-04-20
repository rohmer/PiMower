#pragma once
#include <vector>
#include <sstream>
#include <errno.h>
#include <string.h>
#include <cmath>
#include <thread>
#include "SensorBase.h"
#include "../../RobotLib/DeviceRegistry.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPi.h"
#include <vector>
#include "wiringPi.h"
#include "DeviceBase.h"
#include <map>
#include <utility>

/* Driver for A simple button(s) connected to GPIO  */
class GPIOButton : public DeviceBase
{
public:
	GPIOButton(RobotLib *robotLib);
	std::vector<std::string> getButtonsPressed();
	device_type_t getDeviceType() override
	{
		return device_type_t::DEVICETYPE_INPUT;
	}
	std::string getDeviceName() override
	{
		return "GPIO Button Driver";
	}
	std::string getDeviceDescription() override
	{
		return "Driver for Buttons running on GPIO";
	}
	static device_status_t getDeviceStatus(RobotLib *robotLib)
	{
		// We cant really autodetect this
		return device_status_t::DEVICE_UNKNOWN;
	}
	void addButton(uint8_t pinNumber, std::string buttonName);

private:
	std::map<uint8_t, std::string> buttons;
};

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(GPIOButton);