#pragma once
#include "../../Options.h"

#ifdef FT8XX
#include "../FT8XX/UIPrimitives.h"
#endif
#ifdef RA8875
#include "../RA8875/UIPrimitives.h"
#endif

class CheckBox
{
public:
	static Rectangle Draw(DriverBase &tft, bool sunken, bool isChecked, uint16_t x, uint16_t y,
		uint32_t textColor, uint32_t uncheckedColor, uint32_t checkColor, eUITextFont font,
		std::string text, bool textRight = true, bool is3D = true, uint8_t cornerRadius=4);
};
