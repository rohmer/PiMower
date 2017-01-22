#pragma once	
#include "RobotLib.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../RobotDaemon/RobotDaemon.h"

// Holds the configuration items for the robot

#define CONFIG_FILE "/usr/local/Robot/config.xml"

typedef enum
{
	unknown				= 0,
	triggerPin			= 1,
	analogInputPin		= 2,
	digitalInputPin		= 3
} pin_type_t;

typedef enum 
{
	Unknown				= 0,
	SonorProximityGPIO	= 1,	
	Color				= 2,
	Camera				= 3,
	Gyroscope			= 4,
	GPS					= 5,
	Switch				= 6,
	Accelerometer		= 7,
	Moisture			= 8,
	SonorProximityI2C	= 9
} sensor_type_t;

struct pin_struct
{
	pin_type_t	pinType;
	uint8_t		pinNumber;
	bool		sharedPin;
};

struct sensor_struct
{
	sensor_type_t sensorType;
	int id;
	std::string name;;
	std::vector<pin_struct> pins;
};

class Configuration
{
	public:
		Configuration(RobotLib *robotLib);
		bool getConfig();
	
	private:
		RobotLib *robotLib;	
		std::vector<sensor_struct> sensors;
		bool validConfig = false;
		min_log_level_t minimumLoggingLevel;
	
		void initSensors();
};