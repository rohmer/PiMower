#include "UIPrimitives.h"

#ifdef RA8875
Rectangle UIPrimitives::SunkenPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
	uint8_t cornerRadius, uint32_t color)
{
	uint16_t lw = (cornerRadius << 4) + 8;
	uint16_t x0 = (x << 2) + (cornerRadius << 2) + 4;
	uint16_t y0 = (y << 2) + (cornerRadius << 2) + 4;
	uint16_t x1 = (x << 2) + (width << 2) - 4 - (cornerRadius << 2);
	uint16_t y1 = (y << 2) + (height << 2) - 4 - (cornerRadius << 2);
	
	if(cornerRadius>0)
		tft.drawRoundRect(x0 + 2, y0 + 2, ((x1 + 4) - (x0 + 2)), ((y0 + 2) - (y1 + 4)), cornerRadius, 0xFFFFFF);
	else
		tft.drawRect(x0 + 2, y0 + 2, ((x1 + 4) - (x0 + 2)), ((y0 + 2) - (y1 + 4)), 0xFFFFFF);
	if(cornerRadius>0)
		tft.drawRoundRect(x0 - 5, y0 - 5, ((x1 - 1) - (x0 - 5)), ((y1 - 1) - (y0 - 5)), cornerRadius, 0x000000);
	else
		tft.drawRect(x0 - 5, y0 - 5, ((x1 - 1) - (x0 - 5)), ((y1 - 1) - (y0 - 5)), 0x000000);
	if(cornerRadius>0)
		tft.drawRoundRect(x0 - 2, y0 - 2, ((x1 + 2) - (x0 - 2)), ((y1 + 2) - (y0 - 2)), cornerRadius, 
			Color::Color32To565(color));	
	else
		tft.drawRect(x0 - 2, y0 - 2, ((x1 + 2) - (x0 - 2)), ((y1 + 2) - (y0 - 2)),
			Color::Color32To565(color));
	return (Rectangle(x0 - 5, y0 - 5, x1 + 2, y1 + 2));
}

Rectangle UIPrimitives::RaisedPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
	uint8_t cornerRadius, uint32_t color)
{
	uint16_t lw = (cornerRadius << 4) + 12;
	uint16_t x0 = (x << 2) + (cornerRadius << 2) + 6;
	uint16_t y0 = (y << 2) + (cornerRadius << 2) + 6;
	uint16_t x1 = (x << 2) + (width << 2) - 6 - (cornerRadius << 2);
	uint16_t y1 = (y << 2) + (height << 2) - 6 - (cornerRadius << 2);
	if (cornerRadius>0)
		tft.drawRoundRect(x0 + 1, y0 + 1, ((x1 + 7) - (x0 + 1)), ((y0 + 7) - (y1 + 1)), cornerRadius, 0x000000);
	else
		tft.drawRect(x0 + 1, y0 + 1, ((x1 + 7) - (x0 + 1)), ((y0 + 7) - (y1 + 1)), 0x000000);
	if (cornerRadius>0)
		tft.drawRoundRect(x0 - 5, y0 - 5, ((x1 + 1) - (x0 - 5)), ((y1 + 1) - (y0 - 5)), cornerRadius, 0xFFFFFF);
	else
		tft.drawRect(x0 - 5, y0 - 5, ((x1 + 1) - (x0 - 5)), ((y1 + 1) - (y0 - 5)), 0xFFFFFF);
	if (cornerRadius>0)
		tft.drawRoundRect(x0 - 3, y0 - 3, ((x1 + 3) - (x0 - 3)), ((y1 + 3) - (y0 - 3)), cornerRadius,
			Color::Color32To565(color));
	else
		tft.drawRect(x0 - 3, y0 - 3, ((x1 + 3) - (x0 - 3)), ((y1 + 3) - (y0 - 3)), 
			Color::Color32To565(color));	
	return (Rectangle(x0 - 5, y0 - 5, x1 + 3, y1 + 3));
}

Rectangle UIPrimitives::FlatPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
	uint8_t cornerRadius, uint32_t color, uint8_t alpha = 255)
{
	if (cornerRadius > 0)
		tft.drawRoundRect(x, y, width, height, cornerRadius, Color::Color32To565(color));
	else
		tft.drawRect(x, y, width, height, Color::Color32To565(color));
	return Rectangle(x, y, x + width, y + height);
}

Rectangle UIPrimitives::CircleSunken(DriverBase &tft, uint32_t color, uint16_t x, uint16_t y,
	uint16_t radius)
{
	uint16_t ps = (radius << 4);
	uint16_t x2 = (x << 2);
	uint16_t y2 = (y << 2);
	tft.fillCircle(x2 + 2, y2 + 2, radius, 0xFFFFFF);
	tft.fillCircle(x2 - 3, y2 - 3, radius, 0x000000);
	tft.fillCircle(x2, y2, radius, 0x000000);
	return (Rectangle(x2 - 3 - ps, y2 - 3 - ps, x2 + 2 + ps, y2 + 2 + ps));
}

Rectangle UIPrimitives::CircleRaised(DriverBase &tft, uint32_t color, uint16_t x, uint16_t y,
	uint16_t radius)
{
	uint16_t ps = (radius << 4);
	uint16_t x2 = (x << 2);
	uint16_t y2 = (y << 2);
	tft.fillCircle(x2 + 4, y2 + 4, radius, 0x000000);
	tft.fillCircle(x2 - 2, y2 - 2, radius, 0xFFFFFF);
	tft.fillCircle(x2, y2, radius, color);	
	return (Rectangle(x2 - 2 - ps, y2 - 2 - ps, x2 + 4 + ps, y2 + 4 + ps));
}

Rectangle UIPrimitives::CircleFlat(DriverBase &tft, uint32_t color, uint16_t x, uint16_t y,
	uint16_t radius)
{
	uint16_t ps = (radius << 4);
	uint16_t x2 = (x << 2);
	uint16_t y2 = (y << 2);
	tft.fillCircle(x2, y2, radius, color);	
	return (Rectangle(x2 - ps, y2 - ps, x2 + ps, y2 + ps));
}

Rectangle UIPrimitives::Text(DriverBase & tft, uint32_t color, uint8_t alpha, uint16_t x, uint16_t y, 
	uint8_t font, bool dropShadow, std::string text)
{
	// We need to center the text on x,y
	Rectangle baseRect = FontHelper::GetTextRect(tft, text, (eUITextFont)font, Point(x, y));
	Point centerPt = baseRect.center();
	if (dropShadow)
	{
		tft.textWrite(centerPt.x + 2, centerPt.y + 2, (eUITextFont)font, Color::Color32To565(0x000000), 0, text);
	}
	tft.textWrite(centerPt.x, centerPt.y, (eUITextFont)font, Color::Color32To565(color), 0, text);
	
	baseRect.x2 += 2;
	baseRect.y2 += 2;
	return (baseRect);
}

#endif