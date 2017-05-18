#pragma once
#include "../../Options.h"

#ifdef RA8875
#include "../RA8875/UIPrimitives.h"
#include <map>

class TextEntry
{
public:
	enum eKeyboardState
	{
		normal,
		shifted,
		symbols
	};

	static Rectangle Draw(DriverBase &tft, eKeyboardState keyboardState,uint16_t x, 
		uint16_t y, uint16_t controlColor, uint16_t controlBGColor, uint16_t textColor, 
		eUITextFont font, std::string initialValue, uint8_t cornerRadius = 4);
	static std::map<std::string, Rectangle> GetKeyRects(uint16_t x, uint16_t y);
	static void UpdateInput(DriverBase &tft, uint16_t x, uint16_t y, uint16_t controlBGColor,
		uint16_t textColor, eUITextFont font, std::string inputValue);
private:
	std::string standard[5] = {
		"1234567890",
		"abcdefghij",
		"klmnopqrst",
		"uvwxyz!,.@",
		"SPDC"
	};

};

#endif