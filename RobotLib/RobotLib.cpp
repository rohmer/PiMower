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
	delete(deviceManager);
	if (mapObject)
		delete(mapObject);	
}

void RobotLib::initLog()
{
	humble::logging::Factory &fac = humble::logging::Factory::getInstance();
	fac.setDefaultFormatter(new humble::logging::PatternFormatter("[%lls] %date -> %m\n"));
	fac.registerAppender(new humble::logging::ConsoleAppender());
	switch (config->getLogLevel())
	{
		case min_log_level_t::Debug:
			fac.setConfiguration(new humble::logging::SimpleConfiguration(humble::logging::LogLevel::All));	
			break;
		case min_log_level_t::Warn:
			fac.setConfiguration(new humble::logging::SimpleConfiguration(humble::logging::LogLevel::Warn));	
			break;
		case min_log_level_t::Critical:
			fac.setConfiguration(new humble::logging::SimpleConfiguration(humble::logging::LogLevel::Error));	
			break;
		case min_log_level_t::Exception:
			fac.setConfiguration(new humble::logging::SimpleConfiguration(humble::logging::LogLevel::Fatal));	
			break;		
	}
	fac.registerAppender(new humble::logging::RollingFileAppender("Robot.log", false, 2, 20 * 1024 * 1024));
#ifdef DEBUG
	fac.setConfiguration(new humble::logging::SimpleConfiguration(humble::logging::LogLevel::All));
#endif	
}

void RobotLib::setLogLevel(int logLevel)
{
	humble::logging::Factory &fac = humble::logging::Factory::getInstance();	
	if (logLevel == 0)
		fac.setConfiguration(new humble::logging::SimpleConfiguration(humble::logging::LogLevel::All));
	if (logLevel == 1)
		fac.setConfiguration(new humble::logging::SimpleConfiguration(humble::logging::LogLevel::Warn));
	if (logLevel == 2)
		fac.setConfiguration(new humble::logging::SimpleConfiguration(humble::logging::LogLevel::Error));
	if (logLevel == 3)
		fac.setConfiguration(new humble::logging::SimpleConfiguration(humble::logging::LogLevel::Fatal));
}

void RobotLib::logDB(std::string message, int severity)
{
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
	{
		std::unique_lock<std::mutex> lock(this->logMutex);
		logMessages.push_front(msg);
	}
}

void RobotLib::dbLogger()
{
	SQLite::Database *dbHandle = Database::getInstance().getDBHandle();
	SQLite::Statement stmt(*dbHandle, "INSERT INTO Log VALUES(?,?,?)");
	// DO TIME BASED DELETION
	SQLite::Statement pruneStmt(*dbHandle, "DELETE FROM Log WHERE timestamp <= date('now','-? hour'");
	pruneStmt.bind(config->getMessagedDBRetention());
	long clearPoint = config->getMessagedDBRetention() / 50;
	long clearCounter = 0;
	while (!shutdown && logMessages.size() > 0)
	{
		while(logMessages.size()>0)
		{
			dbLogMsg msg;
			{	
				std::unique_lock<std::mutex> lock(this->logMutex);
				this->logCondition.wait(lock, [=]{return !this->logMessages.empty();});
				msg = logMessages.back();				
				logMessages.pop_back();
			}
			stmt.clearBindings();
			stmt.bind(1, msg.timeStr);
			stmt.bind(2, msg.msg);
			stmt.bind(3, msg.severity);
			try
			{
				if (!stmt.exec())
					LogError("Failed to insert event into database");
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
			if (clearCounter > clearPoint)
			{
				clearCounter = 0;
				pruneStmt.exec();				
			}
			delay(1000);
		}
	}
}
void RobotLib::Log(std::string message)
{
	HUMBLE_LOGGER(logger, "RobotLogger");	
	HL_TRACE(logger, message);		
	logDB(message, 0);
}

void RobotLib::LogWarn(std::string message)
{
	HUMBLE_LOGGER(logger, "RobotLogger");
	HUMBLE_LOG(logger, message, humble::logging::LogLevel::Warn);		
	logDB(message, 1);
}

void RobotLib::LogError(std::string message)
{
	HUMBLE_LOGGER(logger, "RobotLogger");
	HL_ERROR(logger, message);		
	logDB(message, 2);
}

void RobotLib::LogException(std::exception &e)
{
	std::stringstream ss;
	ss << "Exception caught: " << e.what() << std::endl;
	HUMBLE_LOGGER(logger, "RobotLogger");
	HL_FATAL(logger, ss.str());
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
