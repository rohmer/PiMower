#include "GPSManager.h"

GPSManager::GPSManager(RobotLib *robotLib)
{
	this->robotLib = robotLib;
	this->deviceManager = deviceManager;
	setPollingInterval(2);					// Every 2 seconds
	setPollingAverage(3);					// Average last 3
	deviceManager = robotLib->getDeviceManager();
	std::vector<DeviceEntry*> locDevices = deviceManager->getByCap(sensors_type_t::SENSOR_TYPE_GPS);
	if (locDevices.size() == 0)
	{
		initialized = false;
		robotLib->LogError("No GPS device detected");
		return;
	}
	gpsDevice = locDevices[0]->getDevice();	
	gpsManagerThread=std::thread (startManagerThread,this);
}

void GPSManager::setPollingInterval(uint8_t pollingInterval)
{
	this->pollingInt = pollingInterval;
}

void GPSManager::setPollingAverage(uint8_t pollingAverage)
{
	this->pollingAvg = pollingAverage;
}

void GPSManager::gpsThread()
{
	robotLib->Log("Starting gpsThread()");
	sensors_event_t *evt = new sensors_event_t();	
	nmea_position latitude;
	nmea_position longitude;
	while (!shutdown)
	{
		if (gpsDevice->getEvent(evt))
		{
			locationInfo.insert(locationInfo.begin(), evt->gps);
			while (locationInfo.size() > pollingAvg)
				locationInfo.pop_back();
		
		// Average, newest being the highest level
			int intTotal = 0;
			double altTotal = 0;		
			latitude.degrees = 0;
			longitude.degrees = 0;
			latitude.minutes = 0;
			longitude.minutes = 0;
			for (int a = 0; a < locationInfo.size(); a++)
			{
				int mult = locationInfo.size() - a + 1;
				altTotal += (locationInfo[a].altitude*mult);
				latitude.degrees += (locationInfo[a].latitude.degrees*mult);
				latitude.minutes += (locationInfo[a].latitude.minutes*mult);
				longitude.degrees += (locationInfo[a].longitude.degrees*mult);
				longitude.minutes += (locationInfo[a].longitude.minutes*mult);			
				intTotal += mult;
			}
			longitude.cardinal = locationInfo[0].longitude.cardinal;
			latitude.cardinal = locationInfo[0].latitude.cardinal;
			latitude.degrees /= intTotal;
			longitude.degrees /= intTotal;
			latitude.minutes /= intTotal;
			longitude.minutes /= intTotal;
			altTotal /= intTotal;
			locationInfo[0].altitude = altTotal;
			locationInfo[0].latitude = latitude;
			locationInfo[0].longitude = longitude;
			
			if (!robotLib->getDatabase()->insertGPSEvent(locationInfo[0]))
			{
				robotLib->LogWarn("Failed to insert GPS Event");
			}
		} 
		sleep(pollingInt);
	}
	delete(evt);
}

sensors_gps_t GPSManager::getLocation()
{
	if (locationInfo.size() > 0)
		return locationInfo[0];
}

void GPSManager::startManagerThread(GPSManager *gpsMgr)
{
	gpsMgr->gpsThread();
}

GPSManager::~GPSManager()
{
	shutdown = true;
	gpsManagerThread.join();	
}