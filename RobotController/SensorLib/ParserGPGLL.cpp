#include "ParserGPGLL.h"

ParserGPGLL::ParserGPGLL(RobotLib *robotLib)
	: ParserBase(robotLib)
{
	robotLib->Log("ParserGPGLL Initalized");	
}

sensors_gps_t *ParserGPGLL::Parse(std::vector<std::string> tokens)
{
	memset(event, 0, sizeof(sensors_gps_t));
	
	event->messageType.push_back(nmea_msg_t::NMEA_GPGLL);
	for (int a = 1; a < tokens.size(); a++)
	{
		int idx = a - 1;
		switch (idx)
		{
			case NMEA_GPGLL_LATITUDE:
				if (!nmea_position_parse(tokens[a], &event->latitude))
				{
					event->latitude.cardinal = NMEA_CARDINAL_DIR_UNKNOWN;
					event->latitude.degrees = event->latitude.minutes = 0;
				}
				break;
			case NMEA_GPGLL_LATITUDE_CARDINAL:
				event->latitude.cardinal = nmea_cardinal_direction_parse(tokens[a]);
				break;
			case NMEA_GPGLL_LONGITUDE:
				if (!nmea_position_parse(tokens[a], &event->longitude))
				{
					event->longitude.cardinal = NMEA_CARDINAL_DIR_UNKNOWN;
					event->longitude.degrees = event->longitude.minutes = 0;
				}
				break;
			case NMEA_GPGLL_LONGITUDE_CARDINAL:
				event->longitude.cardinal = nmea_cardinal_direction_parse(tokens[a]);
				break;
		}
	}
	return event;
}