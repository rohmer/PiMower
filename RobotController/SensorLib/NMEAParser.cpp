#include "NMEAParser.h"
#include "ParserGPGSV.h"
#include "ParserGPVTG.h"

NMEAParser::NMEAParser(RobotLib *robotLib)
{
	this->robotLib = robotLib;
	
	robotLib->Log("NMEAParser initalized");
}

bool NMEAParser::ValidSentence(const char *sentence)
{
	std::string sent(sentence);
	std::stringstream ss;
	
	if (sent.length() < 9)
	{
		ss << "NMEA Sentence must be >= 9 characters, this one is: " << sent.length();	
		robotLib->Log(ss.str());
		return false;
	}
	if (sent.length() > 82)
	{
		ss << "NMEA Sentence must be <= 82 characters, this one is: " << sent.length();
		robotLib->Log(ss.str());
		return false;
	}
	if (sent[0] != '$')
	{
		ss << "NMEA Sentence must begin with $";
		robotLib->Log(ss.str());
		return false;
	}
	
	// Check checksum
	if (!ValidChecksum(sentence))
	{
		return false;
	}
	
	return true;
}

bool NMEAParser::ValidChecksum(const char *sentence)
{
	std::string sent(sentence);
	
	int askLocation = sent.find_last_of('*');
	sent = sent.substr(0, askLocation + 5);
	int length = sent.length();
	
	uint8_t actual_checksum, expected_checksum;
	char checksum[3];
 	checksum[0] = sentence[length - 4];
	checksum[1] = sentence[length - 3];
	checksum[2] = '\0';
	actual_checksum = GetChecksum(sentence);
	expected_checksum = (uint8_t) strtol(checksum, NULL, 16);
	if (expected_checksum != actual_checksum)
	{
		std::stringstream ss;
		ss << "Checksum mismatch, expected: " << expected_checksum << " received: " << actual_checksum;
		robotLib->Log(ss.str());
		return false;
	}
	
	return true;	
}

uint8_t NMEAParser::GetChecksum(const char *sentence)
{
	const char *n = sentence + 1;
	uint8_t chk = 0;
	
	// While current char isnt '*' or sentence ending newline 
	while (*n != '*' && *n != '\n' && *n != '\0')
	{
		chk ^= (uint8_t)*n;
		n++;
	}
	return chk;
}

sensors_gps_t *NMEAParser::Parse(const char *sentence)
{
	std::string sent(sentence);
	
	// First tokenize based on comma
	std::vector<std::string> tokens;
	size_t pos = 0;
	std::string token;
	while ((pos = sent.find(',')) != std::string::npos)
	{
		token = sent.substr(0, pos);
		sent.erase(0, pos + 1);
		tokens.push_back(token);
	}
	
	// tokens[0] == our message type (We remove the $, as its unnecessary and redundant
	std::string msgType = tokens[0].substr(1,std::string::npos);
	// We have previously created our parser
	if (parsers.find(msgType) != parsers.end())
	{
		return parsers[msgType]->Parse(tokens);
	}
	else
	{
		if (msgType == "GPGGA")
		{
			ParserBase* parser = new ParserGPGGA(robotLib);
			parsers.insert(std::make_pair<std::string, ParserBase*>((std::string)msgType, (ParserBase*)parser));
			return parsers[msgType]->Parse(tokens);
		}
		if (msgType == "GPGLL")
		{
			ParserBase* parser = new ParserGPGLL(robotLib);
			parsers.insert(std::make_pair<std::string, ParserBase*>((std::string)msgType, (ParserBase*)parser));
			return parsers[msgType]->Parse(tokens);		
		}
		if (msgType == "GPRMC")
		{
			ParserBase* parser = new ParserGPRMC(robotLib);
			parsers.insert(std::make_pair<std::string,ParserBase*>((std::string)msgType, (ParserBase*)parser));
			return parsers[msgType]->Parse(tokens);
		}		
		if (msgType == "GPGSV")
		{
			ParserBase* parser = new ParserGPGSV(robotLib);
			parsers.insert(std::make_pair<std::string, ParserBase*>((std::string)msgType, (ParserBase*)parser));
			return parsers[msgType]->Parse(tokens);
		}
		if (msgType == "GPVTG")
		{
			ParserBase* parser = new ParserGPVTG(robotLib);
			parsers.insert(std::make_pair<std::string, ParserBase*>((std::string)msgType, (ParserBase*)parser));
			return parsers[msgType]->Parse(tokens);
		}
	}
}

NMEAParser::~NMEAParser()
{
	parserMap_t::iterator p;
	std::stringstream ss;
	for (p = parsers.begin(); p != parsers.end(); p++)
	{
		ss.clear();
		ss << "Destroying parser: " << p->second->getName();		
		robotLib->Log(ss.str());
		delete(p->second);
	}
	parsers.clear();
}