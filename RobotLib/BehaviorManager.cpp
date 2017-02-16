#include "BehaviorManager.h"
#include "../RobotController/SensorLib/BQ34Z100G1.h"
#include "../RobotController/SensorLib/INA219.h"

BehaviorManager::BehaviorManager(RobotLib *robotLib)
{
	// Set current state to charging
	currentState = STATE_CHARGING;
	
	// Create our scheudler
	scheduler = new Scheduler(robotLib);
	// Precreate all of the behaviors
	Behavior *charging = (Behavior *)new Charging(robotLib,scheduler);
	behaviors.emplace(STATE_CHARGING, charging);
#ifdef DEBUG
	for (std::map<states_t, Behavior *>::iterator it = behaviors.begin(); it != behaviors.end(); it++)
	{
		std::stringstream ss;
		ss << "Created Behavior: " << it->second->getBehaviorName();
		robotLib->Log(ss.str());
	}
#endif
	
	// Initialize all our devices we will need
	BQ34Z100G1 *batterySensor = new BQ34Z100G1(robotLib);
	robotLib->getDeviceManager()->addDevice((DeviceBase *) batterySensor);
	INA219 *currentSensor = new INA219(robotLib);
	robotLib->getDeviceManager()->addDevice((DeviceBase *) currentSensor);
	
	mowingSessions = 0;
	wasInMowingPeriod = false;	
}

BehaviorManager::~BehaviorManager()
{
	for (std::map<states_t, Behavior *>::iterator it = behaviors.begin(); it != behaviors.end(); it++)
	{
#ifdef DEBUG
		std::stringstream ss;
		ss << "Deleting Behavior: " << it->second->getBehaviorName();		
		robotLib->Log(ss.str());
		delete(it->second);
#endif
	}
}

void BehaviorManager::stateChange(states_t newState)
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	std::stringstream timeStr;
	int year = now->tm_year + 1900;
	int mon = now->tm_mon + 1;
	int day = now->tm_mday + 1;
	timeStr << year << "-" << mon << "-" << day << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	SQLite::Database db(DB_LOCATION, SQLite::OPEN_READWRITE);
	SQLite::Statement stmt(db, "INSERT INTO States(?,?,?)");
	std::stringstream gStr;
	gStr << robotLib->getSessionID();
	
	stmt.bind(1, gStr.str());;
	stmt.bind(2, newState);
	stmt.bind(3, timeStr.str());
	if (stmt.exec() <= 0)
		robotLib->LogError("Failed to insert State Change into database");
	currentState = newState;
}

void BehaviorManager::behaviorLoop()
{
	while (true)
	{
		if (scheduler->legalMowingTime(mowingSessions) && (currentState == STATE_IDLE))
		{
			// Check battery charge
			if (behaviors[STATE_IDLE]->run() == 0)				
			{
				stateChange(STATE_UNDOCKING);				
				mowingSessions++;
			}
			else				
				stateChange(STATE_FIND_STATION);
		}
		if (currentState == STATE_IDLE)
		{
			if (behaviors[STATE_IDLE]->run() == 1)
				stateChange(STATE_FIND_STATION);			
		}
		if (currentState == STATE_CHARGING)
		{
			if (behaviors[STATE_CHARGING]->run() == 2)
			{
				if (scheduler->legalMowingTime(mowingSessions))
				{
					mowingSessions++;
					stateChange(STATE_UNDOCKING);					
				}
			}
			if (behaviors[STATE_CHARGING]->run() == 0)
				stateChange(STATE_CHARGING);
		}
	}
}