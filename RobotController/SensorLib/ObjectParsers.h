#pragma once
#include "SensorLib.h"
#include <string>
#include "ParserBase.h"
#include <time.h>
#include <string.h>
#include <stdexcept>

bool nmea_position_parse(std::string s, nmea_position *event);
nmea_cardinal_t nmea_cardinal_direction_parse(std::string s);
bool nmea_time_parse(std::string s, struct tm *time);
bool nmea_date_parse(std::string s, struct tm *time);
double nmea_dec_parse(std::string s);
uint8_t nmea_int_parse(std::string s);
