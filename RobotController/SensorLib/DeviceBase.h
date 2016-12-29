#pragma once
#include <string>
#include "DeviceLib.h"
#include "SensorLib.h"
//#include "../../RobotLib/RobotLib.h"

class RobotLib;
class DeviceBase
{
	public:
		DeviceBase(RobotLib *robotLib)
		{
			this->robotLib = robotLib;
		}
		virtual ~DeviceBase()
		{};
		virtual std::string getDeviceName()
		{
		}
		virtual device_type_t getDeviceType()
		{};	
		device_status_t getDeviceStatus(RobotLib *robotLib)
		{
		}
		virtual std::string getDeviceDescription()
		{
		}
		virtual bool getEvent(sensors_event_t *event) 
		{
		}
	
	protected: 
		RobotLib *robotLib;
		device_status_t deviceStatus;
};
