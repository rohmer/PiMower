#pragma once
#include "RobotLib.h"
#include "DeviceManager.h"
#include <vector>
#include <string>
#include <sstream>

class InertialGuidence
{
	public:
		InertialGuidence(RobotLib *robotLib);
	
	private:
		void initialize();
		RobotLib *robotLib;
		DeviceManager *deviceManager;
		bool hasCompass;
		bool hasDistance;
		DeviceEntry* distanceDevice;
		DeviceEntry* headingDevice;
};