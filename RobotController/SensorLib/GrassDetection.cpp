#include "GrassDetector.h"
#ifdef HAS_OPENCV
GrassDetection::GrassDetection(RobotLib *robotLib) :
	SensorBase(robotLib)
{
	initalized = init();
}

bool GrassDetection::init()
{
	// First find out if we have an imaging sensor
	std::vector<DeviceEntry*> imgDevices = robotLib->getDeviceManager()->getByCap(sensors_type_t::SENSOR_TYPE_IMAGING);
	if (imgDevices.size() == 0)
	{
		robotLib->LogError("Cannot initalize grass detections, no imaging sensor available");
		return false;
	}
	
	device_status_t imageSensorStatus = device_status_t::DEVICE_UNKNOWN;
	for (int a=0; a<imgDevices.size(); a++)
	{
		if (!imageSensor)
		{			
			imageSensor = reinterpret_cast<SensorBase *>(imgDevices[a]);	
			if (!imageSensor)
			{
				std::stringstream ss;
				ss << "Failed to cast device type: " << imgDevices[a]->getDeviceType() << " as sensor";
				robotLib->Log(ss.str());
			}
			else
			{
				if (imgDevices[a]->getDeviceStatus(robotLib) == device_status_t::DEVICE_AVAILABLE)
				{
					std::stringstream ss;
					ss << "Using device type: " << imgDevices[a]->getDeviceType() << " as imaging sensor";
					robotLib->Log(ss.str());
					imageSensorStatus = DEVICE_AVAILABLE;
				}
				else
				{
					if (imgDevices[a]->getDeviceStatus(robotLib) == device_status_t::DEVICE_CONNECTED || imgDevices[a]->getDeviceStatus(robotLib) == device_status_t::DEVICE_CONNECTED)
					{					
						std::stringstream ss;
						ss << "Using device type: " << imgDevices[a]->getDeviceType() << " as imaging sensor, device needs configuration";
						robotLib->LogWarn(ss.str());
						imageSensorStatus = imgDevices[a]->getDeviceStatus(robotLib);
					}
				}
			}
		}
	}
	if (!imageSensor)
	{
		robotLib->LogError("No Imaging Sensor was detected");
		return false;
	}
	
	// Does it need initalization?
	if (imageSensorStatus != DEVICE_AVAILABLE)
	{
		robotLib->Log("Imaging device requires inialization before it can be used");		
	}
	return true;
}
#endif