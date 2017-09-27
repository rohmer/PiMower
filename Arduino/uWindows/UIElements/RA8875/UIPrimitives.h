#pragma once
#include "../../Options.h"

#ifdef RA8875
#include "../../Driver/DriverBase.h"
#include "Fonts.h"
#include "../../Utility/FontHelper.h"
#include "../../Utility/Rectangle.h"
#include "../../Utility/Color.h"

// Defines different drawing primitives used in a bunch of other elements
class UIPrimitives
{
public:
	enum eTextHJustify
	{
		Left,
		Center,
		Right
	};

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
		bool dropShadow, std::string text, eTextHJustify justify=eTextHJustify::Center);
	static Rectangle Polygon(DriverBase &tft, std::vector<Point> points, uint16_t color, uint8_t alpha);

private:
	static void drawVLine(DriverBase &tft, int16_t x, int16_t y, int16_t h, int16_t color);
	static void drawHLine(DriverBase &tft, int16_t x, int16_t y, int16_t w, int16_t color);
	static void drawCircleHelper(DriverBase &tft, uint16_t x0, uint16_t y0, uint8_t r, 
		uint8_t corner, uint16_t color);
};

#endif