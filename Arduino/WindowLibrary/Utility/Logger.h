#pragma once
#include <string>
#include <sstream>
#include "Arduino.h"

#ifndef LOGGING_ENABLED
class Logger
{
public:
	enum LogLevel
	{
		TRACE = 0,
		WARN = 1,
		CRITICAL =2,
		FATAL = 3
	};

	static void Trace(const char *fmt, ...);
	static void Warn(const char *fmt, ...);
	static void Crit(const char *fmt, ...);
	static void Fatal(const char *fmt, ...);

	static void initLogger(LogLevel minimumLevel);
	static void initLogger(LogLevel minimumLevel, long baudRate);

	static std::string BoolToStr(bool val)
	{
		if (val)
			return "TRUE";
		return "FALSE";
	}

private:
	static LogLevel minLevel;
	static HardwareSerial *serial;
	static std::string buildString(LogLevel level, const char *fmt, ...);
	
};


#endif
