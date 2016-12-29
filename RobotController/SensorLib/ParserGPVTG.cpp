#include "ParserGPVTG.h"

ParserGPVTG::ParserGPVTG(RobotLib *robotLib)
	: ParserBase(robotLib)
{
	robotLib->Log("ParserGPVTG Initalized");	
}

sensors_gps_t *ParserGPVTG::Parse(std::vector<std::string> tokens)
{
	memset(event, 0, sizeof(sensors_gps_t));
	
	event->messageType.push_back(nmea_msg_t::NMEA_GPGGA);
	for (int a = 1; a < tokens.size(); a++)
	{
		int idx = a - 1;
		switch (idx)
		{
		case NMEA_GPVTG_TRACK:
			event->course = nmea_dec_parse(tokens[a]);
			break;
		case NMEA_GPVTG_GROUND_SPEED_KTS:
			event->speedKTS = nmea_dec_parse(tokens[a]);
		case NMEA_GPVTG_GROUND_SPEED_KPH:
			event->speedKPH = nmea_dec_parse(tokens[a]);
			break;		
		}
	}
	
	return event;
}