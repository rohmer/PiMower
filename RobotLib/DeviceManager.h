#pragma once
#include "RobotLib.h"
#include <vector>
#include <sstream>
#include "../RobotController/SensorLib/DeviceLib.h"
#include "../RobotController/SensorLib/SensorLib.h"
#include "DeviceEntry.h"
#include <memory>
#include <stdio.h>
#include <unistd.h>
#include <map>

class DeviceEntry;

// Handles the management and detection of connected devices
class DeviceManager
{		
	public:		
		DeviceManager(RobotLib &robotLib);
		~DeviceManager();
		std::vector<DeviceEntry*> getByType(device_type_t deviceType);
		std::vector<DeviceEntry*> getByCap(sensors_type_t capability);
		DeviceEntry* getByName(std::string name);
		static uint8_t getI2CFD(uint8_t dev);
		static uint8_t getSerialFD(std::string dev, int baud);
		static uint8_t getSPIFD(uint8_t dev, int speed);
	
	private:
		std::vector<DeviceEntry*> devices;	
		RobotLib *robotLib;
		void initialize();
		static std::map <std::string,uint8_t> serialfd;
		static std::map<uint8_t, uint8_t> i2cfd, spifd;

};