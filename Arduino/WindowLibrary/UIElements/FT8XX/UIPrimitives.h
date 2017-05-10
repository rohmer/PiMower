#pragma once
#include "../../Options.h"

#ifdef FT8XX
#include "StandardCplusplus.h"
#include "../../External/GD3/GD3.h"
#include "Fonts.h"
#include "../../Utility/FontHelper.h"
#include "../../Utility/Rectangle.h"
#include "../../Driver/DriverBase.h"
#include "Arduino.h"

// Defines different drawing primitives used in a bunch of other elements
class UIPrimitives
{
public:
	static Rectangle SunkenPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
		uint8_t cornerRadius, uint32_t color, uint8_t alpha=255);
	static Rectangle RaisedPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
		uint8_t cornerRadius, uint32_t color, uint8_t alpha = 255);
	static Rectangle FlatPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
		uint8_t cornerRadius, uint32_t color, uint8_t alpha = 255);
	static Rectangle CircleSunken(DriverBase &tft, uint32_t color, uint8_t alpha, uint16_t x, uint16_t y, uint16_t radius);
	static Rectangle CircleRaised(DriverBase &tft, uint32_t color, uint8_t alpha, uint16_t x, uint16_t y, uint16_t radius);
	static Rectangle CircleFlat(DriverBase &tft, uint32_t color, uint8_t alpha, uint16_t x, uint16_t y, uint16_t radius);
	static Rectangle Text(DriverBase &tft, uint32_t color, uint8_t alpha, uint16_t x, uint16_t y, uint8_t font,
		bool dropShadow, std::string text);
	static Rectangle Polygon(DriverBase &tft, std::vector<Point> points, uint16_t color, uint8_t alpha);
};

#endif