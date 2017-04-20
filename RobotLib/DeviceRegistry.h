#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../RobotController/SensorLib/DeviceBase.h"

#define LOW 0
#define HIGH 1

template<class T> DeviceBase* device_factory(RobotLib *robotLib)
{
	return new T(robotLib);
}

typedef DeviceBase* (*device_creator)(RobotLib*);

class DeviceRegistry
{
	public:
		typedef std::vector<device_creator>::iterator it;
		static DeviceRegistry& get();
		void add(device_creator);
		it begin();
		it end();

	private:
		std::vector <device_creator> m_devices;
};

class DeviceRegistration
{
	public:
		DeviceRegistration(device_creator);
};

#define AUTO_REGISTER_DEVICE(DeviceBase) DeviceRegistration _device_registration_ ## DeviceBase(&device_factory<DeviceBase>);