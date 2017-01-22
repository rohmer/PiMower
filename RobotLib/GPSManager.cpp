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
	lsmMag = reinterpret_cast<LSM303_Magnetometer *>(deviceManager->getByName("LSM303_Magnetometer"));
	lsmAccel = reinterpret_cast<LSM303_Accelerometer *>(deviceManager->getByName("LSM303_Accelerometer"));
	if (lsmMag)
	{
		magnetometerActive = true;
	}
	if (lsmAccel)
	{
		accelerometerActive = true;
	}	
	initialized = true;
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
	if (!latestLocation)
	{
		latestLocation = new sensors_event_t();
	}
	nmea_position latitude;
	nmea_position longitude;
	while (!shutdown)
	{
		if (gpsDevice->getEvent(latestLocation))
		{
			locationInfo.insert(locationInfo.begin(), latestLocation->gps);
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
			latestLocation->gps = locationInfo[0];
			
			if (lsmAccel)
			{
				lsmAccel->getEvent(latestLocation);
			}
			if (lsmMag)
			{
				lsmMag->getEvent(latestLocation);
			}
			if (!robotLib->getDatabase()->insertPositionEvent(latestLocation))
			{
				robotLib->LogWarn("Failed to insert GPS Event");
			}			
		} 
		sleep(pollingInt);
	}
	delete(latestLocation);
}

sensors_event_t* GPSManager::getLocation()
{
	if (locationInfo.size() > 0)
	{
		return latestLocation;	
	}
	return NULL;
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