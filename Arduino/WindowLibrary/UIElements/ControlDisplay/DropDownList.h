#pragma once
#include "../../Options.h"

#ifdef FT8XX
#include "../FT8XX/UIPrimitives.h"
#endif
#ifdef RA8875
#include "../RA8875/UIPrimitives.h"
#endif

class DropDownList
{
public:
	static Rectangle Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
		uint32_t textColor, uint32_t controlBGColor, uint32_t dropDownControlColor, uint8_t alpha,
		uint8_t cornerRadius, eUITextFont font,	std::vector<std::string> items, uint8_t selectedIndex, 
		bool is3D=true, bool dropDownPressed=false);

	static Rectangle DrawExpanded(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
		uint32_t textColor, uint32_t controlBGColor, uint32_t dropDownControlColor, uint8_t alpha,
		uint8_t cornerRadius, eUITextFont font,	std::vector<std::string> items, uint8_t selectedIndex, 
		bool is3D=true);

	static int16_t ProcessTouch(bool isExpanded, Point pt, DriverBase &tft, uint16_t x,
		uint16_t y, uint16_t width, uint16_t height, uint32_t textColor, uint32_t controlBGColor,
		uint32_t dropDownControlColor, uint8_t alpha, uint8_t cornerRadius, eUITextFont font,	
		std::vector<std::string> items, uint8_t selectedIndex, bool is3D=true);

private:
	static Rectangle getMinSize(std::vector<std::string> items, uint16_t width, uint16_t height,
		DriverBase &tft, eUITextFont font);
	static Rectangle getDropDownButton(Rectangle controlLocation);
};
