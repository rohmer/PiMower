#pragma once
#pragma once
#include "SensorLib.h"
#include "SensorBase.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPiI2C.h"
#include <stdio.h>
#include <sstream>
#include <cstring>
#include <chrono>
#include <thread>
#include "../../RobotLib/DeviceRegistry.h"

class BQ34Z100G1: public SensorBase
{
public:
	BQ34Z100G1(RobotLib *rl);
	BQ34Z100G1(RobotLib *rl, uint8_t i2cAddress);
	std::string getDeviceName() override;
	bool getEvent(sensors_event_t *event) override;
	sensors_type_t getSensorType() override;	
	std::string getDeviceDescription() override;
	device_type_t getDeviceType() override
	{
		return device_type_t::DEVICETYPE_SENSOR;
	}	
	static device_status_t getDeviceStatus(RobotLib *robotLib);
	
	uint8_t getPctRemaining();
	
private:
	int i2cfd;	
	bool initialized;		
};
