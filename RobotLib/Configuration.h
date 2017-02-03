#pragma once	
#include "RobotLib.h"
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../RobotDaemon/RobotDaemon.h"

// Holds the configuration items for the robot

#define CONFIG_FILE "/usr/local/Robot/config.xml"

struct speedConfig_struct
{
	int forwardRPM;
	int reverseRPM;
	int rotationRPM;
};

struct pwmController_s
{
	uint8_t i2cChannel;
	uint8_t leftDriveChannel;
	uint8_t rightDriveChannel;
	uint8_t bladeChannel;
};

enum eSensorLocation
{
	FRONT,
	BACK,
	LEFT,
	RIGHT
};

struct bumperSensor_s
{
	uint8_t gpioPin;
	eSensorLocation location;
};

struct sProximitySensors
{
	std::string name;
	uint8_t triggerPin;
	uint8_t echoPin;
	eSensorLocation location;
};

struct sArduinoHost
{
	uint8_t i2caddr;
	float proximityTollerance=0.5;
	std::vector<sProximitySensors> proximitySensors;
};

class Configuration
{
	public:
		Configuration(RobotLib *robotLib);
		bool getConfig();
		bool getConfig(std::string cfgFile);
		int getForwardRPM()
		{
			return normalOperationSpeed.forwardRPM;
		}
		int getReverseRPM()
		{
			return normalOperationSpeed.reverseRPM;
		}
		int getRotationRPM()
		{
			return normalOperationSpeed.rotationRPM;
		}
		int getObjDetForwardRPM()
		{
			return objectDetectionSpeed.forwardRPM;
		}
		int getObjDetReverseRPM()
		{
			return objectDetectionSpeed.reverseRPM;
		}
		int getObjDetRotationRPM()
		{
			return normalOperationSpeed.rotationRPM;
		}
		pwmController_s getPWMControllerConfig()
		{
			return this->pwmController;
		}
		std::vector<bumperSensor_s> getBumperSensors()
		{
			return this->bumperSensors;
		}
		std::pair<uint8_t, uint8_t> getMotorEncoderPins()
		{
			return std::make_pair(leftEncoderPin, rightEncoderPin);
		}
		float getDriveWheelDiameter()
		{
			return driveWheelDiameter;
		}
		float getDriveGearRatio()
		{
			return driveGearRatio;
		}
		int getNormalAcceleation()
		{
			return normalAcceleration;
		}
		int getRotationalAcceleration()
		{
			return rotationalAcceleration;
		}		
		sArduinoHost getArduinoHost()
		{
			return arduinoHost;
		}
		unsigned int getMaxDriveRPM()
		{
			return driveMotorMaxRPM;
		}
	
	private:
		speedConfig_struct normalOperationSpeed, objectDetectionSpeed;
		pwmController_s pwmController;	
		RobotLib *robotLib;	
		bool validConfig = false;
		uint8_t leftEncoderPin, rightEncoderPin;
		min_log_level_t minimumLoggingLevel;
		float driveWheelDiameter, driveGearRatio;
		unsigned int driveMotorMaxRPM;
		int normalAcceleration, rotationalAcceleration;
		bool readSensors(rapidxml::xml_node<> *rootNode);
		bool readSpeed(rapidxml::xml_node<> *rootNode);
		bool readLogLevel(rapidxml::xml_node<> *rootNode);
		bool readPhysical(rapidxml::xml_node<> *rootNode);
		void setDefaultSpeed();	
		int setPctValue(int val);
		void writeConfiguration();		
		std::vector<bumperSensor_s> bumperSensors;
		sArduinoHost arduinoHost;
};