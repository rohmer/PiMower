#pragma once 
#include <string>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include "../3rdParty/humblelogging-master/include/humblelogging/api.h"
#include "../3rdParty/RapidXML/rapidxml_print.hpp"
#include "Database.h"
#include "DeviceManager.h"
#include "LawnMap.h"
#include "Config.h"
#include "MotorController.h"
#include "guid.h"

class Database;
class DeviceManager;
class LawnMap;
class Config;
class MotorController;

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
		RobotLib();
		void Log(std::string message);
		void LogWarn(std::string message);
		void LogError(std::string message);	
		void LogException(std::exception &e);
	
		DeviceManager* getDeviceManager()
		{
			return deviceManager;
		}
		Database * getDatabase()
		{
			return database;
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
		Guid getSessionID()
		{
			return sessionGuid;
		}
	
	private:
		void initLog();
		bool checkEmulator();
		Database *database;
		DeviceManager *deviceManager;		
		bool emulator;
		LawnMap *mapObject;
		Config *config = NULL;
		MotorController *motorController=NULL;
		Guid sessionGuid;
};	