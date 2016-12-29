#pragma once
#include "DeviceManager.h"
#include <thread>
#include <unistd.h>
#include "Database.h"

class GPSManager
{
	public:
		GPSManager(RobotLib *robotLib);
		void setPollingInterval(uint8_t pollingInterval);
		void setPollingAverage(uint8_t pollingAverage);
		~GPSManager();
		sensors_gps_t getLocation();
	
	private:
		void gpsThread();
		static void startManagerThread(GPSManager *gpsMgr);
	
		DeviceManager *deviceManager;
		RobotLib *robotLib;
		std::thread gpsManagerThread;
		Database *database;
		uint8_t pollingInt, pollingAvg;	
		std::vector <sensors_gps_t> locationInfo;
		DeviceBase* gpsDevice;
		bool initialized = false;
		bool shutdown = false;
			
};
