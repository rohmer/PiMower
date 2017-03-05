#pragma once 
#include <string>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <Poco/Message.h>
#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>
#include <Poco/FileChannel.h>
#include <Poco/SplitterChannel.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/Data/Statement.h>
#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Data/SQLite/Utility.h>
#include "../3rdParty/RapidXML/rapidxml_print.hpp"
#include "../3rdParty/wiringPi/wiringPi/wiringPi.h"
#include "Database.h"
#include "DeviceManager.h"
#include "LawnMap.h"
#include "Config.h"
#include "MotorController.h"
#include "guid.h"

class DeviceManager;
class LawnMap;
class Config;
class MotorController;
class GPSManager;

// If running on a preempt kernel (Suggested) uncomment
#define PREEMPT_RT

// Defined if we are going to be running in test mode
// This will have the various managers get simulated data
#define SIMULATION

// Library class used throughout RobotLib
// Includes things like the logger
class RobotLib
{
public:			
	static RobotLib &getInstance()
	{
		static RobotLib instance;
		return instance;
	}
	void Log(std::string message);
	void LogWarn(std::string message);
	void LogError(std::string message);	
	void LogException(std::exception &e);
	void LogBehaviorError(std::string message, std::string fromBehavior);
	
	DeviceManager* getDeviceManager()
	{
		return deviceManager;
	}
	bool getEmulator()
	{
		return emulator;
	}
	~RobotLib();
		
	LawnMap *getMap();	
	void setLogLevel(int logLevel);
	Config *getConfig();
	MotorController *getMotorController();
	void setSessionID();
	static Guid getSessionID()
	{
		return sessionGuid;
	}
	GPSManager *getGPSManager();	
	int getCurrentXLoc()
	{
		return currentLocation.first;
	}
	int getCurrentYLoc()
	{
		return currentLocation.second;
	}
	void setCurrentXLoc(int loc)
	{
		currentLocation.first = loc;
	}
	void setCurrentYLoc(int loc)
	{
		currentLocation.second = loc;
	}
	
	void setError(std::string errorMessage, std::string fromBehavior);
	void clearError();
		
private:	
	RobotLib();
	
	struct dbLogMsg
	{
		std::string timeStr;
		std::string msg;
		int severity;
		std::string sessionID;
	};
	
	int clearCounter = 0;
	
	void logDB(std::string message, int severity);
	void initLog();
	bool checkEmulator();
	DeviceManager *deviceManager;		
	bool emulator;
	LawnMap *mapObject;
	Config *config = NULL;
	MotorController *motorController = NULL;
	static Guid sessionGuid;	
	void dbLogger();
	bool shutdown = false;
	std::pair <int, int> currentLocation;
	int minLogLevel = 1;
	
public:
	RobotLib(RobotLib const&)		= delete;
	void operator=(RobotLib const&)	= delete;
};