#pragma once
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sstream>
#include "../../RobotLib/RobotLib.h"
#include "SensorLib.h"
#include "DeviceBase.h"

// Define for using OpenCV in grass detectors
#define HAS_OPENCV 1

class SensorBase : public DeviceBase
{
	public:
		SensorBase(RobotLib *robotLib);
		virtual ~SensorBase()
		{};
		virtual std::string getDeviceDescription()	
		{
		}
		virtual bool getEvent(sensors_event_t *event) 
		{
		}
		virtual sensors_type_t getSensorType()
		{			
		}
		double getTimestamp();			
		bool i2cWriteReg8(int fd, uint8_t reg, uint8_t val);
		bool i2cWriteReg16(int fd, uint8_t reg, uint16_t val);
		uint8_t i2cReadReg8(int fd, uint8_t reg);
		uint16_t i2cReadReg16(int fd, uint8_t reg);

	private:
		bool _autoRange;
	
	protected:
		RobotLib *robotLib;
};
