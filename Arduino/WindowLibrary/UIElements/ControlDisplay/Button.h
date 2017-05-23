#pragma once
#include "../../Options.h"

#if defined(useButton) || defined(useActiveButton)

#include "../../Utility/Color.h"
#ifdef FT8XX
#include "../FT8XX/UIPrimitives.h"
#endif
#ifdef RA8875
#include "../RA8875/UIPrimitives.h"
#endif

class Button
{
public:
	static Rectangle Draw(DriverBase &tft, bool sunken, uint16_t x, uint16_t y, uint16_t width, 
		uint16_t height, int32_t textColor, uint32_t buttonColor, eUITextFont font,	std::string text, 
		bool is3D = true, uint8_t cornerRadius = 4, uint8_t alpha=255);
};

#endif