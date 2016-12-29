#pragma once
#include "../SensorLib/SensorLib.h"
#include "ParserGPRMC.h"
#include "ParserGPGLL.h"
#include "ParserGPGGA.h"
#include <utility>
#include <string>
#include <sstream>
#include <stdint.h>
#include <map>
#include "ParserBase.h"

class RobotLib;
class ParserBase;

typedef std::map<std::string, ParserBase*> parserMap_t;
typedef std::pair<std::string, ParserBase*> parserPair_t;

class NMEAParser
{	
	public: 
		NMEAParser(RobotLib *robotLib);	
		bool ValidSentence(const char *sentence);
		bool ValidChecksum(const char *sentence);
		uint8_t GetChecksum(const char *sentence);
		sensors_gps_t *Parse(const char *sentence);
		~NMEAParser();
	
	private:
		RobotLib *robotLib;
		// Map containing parser objects
		parserMap_t parsers;
};
