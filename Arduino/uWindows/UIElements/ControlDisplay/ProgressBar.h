#pragma once
#pragma once
#include "../../Options.h"

#ifdef FT8XX
#include "../FT8XX/UIPrimitives.h"
#endif
#ifdef RA8875
#include "../RA8875/UIPrimitives.h"
#endif

class ProgressBar
{
public:
	static Rectangle Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width,
		uint16_t height, uint8_t progress, int32_t textColor, uint32_t barBGColor, uint32_t barProgressColor, eUITextFont font, 
		bool is3D = true, uint8_t cornerRadius = 4, uint8_t alpha = 255);
	static Rectangle Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width,
		uint16_t height, uint8_t progress, uint32_t barBGColor, uint32_t barProgressColor,
		bool is3D = true, uint8_t cornerRadius = 4, uint8_t alpha = 255);

};

