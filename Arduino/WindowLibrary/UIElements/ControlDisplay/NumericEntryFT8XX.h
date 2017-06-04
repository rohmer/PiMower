#pragma once
#pragma once

#include "../../Options.h"

#ifdef FT8XX
#ifdef useNumericEntry
#include <map>
#include "../../Utility/Rectangle.h"
#include "../../Driver/FT8XXDriver.h"
#include "../../Utility/FontHelper.h"
#include "../FT8XX/UIPrimitives.h"
class NumericEntry
{
public:
	static Rectangle Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t controlColor,
		uint16_t controlBGColor, uint16_t textColor, eUITextFont font, std::string initialValue,
		bool is3D = true, uint8_t cornerRadius = 4, uint8_t alpha=255, bool singleDecimal=true);	

	static void DrawKeys(DriverBase &tft, uint16_t x, uint16_t y, uint16_t controlColor,
		uint16_t textColor, eUITextFont font, bool is3D = true, bool periodActive=true, 
		bool singleDecimal=true);

	static void UpdateInput(DriverBase &tft, uint16_t x, uint16_t y, uint16_t controlBGColor,
		uint16_t textColor, eUITextFont font, std::string inputValue, bool is3D = true);
	static std::string ProcessTouch(DriverBase &tft, std::string value, uint16_t x, uint16_t y, 
		Point pt, bool &complete, bool singleDecimal);
};



#endif
#endif
