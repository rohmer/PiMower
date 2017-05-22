#include "RingMeter.h"

#ifdef RA8875
//void RA8875::ringMeter(int val, int minV, int maxV, int16_t x, int16_t y, uint16_t r, 
//						const char* units, uint16_t colorScheme,uint16_t backSegColor,int16_t angle,uint8_t inc)


void RingMeter::Draw(DriverBase &tft, eUITextFont font, int value, int minValue, int maxValue,
	int16_t x, int16_t y, int16_t radius, std::string units, uint16_t colorScheme, uint16_t segmentColor,
	int16_t angle, uint8_t increment, uint16_t textColor, int textShiftY)		// TODO: Make yShift shift the text, up or down
{
	if (increment < 5)
		increment = 5;
	if (increment > 20)
		increment = 20;
	if (radius < 50)
		radius = 50;
	if (angle < 90)
		angle = 90;
	if (angle > 180)
		angle = 180;

	int curAngle = map(value, minValue, maxValue, -angle, angle);
	uint16_t color;

	x += radius;
	y += radius;						// Calculate coords of center ring;
	uint16_t w = radius / 4;			// Width of the outer ring is 1/4 the radius
	const uint8_t seg = 5;				// Segments are 5 degrees wide = 60 segments for 300 degrees
	// Draw color blocks every inc degrees
	for (int16_t i = -angle; i < angle; i += increment)
	{
		color = Color::Black;
		switch (colorScheme)
		{
		case 0:
			color = Color::Red;
			break;
		case 1:
			color = Color::Green;
			break;
		case 2:
			color = Color::Blue;
			break;
		case 3:
			color = gradient(map(i, -angle, angle, 0, 127));
			break;		// Full spectrum Blue to Red
		case 4:
			color = gradient(map(i, -angle, angle, 63, 127));
			break;		// Green to red
		case 5:
			color = gradient(map(i, -angle, angle, 127, 63));
			break;		// Red to Green (Battery level, ex)
		case 6:
			color = gradient(map(i, -angle, angle, 127, 0));
			break;		// Red to blue
		case 7:
			color = gradient(map(i, -angle, angle, 35, 127));
			break;		// Cyan to red
		case 8:
			color = tft.colorInterpolation565(0, 0, 0, 255, 255, 255, map(i, -angle, angle, 0, w), w);
			break;		// Black to white
		case 9:
			color = tft.colorInterpolation565(0x80, 0, 0xC0, 0xFF, 0xFF, 0, map(i, -angle, angle, 0, w), w);
			break;		// Violet to yellow
		default:
			if (colorScheme > 9)
				color = colorScheme;
			else
				color = Color::Blue;
			break;		// Fixed color;
		}
		float xStart = cos((i - 90)*0.0174532925);
		float yStart = sin((i - 90)*0.0174532925);
		uint16_t x0 = xStart*(radius - w) + x;
		uint16_t y0 = yStart * (radius - w) + y;
		uint16_t x1 = xStart * radius + x;
		uint16_t y1 = yStart * radius + y;
		
		// Calculate pair of coordinates for segment end
		float xEnd = cos((i + seg - 90) * 0.0174532925);
		float yEnd = sin((i + seg - 90) * 0.0174532925);
		int16_t x2 = xEnd * (radius - w) + x;
		int16_t y2 = yEnd * (radius - w) + y;
		int16_t x3 = xEnd * radius + x;
		int16_t y3 = yEnd * radius + y;
		if (i < curAngle)			
		{ // Fill in colored segments with 2 triangles
			tft.fillQuad(x0, y0, x1, y1, x2, y2, x3, y3, color, false);
		}
		else 
		{
			// Fill in blank segments
			tft.fillQuad(x0, y0, x1, y1, x2, y2, x3, y3, segmentColor, false);
		}	
	}
	// text

	if (units!="none") 
	{
		//erase internal background
		if (angle > 90) 
		{
			tft.fillCircle(x, y, radius - w, tft.getBackgroundColor());
		}
		else
		{
			tft.fillCurve(x, y + FontHelper::GetTextRect(tft,"T",font,Point(0,0)).height / 2, radius - w, radius - w, 1, tft.getBackgroundColor());
			tft.fillCurve(x, y + FontHelper::GetTextRect(tft, "T", font, Point(0, 0)).height / 2, radius - w, radius - w, 2, tft.getBackgroundColor());
		}

		//prepare for write text
		if (radius > 84) 
		{
			tft.setTextSize(1);
		}
		else 
		{
			tft.setTextSize(0);
		}
		std::stringstream ss;
		ss << value;
		ss << " ";
		ss << units;

		uint16_t width = FontHelper::GetTextRect(tft, ss.str(), font, Point(0, 0)).width / 2;

		if (!tft.isLandscape()) 
		{
			UIPrimitives::Text(tft, textColor, 255, y-width-textShiftY, x, font, true, ss.str());
		}
		else 
		{
			UIPrimitives::Text(tft, textColor, 255, x-width, y-textShiftY, font, true, ss.str());
		}
	}
}
 
uint16_t RingMeter::gradient(uint8_t val)
{
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t q = val / 32;
	switch (q)
	{
	case 0:
		r = 0; g = 2 * (val % 32); b = 31;
		break;
	case 1:
		r = 0; g = 63; b = 31 - (val % 32);
		break;
	case 2:
		r = val % 32; g = 63; b = 0;
		break;
	case 3:
		r = 31; g = 63 - 2 * (val % 32); b = 0;
		break;
	}
	return (r << 11) + (g << 5) + b;
}

#endif