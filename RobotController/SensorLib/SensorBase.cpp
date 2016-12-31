#include "SensorBase.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPiI2C.h"

SensorBase::SensorBase(RobotLib *robotLib)
	: DeviceBase(robotLib, DEVICE_TYPE_T::SENSOR)
{
}

double SensorBase::getTimestamp()
{
	time_t timer;
	time(&timer);
	struct tm y2k = { 0 };
	y2k.tm_hour = 0; y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
	
	return (difftime(timer, mktime(&y2k)));
}

uint16_t SensorBase::i2cReadReg16(int fd, uint8_t reg)
{
	uint16_t val = wiringPiI2CReadReg16(fd, reg);
	if (val <= 0)
	{
		std::stringstream ss;
		ss << "Error writing to Registry: " << reg << " error: " << strerror(errno);
		robotLib->LogError(ss.str());		
		return -1;
	}

	return val;
}

uint8_t SensorBase::i2cReadReg8(int fd, uint8_t reg)
{
	uint8_t val = wiringPiI2CReadReg8(fd, reg);
	if (val <= 0)
	{
		std::stringstream ss;
		ss << "Error writing to Registry: " << reg << " error: " << strerror(errno);
		robotLib->LogError(ss.str());
		return -1;
	}

	return val;
}

bool SensorBase::i2cWriteReg16(int fd, uint8_t reg, uint16_t val)
{
	if (wiringPiI2CWriteReg16(fd, reg, val) <=0)
	{
		std::stringstream ss;
		ss << "Error writing to Registry: " << reg << " error: " << strerror(errno);
		robotLib->LogError(ss.str());
		return false;
	}
	return true;
}

bool SensorBase::i2cWriteReg8(int fd, uint8_t reg, uint8_t val)
{
	if (wiringPiI2CWriteReg8(fd, reg, val) <= 0)
	{
		std::stringstream ss;
		ss << "Error writing to Registry: " << reg << " error: " << strerror(errno);
		robotLib->LogError(ss.str());
		return false;
	}
	return true;
}
