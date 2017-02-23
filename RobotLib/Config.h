#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "RobotLib.h"
#include "Database.h"
#include "../3rdParty/SQLiteC++/include/SQLiteCpp/Statement.h"

// Holds the configuration items for the robot

#define CONFIG_FILE "/usr/local/Robot/config.xml"

typedef enum min_log_level
{
	Debug,
	Warn,
	Critical,
	Exception		
} min_log_level_t;

struct sSpeedConfig
{
	int forwardRPM;
	int reverseRPM;
	int rotationRPM;
};

struct sPWMController
{
	int i2cChannel;
	int leftDriveChannel;
	int rightDriveChannel;
	int bladeChannel;
};

enum eSensorLocation
{
	FRONT,
	BACK,
	LEFT,
	RIGHT
};

struct sBumperSensor
{
	int gpioPin;
	eSensorLocation location;
};

struct sProximitySensors
{
	std::string name;
	int triggerPin;
	int echoPin;
	eSensorLocation location;
};

struct sArduinoHost
{
	int i2caddr;
	float proximityTollerance = 0.5;
	std::vector<sProximitySensors> proximitySensors;
};

class Config
{
public:
	Config()
	{
	}
	Config(RobotLib *robotLib);
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
	sPWMController getPWMControllerConfig()
	{
		return this->pwmController;
	}
	std::vector<sBumperSensor> getBumperSensors()
	{
		return this->bumperSensors;
	}
	std::pair<int, int> getMotorEncoderPins()
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
	min_log_level_t getLogLevel()
	{
		return minimumLoggingLevel;
	}
	uint8_t getMinimumBatteryPct()
	{
		return batteryChargePercentage;
	}
	
	unsigned int getMapScale()
	{
		return mapScale;
	}
	
	unsigned int getEncoderTicksPerRevolution()
	{
		return encoderTicksPerRevolution;
	}
	
	unsigned long getMessagedDBRetention()
	{
		return messagesToKeepInDB;
	}
	
private:
	unsigned int mapScale;
	sSpeedConfig normalOperationSpeed, objectDetectionSpeed;
	sPWMController pwmController;	
	RobotLib *robotLib;	
	bool validConfig = false;
	uint8_t leftEncoderPin, rightEncoderPin;	
	min_log_level_t minimumLoggingLevel;
	float driveWheelDiameter, driveGearRatio;
	unsigned int driveMotorMaxRPM;
	int normalAcceleration, rotationalAcceleration;
	bool readSensors(rapidxml::xml_node<> *rootNode);
	bool readPWMController(rapidxml::xml_node<> *pwm);
	bool readBumperSensor(rapidxml::xml_node<> *bumper);
	bool readArduinoHost(rapidxml::xml_node<> *arduinoHost);
	bool readSpeed(rapidxml::xml_node<> *speedNode);
	rapidxml::xml_node<> *createSpeedNode(rapidxml::xml_node<> *rootNode, rapidxml::xml_document<> &doc);
	void readLogLevel(rapidxml::xml_node<> *rootNode);
	bool readEncoder(rapidxml::xml_node<> *encoderNode);	
	bool readPhysical(rapidxml::xml_node<> *rootNode);	
	void writeConfiguration(rapidxml::xml_node<> *rootNode, 
		rapidxml::xml_document<> &doc,
		std::string cfgFile);		
	uint8_t getBatChargePct();
	
	void writeConfigDB();
	bool readConfigDB();
	
	unsigned long messagesToKeepInDB = 168;
	
	unsigned int errorLEDPin=-1;
	unsigned int encoderTicksPerRevolution;
	uint8_t batteryChargePercentage;
	std::vector<sBumperSensor> bumperSensors;
	sArduinoHost arduinoHost;
};