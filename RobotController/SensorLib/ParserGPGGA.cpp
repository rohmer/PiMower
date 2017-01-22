#include "ParserGPGGA.h"

ParserGPGGA::ParserGPGGA(RobotLib *robotLib)
	: ParserBase(robotLib)
{
	robotLib->Log("ParserGPGGA Initalized");	
}

sensors_gps_t *ParserGPGGA::Parse(std::vector<std::string> tokens)
{
	//memset(event, 0, sizeof(sensors_gps_t));
	event->messageType.push_back(nmea_msg_t::NMEA_GPGGA);
	for (int a = 1; a < tokens.size(); a++)
	{
		int idx = a - 1;
		switch (idx)
		{
			case NMEA_GPGGA_TIME:
				if (!nmea_time_parse(tokens[a], &event->time))
				{
					event->time.tm_gmtoff = event->time.tm_hour = event->time.tm_isdst =
						event->time.tm_min = event->time.tm_sec;
				}
				break;
			case NMEA_GPGGA_LATITUDE:
				if (!nmea_position_parse(tokens[a], &event->latitude))
				{
					event->latitude.cardinal = NMEA_CARDINAL_DIR_UNKNOWN;
					event->latitude.degrees = event->latitude.minutes = 0;
				}
				break;
			case NMEA_GPGGA_LATITUDE_CARDINAL:
				event->latitude.cardinal = nmea_cardinal_direction_parse(tokens[a]);
				break;
			case NMEA_GPGGA_LONGITUDE:
				if (!nmea_position_parse(tokens[a], &event->longitude))
				{
					event->longitude.cardinal = NMEA_CARDINAL_DIR_UNKNOWN;
					event->longitude.degrees = event->longitude.minutes = 0;
				}
				break;
			case NMEA_GPGGA_LONGITUDE_CARDINAL:
				event->longitude.cardinal = nmea_cardinal_direction_parse(tokens[a]);
				break;
			case NMEA_GPGGA_FIXQUALITY:
				{
					uint8_t i = nmea_int_parse(tokens[a]);
					switch (i)
					{
					case 0:
						event->fixquality = nmea_fix_quality_t::INVALID;
						break;
					case 1:
						event->fixquality = nmea_fix_quality_t::GPS_FIX;
						break;
					case 2:
						event->fixquality = nmea_fix_quality_t::DGPS_FIX;
						break;
					default:
						event->fixquality = nmea_fix_quality_t::UNK;
						break;
					}			
				}
				break;
			case NMEA_GPGGA_SATNUM:
				event->satellites = nmea_int_parse(tokens[a]);
				break;
			case NMEA_GPGGA_HDOP:	
				event->HDOP = nmea_dec_parse(tokens[a]);
				break;
			case NMEA_GPGGA_ALTITUDE:
				event->altitude = nmea_dec_parse(tokens[a]);
				break;
			case NMEA_GPGGA_GEOID:
				event->geoIDHeight = nmea_dec_parse(tokens[a]);
				break;
			case NMEA_GPGGA_TIME_SINCE_DGPS:
				break;
			case NMEA_GPGGA_DGPS_REF_STAT:
				break;							
		}
	}
	
	return event;
}