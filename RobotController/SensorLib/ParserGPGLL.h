#pragma once
#include "ParserBase.h"

#define NMEA_GPGLL_LATITUDE				0
#define NMEA_GPGLL_LATITUDE_CARDINAL	1
#define NMEA_GPGLL_LONGITUDE			2
#define NMEA_GPGLL_LONGITUDE_CARDINAL	3

class ParserGPGLL : public ParserBase
{
	public:
		ParserGPGLL(RobotLib *robotLib);
		sensors_gps_t *Parse(std::vector<std::string> tokens);	
		std::string getName()
		{ 
			return "GPGLL";
		}
};