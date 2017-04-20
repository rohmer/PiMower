#pragma once
#include "../../RobotLib/RobotLib.h"
#include <string>
#include <string.h>
#include <sstream>
#include "SensorLib.h"
#include "ObjectParsers.h"

#define NMEA_TIME_FORMAT	"%H%M%S"
#define NMEA_TIME_FORMAT_LEN	6
#define NMEA_DATE_FORMAT	"%d%m%y"
#define NMEA_DATE_FORMAT_LEN	6

class RobotLib;

class ParserBase
{
public:
	ParserBase(RobotLib *robotLib)
	{
		this->robotLib = robotLib;
		event = new sensors_gps_t();
	}
	virtual sensors_gps_t *Parse(std::vector<std::string> tokens)
	{
	}
	virtual std::string getName()
	{
	}
	~ParserBase()
	{
	}

protected:
	std::vector<std::string> tokens;
	RobotLib *robotLib;
	sensors_gps_t *event;
};
