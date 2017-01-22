#include "RobotLib.h"

RobotLib::RobotLib()
{	 	
	initLog();
	emulator = checkEmulator();
	if (emulator)
	{
		Log("Running on QEMU emulator");
	}
	database = new Database(*this);	
	//deviceManager = new DeviceManager(*this);
}

RobotLib::~RobotLib()
{
	delete(database);
	delete(deviceManager);
}

void RobotLib::initLog()
{
	humble::logging::Factory &fac = humble::logging::Factory::getInstance();
	fac.registerAppender(new humble::logging::ConsoleAppender());
	fac.registerAppender(new humble::logging::RollingFileAppender("Robot.log", false, 2, 20 * 1024 * 1024));
#ifdef DEBUG
	fac.setConfiguration(new humble::logging::SimpleConfiguration(humble::logging::LogLevel::All));
#else
	fac.setConfiguration(new humble::logging::SimpleConfiguration(humble::logging::LogLevel::Warn));
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

void RobotLib::Log(std::string message)
{
	HUMBLE_LOGGER(logger, "RobotLogger");
	HL_TRACE(logger, message);		
}

void RobotLib::LogWarn(std::string message)
{
	HUMBLE_LOGGER(logger, "RobotLogger");
	HUMBLE_LOG(logger, message, humble::logging::LogLevel::Warn);		
}

void RobotLib::LogError(std::string message)
{
	HUMBLE_LOGGER(logger, "RobotLogger");
	HL_ERROR(logger, message);		
}

void RobotLib::LogException(std::exception &e)
{
	std::stringstream ss;
	ss << "Exception caught: " << e.what() << std::endl;
	HUMBLE_LOGGER(logger, "RobotLogger");
	HL_FATAL(logger, ss.str());
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