#include "RobotLib.h"
Guid RobotLib::sessionGuid;

RobotLib::RobotLib()
{	
	config = getConfig();
	initLog();
	emulator = checkEmulator();
	if (emulator)
	{
		Log("Running on QEMU emulator");
	}
	deviceManager = new DeviceManager(*this);
	dbLoggerThread = std::thread(startLogDBThread,this);
	// Set error pin and clear it
	pinMode(config->getErrorStatusPin(), OUTPUT);
	digitalWrite(config->getErrorStatusPin(), LOW);
}

void RobotLib::startLogDBThread(RobotLib *robotLib)
{
	robotLib->dbLogger();
}

Config *RobotLib::getConfig()
{
	if (config == NULL)
	{
		config = new Config(this);
		config->getConfig();
	}
	return config;
}

RobotLib::~RobotLib()
{	
	shutdown = true;
	dbLoggerThread.join();
	delete(deviceManager);
	if (mapObject)
		delete(mapObject);	
}

void RobotLib::initLog()
{
	Poco::Logger& logger = Poco::Logger::get("RobotLib");		
	switch (config->getLogLevel())
	{
		case min_log_level_t::Debug:
			logger.setLevel("trace");
			break;
		case min_log_level_t::Warn:
		logger.setLevel("warning");
		break;
		case min_log_level_t::Critical:
		logger.setLevel("critical");
		break;
		case min_log_level_t::Exception:
		logger.setLevel("fatal");
			
			break;		
	}
	Poco::AutoPtr<Poco::FileChannel> pChannel(new Poco::FileChannel);
	pChannel->setProperty("path", "Robot.log");
	pChannel->setProperty("rotation", "20 K");
	pChannel->setProperty("archive", "timestamp");
	logger.setChannel(pChannel);	
#ifdef DEBUG
	logger.setLevel("trace");			
#endif	
}

void RobotLib::setLogLevel(int logLevel)
{	
	if (logLevel == 0)
	{		
		Poco::Logger::get("RobotLib").setLevel("trace");
		minLogLevel = logLevel;
		return;
	}
	if (logLevel == 1)
	{		
		Poco::Logger::get("RobotLib").setLevel("warning");
		minLogLevel = logLevel;
		return;
	}
	if (logLevel == 2)
	{
		Poco::Logger::get("RobotLib").setLevel("critical");
		minLogLevel = logLevel;
		return;
	}
	if (logLevel == 3)
	{
		Poco::Logger::get("RobotLib").setLevel("fatal");
		minLogLevel = logLevel;
		return;
	}
	logLevel = 1;
	Poco::Logger::get("RobotLib").setLevel("warning");
	minLogLevel = logLevel;
}

void RobotLib::logDB(std::string message, int severity)
{
	if (severity < minLogLevel)
		return;
	std::stringstream sql;
	time_t t = time(0);
	struct tm *now = localtime(&t);
	std::stringstream timeStr;
	int year = now->tm_year + 1900;
	int mon = now->tm_mon + 1;
	int day = now->tm_mday + 1;
	timeStr << year << "-" << mon << "-" << day << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	dbLogMsg msg;	
	msg.timeStr = timeStr.str();
	msg.severity = severity;
	msg.msg = message;
	std::stringstream ss;
	ss << getSessionID();
	msg.sessionID = ss.str();
	{
		std::unique_lock<std::mutex> lock(this->logMutex);
		logMessages.push_front(msg);
	}
}

void RobotLib::dbLogger()
{
	long clearPoint = 300; // clear every 5 minutes
	long clearCounter = 0;
	while (!shutdown && logMessages.size() > 0)
	{
		Poco::Data::Session  dbSession("SQLite", DB_LOCATION);
		Poco::Data::Statement stmt(dbSession);		
		while(logMessages.size()>0)
		{
			dbLogMsg msg;
			{	
				std::unique_lock<std::mutex> lock(this->logMutex);
				this->logCondition.wait(lock, [=]{return !this->logMessages.empty();});
				msg = logMessages.back();				
				logMessages.pop_back();
			}
			stmt << "INSERT INTO Log VALUES(?,?,?,?)",
				Poco::Data::use(msg.timeStr),
				Poco::Data::use(msg.msg),
				Poco::Data::use(msg.severity),
				Poco::Data::use(msg.sessionID);			
			try
			{
				{
					std::unique_lock<std::mutex> lock(Database::dbMutex);
		
					if (!stmt.execute())
						LogError("Failed to insert event into database");										
				}
			}
			catch (std::exception &e)
			{
				std::stringstream ss;
				ss << "Exception caught: " << e.what() << std::endl;
				LogError(ss.str());
			}
		}		
		// If we are shutting down, push these as fast as we can
		// Also dont prune
		if (!shutdown)
		{			
			clearCounter++;
			// DO TIME BASED DELETION
			std::stringstream ss;
			Poco::Data::Statement clear(dbSession);
			clear << "DELETE FROM Log WHERE timestamp <= date('now','-" << config->getMessagedDBRetention() << " minutes')";
			Log(ss.str());
			
			if (clearCounter > clearPoint)				
			{
				clearCounter = 0;
				{
					std::unique_lock<std::mutex> lock(Database::dbMutex);
					clear.execute();
				}
			}
			delay(1000);
		}
	}
}
void RobotLib::Log(std::string message)
{
	Poco::Logger::get("RobotLib").trace(message);		
	logDB(message, 0);
}

void RobotLib::LogWarn(std::string message)
{
	Poco::Logger::get("RobotLib").warning(message);
	logDB(message, 1);
}

void RobotLib::LogError(std::string message)
{
	Poco::Logger::get("RobotLib").critical(message);		
	logDB(message, 2);
}

void RobotLib::LogException(std::exception &e)
{
	std::stringstream ss;
	ss << "Exception caught: " << e.what() << std::endl;
	Poco::Logger::get("RobotLib").fatal(ss.str());
	logDB(ss.str(), 3);
}

bool RobotLib::checkEmulator()
{
	FILE *cpufd;
	char line[120];
	if ((cpufd = fopen("/proc/cpuinfo", "r")) == NULL)
	{
		LogError("Could not open /proc/cpuinfo");
		return false;
	}
	
	while (fgets(line, 120, cpufd) != NULL)
		if (strncmp(line, "Hardware", 8) == 0)
			break ;

	if (strncmp(line, "Hardware", 8) != 0)
	{
		LogError("No hardware line in /proc/cpuinfo");
		fclose(cpufd);
		return false;
	}
	
	if (strstr(line, "BCM2709") != NULL)	// Pi v2 - no point doing anything more at this point
	{
		fclose(cpufd);
		return false;
	}
	if (strstr(line, "BCM2708") != NULL)
	{
		fclose(cpufd);
		return false;
	}
	if (strstr(line, "ARM-Versatile PB") != NULL)
	{
		fclose(cpufd);
		return true;
	}
	fclose(cpufd);
	return false;
}

LawnMap *RobotLib::getMap()
{
	if (mapObject == NULL)
	{
		mapObject = new LawnMap(this);
	}
	return mapObject;
}

MotorController *RobotLib::getMotorController()
{
	if (motorController == NULL)
	{
		motorController = new MotorController(this, config);
	}
	return motorController;
}

void RobotLib::setSessionID()
{
	GuidGenerator guidGen;
	this->sessionGuid=guidGen.newGuid();
}
