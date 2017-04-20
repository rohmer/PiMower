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

/* Driver for a MCP23017 or MCP23008 i2c Port Expander */
class MCP230XX : public DeviceBase
{
	enum eChipType
	{
		mcp23017,
		mcp23008
	};

public:
	MCP230XX(RobotLib *robotLib);
	MCP230XX(RobotLib *robotLib, eChipType chipType);

	~MCP230XX();
	device_type_t getDeviceType() override
	{
		return device_type_t::DEVICETYPE_IO;
	}
	std::string getDeviceName() override
	{
		return "MCP230XX Port Expander Driver";
	}
	std::string getDeviceDescription() override
	{
		return "Driver for the MCP230XX Port Expander";
	}
	static device_status_t getDeviceStatus(RobotLib *robotLib)
	{
		// We cant really autodetect this
		return device_status_t::DEVICE_UNKNOWN;
	}
	void writePort(uint8_t portNumber, bool value);		// value: true=1, false=0
	bool readPort(uint8_t portNumber); // return: true=1, false=0
	std::vector<uint8_t> readPorts();

private:
	std::map<uint8_t, bool> portIO;		// TRUE = Input, FALSE = Output
};
