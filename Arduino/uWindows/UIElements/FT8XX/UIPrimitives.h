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
#include "../../Utility/Color.h"

// TODO: Copy ALL of these to RA8875
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
	static Rectangle CircleOutline(DriverBase &tft, tColor color, uint16_t lineWidth, uint8_t alpha, 
		uint16_t x, uint16_t y, uint16_t radius);
	static Rectangle Text(DriverBase &tft, uint32_t color, uint8_t alpha, uint16_t x, uint16_t y, uint8_t font,
		bool dropShadow, std::string text, eTextHJustify justify=eTextHJustify::Center);

	static Rectangle Polygon(DriverBase &tft, std::vector<Point> points, tColor color, uint8_t alpha);
	static Rectangle DrawLine(DriverBase &tft, uint8_t lineWidth, Point pt1, Point pt2, tColor color, uint8_t alpha);
	static Rectangle DrawPoint(DriverBase &tft, uint8_t pointSize, Point pt1, tColor color, uint8_t alpha);
};

#endif