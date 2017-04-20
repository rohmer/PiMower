#pragma once
#include "ParserBase.h"

#define NMEA_GPGGA_TIME					0
#define NMEA_GPGGA_LATITUDE				1
#define NMEA_GPGGA_LATITUDE_CARDINAL	2
#define NMEA_GPGGA_LONGITUDE			3
#define NMEA_GPGGA_LONGITUDE_CARDINAL	4
#define NMEA_GPGGA_FIXQUALITY			5
#define NMEA_GPGGA_SATNUM				6
#define NMEA_GPGGA_HDOP					7
#define NMEA_GPGGA_ALTITUDE				8
#define NMEA_GPGGA_GEOID				10
#define NMEA_GPGGA_TIME_SINCE_DGPS		12
#define NMEA_GPGGA_DGPS_REF_STAT		13

class ParserGPGGA : public ParserBase
{
public:
	ParserGPGGA(RobotLib *robotLib);
	sensors_gps_t *Parse(std::vector<std::string> tokens);
	std::string getName()
	{
		return "GPGGA";
	}
};