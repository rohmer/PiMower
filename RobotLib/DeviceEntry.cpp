#include "DeviceEntry.h"

DeviceEntry::DeviceEntry(RobotLib *robotLib, DeviceBase *device)
{
	this->robotLib = robotLib;
	this->device = device;
}

device_status_t DeviceEntry::getDeviceStatus(RobotLib* robotLib)
{
	return device->getDeviceStatus(robotLib);
}