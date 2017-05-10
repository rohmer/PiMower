#pragma once
#pragma once
#include "../../Options.h"
#include <string>

#ifdef FT8XX
#include "../FT8XX/UIPrimitives.h"
#endif
#ifdef RA8875
#include "../RA8875/UIPrimitives.h"
#endif

// If width>=height horizontal otherwise vertical
class Slider
{
public:
	static Rectangle Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
		uint32_t textColor, uint32_t sliderBarColor, uint32_t sliderControlColor, eUITextFont font,
		int16_t value, int16_t minValue, int16_t maxValue, bool is3D = true, uint8_t cornerRadius = 4,
		uint8_t alpha=255);
	static uint16_t GetValue(Rectangle controlLocation, int16_t minValue, int16_t maxValue, Point pt);
};
