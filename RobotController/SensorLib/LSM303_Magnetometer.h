#pragma once
#include "SensorLib.h"
#include "SensorBase.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPiI2C.h"
#include "LSM303.h"
#include <stdio.h>
#include <sstream>
#include <cstring>
#include <thread>
#include <chrono>
#include <cmath>
#include "../../RobotLib/DeviceRegistry.h"

class LSM303_Magnetometer : public SensorBase
{
	public:
		LSM303_Magnetometer(RobotLib *rl);
		void setMagGain(lsm303MagGain gain);
		void enableAutoRange(bool enabled);
		void setMagRate(lsm303MagRate rate);
		std::string getDeviceName() override;
		bool getEvent(sensors_event_t*) override;		
		~LSM303_Magnetometer();
		sensors_type_t getSensorType() override;
		void getSensor(sensor_t *sensor);
		void calibrate();
		std::string getDeviceDescription() override;
		device_type_t getDeviceType() override
		{
			return device_type_t::DEVICETYPE_SENSOR;
		}
		static device_status_t getDeviceStatus(RobotLib *robotLib);
		
	private:
		void read();
		static int i2cfd_Mag;		
		static bool magInit, magAttached;
		bool autoRange;
		lsm303MagGain   magGain;
		lsm303MagData raw;        // Last read magnetometer data will be available here
};
