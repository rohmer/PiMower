#pragma once
#pragma once
#include "ParserBase.h"

#define NMEA_GPGSV_MSGTOT				0
#define NMEA_GPGSV_MSGNUM				1
#define NMEA_GPGSV_SVS_IN_VIEW			2
#define NMEA_GPGSV_SV_PRN_NUM_1			3
#define NMEA_GPGSV_ELEVATION_DEGREES_1	4
#define NMEA_GPGSV_AZIMUTH_1			5
#define NMEA_GPGSV_SNR_1				6
#define NMEA_GPGSV_SV_PRN_NUM_2			7
#define NMEA_GPGSV_ELEVATION_DEGREES_2	8
#define NMEA_GPGSV_AZIMUTH_2			9
#define NMEA_GPGSV_SNR_2				10
#define NMEA_GPGSV_SV_PRN_NUM_3			11
#define NMEA_GPGSV_ELEVATION_DEGREES_3	12
#define NMEA_GPGSV_AZIMUTH_3			13
#define NMEA_GPGSV_SNR_3				14
#define NMEA_GPGSV_SV_PRN_NUM_4			15
#define NMEA_GPGSV_ELEVATION_DEGREES_4	16
#define NMEA_GPGSV_AZIMUTH_4			17
#define NMEA_GPGSV_SNR_4				18

class ParserGPGSV : public ParserBase
{
public:
	ParserGPGSV(RobotLib *robotLib);
	sensors_gps_t *Parse(std::vector<std::string> tokens);
	std::string getName()
	{
		return "GPGSV";
	}
};