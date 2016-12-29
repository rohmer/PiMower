#include "ObjectParsers.h"

bool nmea_position_parse(std::string s, nmea_position *event)
{
	event->degrees = 0;
	event->minutes = 0;
	if (s.empty() || s[0] == '\0')
	{
		return false;		
	}
	
	// Format is nnnn.nn for latitude and nnnnn.nn for longitude
	int degLen = 2;
	if (s.length() > 9)
	{
		// lattitude
		degLen = 3;
	}
	
	event->minutes = std::stod(s.substr(degLen,std::string::npos));
	event->degrees = std::stod(s.substr(0, degLen));
	return true;
}

nmea_cardinal_t nmea_cardinal_direction_parse(std::string s)
{
	if (s.empty() || s[0] == '\0')
	{
		return NMEA_CARDINAL_DIR_UNKNOWN;
	}
	if (s == "N")
	{		
		return NMEA_CARDINAL_DIR_NORTH;
	}
	if (s == "E")
	{		
		return NMEA_CARDINAL_DIR_EAST;
	}
	if (s == "S")
	{		
		return NMEA_CARDINAL_DIR_SOUTH;
	}
	if (s == "W")
	{		
		return NMEA_CARDINAL_DIR_WEST;
	}
	
	return NMEA_CARDINAL_DIR_UNKNOWN;
}

bool nmea_time_parse(std::string s, struct tm *time)
{
	char *rv;
	memset(time, 0, sizeof(struct tm));
	
	if (s.empty() || s[0] == '\0')
		return false;
	
	rv = strptime(s.c_str(), NMEA_TIME_FORMAT, time);
	if (rv == NULL || (int)(rv - s.c_str()) != NMEA_TIME_FORMAT_LEN)
	{
		return false;
	}
	
	return true;
}

bool nmea_date_parse(std::string s, struct tm *time)
{
	char *rv;
	
	if (s.empty() || s[0] == '\0')
		return false;
	rv = strptime(s.c_str(), NMEA_DATE_FORMAT, time);
	if (rv == NULL || (int)(rv - s.c_str()) != NMEA_DATE_FORMAT_LEN)
	{
		return false;		
	}
	
	return true;
}

double nmea_dec_parse(std::string s)
{
	double retVal;
	try
	{
		retVal = std::stod(s);
	}
	catch(std::invalid_argument)
	{
		retVal = -1;
	}
	return retVal;
}

uint8_t nmea_int_parse(std::string s)
{
	uint8_t retVal;
	try
	{
		retVal = std::stoi(s);
	}
	catch (std::invalid_argument)
	{
		retVal = -1;
	}
	return retVal;
}