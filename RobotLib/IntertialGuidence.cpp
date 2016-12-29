#include "InertialGuidence.h"

InertialGuidence::InertialGuidence(RobotLib *robotLib)
{
	this->robotLib = robotLib;
	this->deviceManager = robotLib->getDeviceManager();
}

void InertialGuidence::initialize()
{
	std::vector<DeviceEntry *> distance = deviceManager->getByCap(sensors_type_t::SENSOR_TYPE_LINEAR_DISTANCE);
	if (distance.size() > 0)
	{
		bool availDevice = false;
		for (int a = 0; a < distance.size(); a++)
		{
			if (distance[a]->getDeviceStatus(robotLib) == device_status_t::DEVICE_AVAILABLE)
			{
				distanceDevice = distance[a];
				availDevice = true;
			}
		}
		if (!availDevice)
		{
			for (int a = 0; a < distance.size(); a++)
			{
				if (distance[a]->getDeviceStatus(robotLib) == device_status_t::DEVICE_CONNECTED)
				{
					distanceDevice = distance[a];
					availDevice = true;
				}
			}	
		}
		if (!availDevice)
			distanceDevice = distance[0];
#if DEBUG
		std::stringstream ss;
		ss << "Distance device being used: " << distanceDevice->getDevice()->getDeviceName() << " status is: " << distanceDevice->getDevice()->getDeviceStatus(robotLib);
		robotLib->Log(ss.str());
#endif
		if (!distanceDevice)
			robotLib->LogWarn("Inertial guidence will be unavailable, no distance device detected");
		
	}
}