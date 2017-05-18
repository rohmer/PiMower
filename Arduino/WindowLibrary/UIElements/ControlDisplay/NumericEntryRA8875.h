#pragma once
#include "../../Options.h"

#ifdef RA8875
#include "../RA8875/UIPrimitives.h"
#include <map>

class NumericEntry
{
public:
	static Rectangle Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t controlColor, 
		uint16_t controlBGColor, uint16_t textColor, eUITextFont font, std::string initialValue, 
		bool is3D=true, uint8_t cornerRadius=4);
	static std::map<std::string, Rectangle> GetKeyRects(uint16_t x, uint16_t y);

	static void UpdateInput(DriverBase &tft, uint16_t x, uint16_t y, uint16_t controlBGColor,
		uint16_t textColor, eUITextFont font, std::string inputValue, bool is3D=true);
	
};


#endif
