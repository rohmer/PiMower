#pragma once
#pragma once
#include <map>
#include <vector>
#include <string>
#include "Utility/Color.h"
#include "UIElements/UIElement.h"
#include <SPI.h>

class MowerStats
{
public:
	static void Draw(DriverBase &tft,std::string nextSchedule, int degreesLat, int degreesLon, 
		uint32_t minutesLat, uint32_t minutesLon, std::string cardnialLat, std::string cardinalLon, 
		uint8_t numGPSSats, Point location);
};