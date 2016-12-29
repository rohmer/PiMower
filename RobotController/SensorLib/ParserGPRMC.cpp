#include "ParserGPRMC.h"

ParserGPRMC::ParserGPRMC(RobotLib *robotLib)
	: ParserBase(robotLib)
{
	robotLib->Log("ParserGPRMC Initalized");	
}

sensors_gps_t *ParserGPRMC::Parse(std::vector<std::string> tokens)
{
	memset(event, 0, sizeof(sensors_gps_t));
	
	event->messageType.push_back(nmea_msg_t::NMEA_GPRMC);
	for (int a = 1; a < tokens.size(); a++)
	{
		int idx = a - 1;
		switch (idx)
		{
			case NMEA_GPRMC_DATAQUALITY:
				if (tokens[a] == "A")
					event->dataQuality = nmea_data_quality_t::DATA_OK;
				else
					if (tokens[a] == "V")
					event->dataQuality = nmea_data_quality_t::WARNING;
				else
					event->dataQuality = nmea_data_quality_t::UNKNOWN;
				break;
			case NMEA_GPRMC_TIME:
				if (!nmea_time_parse(tokens[a], &event->time))
				{
					event->time.tm_gmtoff = event->time.tm_hour = event->time.tm_isdst =
						event->time.tm_min = event->time.tm_sec;
				}
				break;
			case NMEA_GPRMC_LATITUDE:
				if (!nmea_position_parse(tokens[a], &event->latitude))
				{
					event->latitude.cardinal = NMEA_CARDINAL_DIR_UNKNOWN;
					event->latitude.degrees = event->latitude.minutes = 0;
				}
				break;
			case NMEA_GPRMC_LATITUDE_CARDINAL:
				event->latitude.cardinal = nmea_cardinal_direction_parse(tokens[a]);
				break;
			case NMEA_GPRMC_LONGITUDE:
				if (!nmea_position_parse(tokens[a], &event->longitude))
				{
					event->longitude.cardinal = NMEA_CARDINAL_DIR_UNKNOWN;
					event->longitude.degrees = event->longitude.minutes = 0;
				}
				break;
			case NMEA_GPRMC_LONGITUDE_CARDINAL:
				event->longitude.cardinal = nmea_cardinal_direction_parse(tokens[a]);
				break;
			case NMEA_GPRMC_DATE:
				/* Parse date */
				if(!nmea_date_parse(tokens[a], &event->time)) 
				{
					event->time.tm_gmtoff = event->time.tm_isdst =
						event->time.tm_mday = event->time.tm_mon =
						event->time.tm_wday = event->time.tm_yday =
						event->time.tm_year;
				}
				break;
			case NMEA_GPRMC_GROUND_SPEED:
				/* Parse a double */
				event->speedKTS = nmea_dec_parse(tokens[a]);
				event->speedKPH = event->speedKTS * 0.5399568;
				break;
			case NMEA_GPRMC_TRUE_COURSE:
				/* Parse a double */
				event->course = nmea_dec_parse(tokens[a]);
				break;
		}
	}
	return event;
}
