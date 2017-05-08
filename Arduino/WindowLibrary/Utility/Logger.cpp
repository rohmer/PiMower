#include "Logger.h"
Logger::LogLevel Logger::minLevel;
HardwareSerial *Logger::serial;

void Logger::initLogger(LogLevel minimumLevel)
{
	minLevel = minimumLevel;
}

void Logger::initLogger(LogLevel minimumLevel, long baudRate)
{
	serial = &Serial;
	minLevel = minimumLevel;
	serial->begin(baudRate);
}

void Logger::Trace(const char *fmt, ...)
{
	if (minLevel > 0)
		return;
	if (!serial)
		serial = &Serial;
	std::stringstream ss;
	ss << millis();
	ss << " | ";
	ss << "TRACE | ";
	char buf[256];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, 255, fmt, ap);
	va_end(ap);
	ss << buf;	
	serial->println(ss.str().c_str());
}

void Logger::Warn(const char *fmt, ...)
{
	if (minLevel > 1)
		return;
	if (!serial)
		serial = &Serial;
	std::stringstream ss;
	ss << millis();
	ss << " | ";
	ss << "WARN | ";
	char buf[256];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, 255, fmt, ap);
	va_end(ap);
	ss << buf;
	serial->println(ss.str().c_str());
}

void Logger::Crit(const char *fmt, ...)
{
	if (minLevel > 2)
		return;
	if (!serial)
		serial = &Serial;
	std::stringstream ss;
	ss << millis();
	ss << " | ";
	ss << "CRITICAL | ";
	char buf[256];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, 255, fmt, ap);
	va_end(ap);
	ss << buf;
	serial->println(ss.str().c_str());
}

void Logger::Fatal(const char *fmt, ...)
{
	if (!serial)
		serial = &Serial;
	std::stringstream ss;
	ss << millis();
	ss << " | ";
	ss << "FATAL | ";
	char buf[256];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, 255, fmt, ap);
	va_end(ap);
	ss << buf;
	serial->println(ss.str().c_str());
}
