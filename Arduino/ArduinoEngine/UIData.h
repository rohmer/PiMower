#pragma once
#include "3rdParty/ArduinoJson/ArduinoJson.h"
#include <string>

#define APRIME 8537
#define BPRIME 7937
#define FIRSTH 37

/// <summary>
/// Class to hold all the data that will be displayed on the main page
/// </summary>
class UIData
{
public:	

	UIData();
	std::string ToJson();
	bool FromJson(std::string jsonString, uint32_t inputHash);

	uint16_t accelX, accelY, accelZ;
	uint16_t heading, roll, pitch;
	uint16_t altitude;
	uint8_t battPct;
	uint32_t minutesLat, minutesLon;
	int degreesLat, degreesLon;
	char cardinalLat, cardinalLon;
	uint8_t gpsSatNum;
	uint32_t hashCode;	
	uint8_t frontSonorIn, leftSonorIn, rightSonorIn, backSonorIn;		// >150 = No object
	uint8_t leftWheel, rightWheel;		// 0 = stationary, 1=forward, 2=reverse
	bool blade;							// false=off, true=on
	std::string nextSchedule;
	bool frontBumper, backBumper;


private:
	uint32_t genHashCode(std::string inputStr);

};