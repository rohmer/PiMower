#pragma once
#include <vector>
#include <sstream>
#include <errno.h>
#include <string.h>
#include <cmath>
#include "DeviceBase.h"
#include "SensorBase.h"

class LS7366R : public SensorBase
{
public:
	LS7366R(RobotLib *robotLib);
	LS7366R(RobotLib *robotLib, uint8_t slaveSelectEnc1, uint8_t slaveSelectEnc2);
	~LS7366R();
	device_type_t getDeviceType() override
	{
		return device_type_t::DEVICETYPE_SENSOR;
	}
	std::string getDeviceName() override
	{
		return "LS7366R";
	}
	std::string getDeviceDescription() override
	{
		return "LS7366R quadrature counter";
	}
	static device_status_t getDeviceStatus(RobotLib *robotLib);
	sensors_type_t getSensorType() override
	{
		return sensors_type_t::SENSOR_TYPE_COUNTER;
	}

	std::pair<long, long> readCounters();

private:
	void initialize(uint8_t slaveEncPin1, uint8_t slaveEncPin2);
	void clearCounter();
	void clearStatus();

	bool initialized = false;
	uint8_t slaveSelectEnc1, slaveSelectEnc2;
	uint8_t CLEAR_COUNTER = 0x20;
	uint8_t CLEAR_STATUS = 0x30;
	uint8_t READ_COUNTER = 0x60;
	uint8_t READ_STATUS = 0x70;
	uint8_t WRITE_MODE0 = 0x88;
	uint8_t WRITE_MODE1 = 0x90;
};