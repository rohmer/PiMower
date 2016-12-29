#pragma once
#include "ParserBase.h"

#define NMEA_GPRMC_TIME			0
#define NMEA_GPRMC_DATAQUALITY	1
#define NMEA_GPRMC_LATITUDE		2
#define NMEA_GPRMC_LATITUDE_CARDINAL	3
#define NMEA_GPRMC_LONGITUDE		4
#define NMEA_GPRMC_LONGITUDE_CARDINAL	5
#define NMEA_GPRMC_GROUND_SPEED 6
#define NMEA_GPRMC_TRUE_COURSE 7
#define NMEA_GPRMC_DATE			8

class ParserGPRMC : public ParserBase
{
	public:
		ParserGPRMC(RobotLib *robotLib);
		sensors_gps_t *Parse(std::vector<std::string> tokens);
		std::string getName()
		{ 
			return "GPRMC";
		}
};