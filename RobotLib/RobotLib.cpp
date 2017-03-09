#include "RobotLib.h"
Guid RobotLib::sessionGuid;

RobotLib::RobotLib()
{		
	//Database::initDB();
	config = getConfig();	
	initLog();
	emulator = checkEmulator();
	if (emulator)
	{
		Log("Running on QEMU emulator");
	}
	deviceManager = new DeviceManager(*this);	
	mapObject = new LawnMap(this);
	// Set error pin and clear it
	pinMode(config->getErrorStatusPin(), OUTPUT);
	digitalWrite(config->getErrorStatusPin(), LOW);
	Log("RobotLib Initialized");
}

bool RobotLib::loadConfig(std::string configFile)
{
	return config->getConfig(configFile);
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
	Poco::AutoPtr<Poco::SplitterChannel> pSplitter(new Poco::SplitterChannel);
	Poco::AutoPtr<Poco::FileChannel> pChannel(new Poco::FileChannel);
	Poco::AutoPtr<Poco::PatternFormatter> pf(new Poco::PatternFormatter);
	pf->setProperty("pattern", "%Y/%m/%d %H:%M:%S %p: %t");
	Poco::AutoPtr<Poco::ConsoleChannel>  cChannel(new Poco::ConsoleChannel);
	Poco::AutoPtr<Poco::FormattingChannel> pFC(new Poco::FormattingChannel(pf, pChannel));
	pChannel->setProperty("path", "Robot.log");
	pChannel->setProperty("rotation", "20 M");
	pChannel->setProperty("archive", "timestamp");	
	pChannel->setProperty("purgeCount", "1");
	pSplitter->addChannel(pFC);
	pSplitter->addChannel(cChannel);	
	logger.setChannel(pSplitter);	
	
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
	std::clog << "Sev: " << severity << " Message: " << message;
	//if (severity <= minLogLevel)
//		return;
	time_t t = time(0);
	struct tm *now = localtime(&t);
	std::stringstream timeStr;
	int year = now->tm_year + 1900;
	int mon = now->tm_mon + 1;
	int day = now->tm_mday + 1;
	timeStr << year << "-" << mon << "-" << day << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	std::stringstream ss;
	ss << getSessionID();
	std::string sessionID = ss.str();
	Poco::Data::Session dbSession = Database::getDBSession(); 
	Poco::Data::Statement stmt = (dbSession << "INSERT LOW_PRIORITY INTO Log (timestamp,message,severity,sessionID) VALUES(?,?,?,?)",
		Poco::Data::Keywords::bind(timeStr.str()),
		Poco::Data::Keywords::bind(message),
		Poco::Data::Keywords::bind(severity),
		Poco::Data::Keywords::bind(sessionID));
	stmt.execute();
	
	clearCounter++;
	if (clearCounter > 100)
	{		
		std::stringstream ss;
		Poco::Data::Statement clear(dbSession);
		int clearNum = config->getMessagedDBRetention();
		clear << "DELETE FROM Log WHERE timestamp <= date_sub(curdate(), interval " << clearNum << " minute);";
		clearCounter = 0;
		clear.executeAsync();
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
	std::clog << "Error Message: " <<message;
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
