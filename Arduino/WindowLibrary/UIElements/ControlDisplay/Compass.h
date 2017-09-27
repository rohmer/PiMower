#pragma once
#include "../../Options.h"

#ifdef FT8XX
#include "../FT8XX/UIPrimitives.h"
#endif
#ifdef RA8875
#include "../RA8875/UIPrimitives.h"
#endif

class Compass
{
public:
	static Rectangle Draw(DriverBase &tft, Rectangle location, float direction,
		tColor controlColor, tColor pointerColor, eUITextFont controlFont,		
		bool showNSEW=true, tColor textColor = Color::White);
private:
	enum eAngle
	{
		N = 0,
		E = 1,
		S = 2,
		W = 3,
		NE = 4,
		SE = 5,
		SW = 6,
		NW = 7
	};
	static void DrawCompassTriangle(DriverBase &tft, eAngle angle, Point centerPoint, 
		uint16_t length, uint16_t centerRadius, tColor color, tColor color2);
	static uint16_t angleMath(uint16_t startAngle, int adjustment);
	static double degrees_to_radian(double deg)
	{
		return deg * M_PI / 180.0;
	};
};
