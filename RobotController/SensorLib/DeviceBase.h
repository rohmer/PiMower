#pragma once
#include <string>
#include "DeviceLib.h"
#include "SensorLib.h"
//#include "../../RobotLib/RobotLib.h"

typedef enum DEVICE_TYPE
{
	SENSOR,
	DEVICE
} DEVICE_TYPE_T;

class RobotLib;
class DeviceBase
{
public:
	DeviceBase(RobotLib *robotLib, DEVICE_TYPE_T deviceType)
	{
		this->robotLib = robotLib;
		this->deviceType = deviceType;
	}
	virtual ~DeviceBase()
	{}
	;
	virtual std::string getDeviceName()
	{
	}
	virtual device_type_t getDeviceType()
	{}
	;
	device_status_t getDeviceStatus(RobotLib *robotLib)
	{
	}
	virtual std::string getDeviceDescription()
	{
	}
	virtual bool getEvent(sensors_event_t *event)
	{
	}
	DEVICE_TYPE_T deviceType;

protected:
	RobotLib *robotLib;
	device_status_t deviceStatus;
};
