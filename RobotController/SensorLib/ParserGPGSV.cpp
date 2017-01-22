#include "ParserGPGSV.h"

ParserGPGSV::ParserGPGSV(RobotLib *robotLib)
	: ParserBase(robotLib)
{
	robotLib->Log("ParserGPGSV Initalized");	
}

sensors_gps_t *ParserGPGSV::Parse(std::vector<std::string> tokens)
{
	//memset(event, 0, sizeof(sensors_gps_t));
	
	event->messageType.push_back(nmea_msg_t::NMEA_GPGGA);
	for (int a = 1; a < tokens.size(); a++)
	{
		int idx = a - 1;
		switch (idx)
		{
		case NMEA_GPGSV_MSGTOT:
			event->sateliteInfo.msgTotal = nmea_int_parse(tokens[a]);
			break;
		case NMEA_GPGSV_MSGNUM:
			event->sateliteInfo.msgNum = nmea_int_parse(tokens[a]);
			break;
		case NMEA_GPGSV_SVS_IN_VIEW:
			event->sateliteInfo.totalSVsInView = nmea_int_parse(tokens[a]);
			break;		
		case NMEA_GPGSV_SV_PRN_NUM_1:
			event->sateliteInfo.svPRNNum1 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_ELEVATION_DEGREES_1:
			event->sateliteInfo.elevation1 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_AZIMUTH_1:
			event->sateliteInfo.azimuth1 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_SNR_1:
			event->sateliteInfo.SNR1 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_SV_PRN_NUM_2:
			event->sateliteInfo.svPRNNum2 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_ELEVATION_DEGREES_2:
			event->sateliteInfo.elevation2 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_AZIMUTH_2:
			event->sateliteInfo.azimuth2 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_SNR_2:
			event->sateliteInfo.SNR2 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_SV_PRN_NUM_3:
			event->sateliteInfo.svPRNNum3 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_ELEVATION_DEGREES_3:
			event->sateliteInfo.elevation3 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_AZIMUTH_3:
			event->sateliteInfo.azimuth3 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_SNR_3:
			event->sateliteInfo.SNR3 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_SV_PRN_NUM_4:
			event->sateliteInfo.svPRNNum4 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_ELEVATION_DEGREES_4:
			event->sateliteInfo.elevation4 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_AZIMUTH_4:
			event->sateliteInfo.azimuth4 = nmea_int_parse(tokens[a]);
			break;	
		case NMEA_GPGSV_SNR_4:
			event->sateliteInfo.SNR4 = nmea_int_parse(tokens[a]);
			break;	
		
		}
	}
	
	return event;
}