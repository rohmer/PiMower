#pragma once
#include "DeviceManager.h"
#include <thread>
#include <unistd.h>
#include "Database.h"
#include "../RobotController/SensorLib/LSM303_Magnetometer.h"
#include "../RobotController/SensorLib/LSM303_Accelerometer.h"

class GPSManager
{
	public:
		GPSManager(RobotLib *robotLib);
		void setPollingInterval(uint8_t pollingInterval);
		void setPollingAverage(uint8_t pollingAverage);
		~GPSManager();
		sensors_event_t* getLocation();
		int getHeading();

	private:
		void gpsThread();
		static void startManagerThread(GPSManager *gpsMgr);
		sensors_event_t *latestLocation, *headingEvt;
		DeviceManager *deviceManager;
		RobotLib *robotLib;
		LSM303_Magnetometer *lsmMag;
		LSM303_Accelerometer *lsmAccel;
		std::thread gpsManagerThread;
		Database *database;
		uint8_t pollingInt, pollingAvg;
		std::vector <sensors_gps_t> locationInfo;
		DeviceBase* gpsDevice;
		bool initialized = false;
		bool shutdown = false;
		bool magnetometerActive = false;
		bool accelerometerActive = false;
};
