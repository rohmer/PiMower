#pragma once
#include "SensorLib.h"
#include "SensorBase.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPiI2C.h"
#include "LSM303.h"
#include <stdio.h>
#include <sstream>
#include <cstring>
#include <chrono>
#include <thread>
#include "../../RobotLib/DeviceRegistry.h"

class LSM303_Accelerometer : public SensorBase
{
public:
	LSM303_Accelerometer(RobotLib *rl);
	void enableAutoRange(bool enabled);
	std::string getDeviceName() override;
	bool getEvent(sensors_event_t*) override;
	sensors_type_t getSensorType() override;
	void getSensor(sensor_t *sensor);	
	~LSM303_Accelerometer();
	void calibrate();	
	std::string getDeviceDescription() override;
	device_type_t getDeviceType() override
	{
		return device_type_t::DEVICETYPE_SENSOR;
	}	
	static device_status_t getDeviceStatus(RobotLib *robotLib);
	
private:
	void read();
	void init();
	static int i2cfd_Accel;	
	static bool accelInit, accelAttached;
	bool autoRange;	
	lsm303AccelData raw; 
};
