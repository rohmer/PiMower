#pragma once
//#include "RobotLib.h"
#include "../RobotController/SensorLib/SensorBase.h"

class DeviceBase;

class DeviceEntry
{
	public:
		DeviceEntry(RobotLib *robotLib, DeviceBase *device);
		virtual device_type_t getDeviceType()
		{
		}
		device_status_t getDeviceStatus(RobotLib *robotLib);				
		DeviceBase *getDevice() 
		{
			return device;
		}
	private:
		DeviceBase *device;
		RobotLib *robotLib;	
};
