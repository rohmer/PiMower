#pragma once
#include "ParserBase.h"

#define NMEA_GPVTG_TRACK				0
#define NMEA_GPVTG_GROUND_SPEED_KTS 	4
#define NMEA_GPVTG_GROUND_SPEED_KPH		6

class ParserGPVTG : public ParserBase
{
public:
	ParserGPVTG(RobotLib *robotLib);
	sensors_gps_t *Parse(std::vector<std::string> tokens);	
	std::string getName()
	{ 
		return "GPVTG";
	}
};
