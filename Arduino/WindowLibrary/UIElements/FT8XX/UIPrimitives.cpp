#include "UIPrimitives.h"

#ifdef FT8XX
Rectangle UIPrimitives::SunkenPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t cornerRadius, uint32_t color, uint8_t alpha)
{
	uint32_t lw = ((uint32_t)cornerRadius << 4) + 8;
	uint32_t x0 = ((uint32_t)x << 2) + ((uint32_t)cornerRadius << 2) + 4;
	uint32_t y0 = ((uint32_t)y << 2) + ((uint32_t)cornerRadius << 2) + 4;
	uint32_t x1 = ((uint32_t)x << 2) + ((uint32_t)width << 2) - 4 - ((uint32_t)cornerRadius << 2);
	uint32_t y1 = ((uint32_t)y << 2) + ((uint32_t)height << 2) - 4 - ((uint32_t)cornerRadius << 2);
	GD.Begin(RECTS);
#ifdef FT81X
	GD.VertexFormat(2);
#endif
	GD.ColorA(alpha);
	GD.ColorRGB(0xFFFFFF);
	GD.LineWidth(lw);
	GD.Vertex2f(x0 + 2, y0 + 2);	
	GD.Vertex2f(x1 + 4, y1 + 4);
	GD.Vertex2f(x0 + 3, y0 + 3);
	GD.Vertex2f(x1 + 5, y1 + 5);
	GD.ColorRGB(0x000000);
	GD.Vertex2f(x0 - 5, y0 - 5);
	GD.Vertex2f(x1 - 1, y1 - 1);
	GD.ColorRGB(0x111111);
	GD.Vertex2f(x0 - 6, y0 - 6);
	GD.Vertex2f(x1 - 2, y1 - 2);
	GD.ColorRGB(color);
	GD.Vertex2f(x0 - 3, y0 - 3);
	GD.Vertex2f(x1 + 1, y1 + 1);	
	return (Rectangle(x,y,x+width,y+height));
}

Rectangle  UIPrimitives::RaisedPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t cornerRadius, uint32_t color, uint8_t alpha)
{
	uint16_t lw = (cornerRadius << 4) + 12;
	uint16_t x0 = (x << 2) + (cornerRadius << 2) + 6;
	uint16_t y0 = (y << 2) + (cornerRadius << 2) + 6;
	uint16_t x1 = (x << 2) + (width << 2) - 6 - (cornerRadius << 2);
	uint16_t y1 = (y << 2) + (height << 2) - 6 - (cornerRadius << 2);
	GD.ColorA(alpha);
	GD.Begin(RECTS);
#ifdef FT81X
	GD.VertexFormat(2);
#endif
	GD.ColorRGB(0x000000);
	GD.LineWidth(lw);
	GD.Vertex2f(x0 + 1, y0 + 1);
	GD.Vertex2f(x1 + 7, y1 + 7);
	GD.ColorRGB(0xFFFFFF);
	GD.Vertex2f(x0 - 5, y0 - 5);
	GD.Vertex2f(x1 + 1, y1 + 1);
	GD.ColorRGB(color);
	GD.Vertex2f(x0 - 3, y0 - 3);
	GD.Vertex2f(x1 + 3, y1 + 3);	
	return (Rectangle(x, y, x+width, y+height));
}

Rectangle UIPrimitives::FlatPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
	uint8_t cornerRadius, uint32_t color, uint8_t alpha = 255)
{
	tft.colorA(alpha);
	if (cornerRadius > 0)
		tft.fillRoundRect(x, y, width, height, cornerRadius, color);
	else
		tft.fillRect(x, y, width, height, color);
	return Rectangle(x, y, x + width, y + height);
}

Rectangle  UIPrimitives::CircleSunken(DriverBase &tft, uint32_t color, uint8_t alpha, uint16_t x, uint16_t y, uint16_t radius)
{
	uint16_t ps = (radius << 4);
	uint16_t x2 = (x << 2);
	uint16_t y2 = (y << 2);
	GD.Begin(POINTS);
#ifdef FT81X
	GD.VertexFormat(2);
#endif
	GD.PointSize(ps);
	GD.ColorA(alpha);
	GD.ColorRGB(0xFFFFFF);
	GD.Vertex2f(x2 + 2, y2 + 2);
	GD.ColorRGB(0x000000);
	GD.Vertex2f(x2 - 3, y2 - 3);
	GD.ColorRGB(color);
	GD.Vertex2f(x2, y2);	
	return (Rectangle(x-radius,y-radius,x+radius,y+radius));
}

Rectangle  UIPrimitives::CircleRaised(DriverBase &tft, uint32_t color, uint8_t alpha, uint16_t x, uint16_t y, uint16_t radius)
{
	uint16_t ps = (radius << 4);
	uint16_t x2 = (x << 2);
	uint16_t y2 = (y << 2);
	GD.Begin(POINTS);
#ifdef FT81X
	GD.VertexFormat(2);
#endif
	GD.PointSize(ps);
	GD.ColorA(alpha);
	GD.ColorRGB(0x000000);
	GD.Vertex2f(x2 + 4, y2 + 4);
	GD.ColorRGB(0xFFFFFF);
	GD.Vertex2f(x2 - 2, y2 - 2);
	GD.ColorRGB(color);
	GD.Vertex2f(x2, y2);	
	return (Rectangle(x - radius, y - radius, x + radius, y + radius));
}

Rectangle  UIPrimitives::CircleFlat(DriverBase &tft, uint32_t color, uint8_t alpha, uint16_t x, uint16_t y, uint16_t radius)
{
	uint16_t ps = (radius << 4);
	uint16_t x2 = (x << 2);
	uint16_t y2 = (y << 2);
	GD.Begin(POINTS);
#ifdef FT81X
	GD.VertexFormat(2);
#endif
	GD.PointSize(ps);
	GD.ColorA(alpha);
	GD.ColorRGB(color);
	GD.Vertex2f(x2, y2);	
	return (Rectangle(x - radius, y - radius, x + radius, y + radius));
}

Rectangle  UIPrimitives::Text(DriverBase &tft, uint32_t color, uint8_t alpha, uint16_t x, uint16_t y, uint8_t font,
		bool dropShadow, std::string text, eTextHJustify justify)
{
	GD.ColorA(alpha);
	uint16_t just;
	switch (justify)
	{
	case(eTextHJustify::Left):
		just = 0;
		break;
	case(eTextHJustify::Center):
		just = OPT_CENTERX;
		break;
	case(eTextHJustify::Right):
		just = OPT_RIGHTX;
		break;
	}
	if (dropShadow)
	{
		GD.ColorRGB(0x000000);
		GD.cmd_text(x+2, y+2, font, just, text.c_str());	
	}
	GD.ColorRGB(color);
	GD.cmd_text(x, y, font, just, text.c_str());
	Rectangle baseRect = FontHelper::GetTextRect(tft, text, (eUITextFont)font, Point(x, y));
	if (dropShadow)
	{
		baseRect.x2 += 2;
		baseRect.y2 += 2;
	}
	return (baseRect);
}

Rectangle UIPrimitives::Polygon(DriverBase & tft, std::vector<Point> points, tColor color, uint8_t alpha)
{
	Rectangle s(0, 0, 0, 0);
	GD.ColorA(alpha);
	GD.ColorRGB(color);
	Poly po;
	po.begin();
	for (int i = 0; i < points.size(); i++)
	{
		if (points[i].x < s.x1)
			s.x1 = points[i].x;
		if (points[i].x > s.x2)
			s.x2 = points[i].x;
		if (points[i].y < s.y1)
			s.y1 = points[i].x;
		if (points[i].y > s.y2)
			s.y2 = points[i].y;
		po.v(16 * points[i].x, 16 * points[i].y);
	}
	po.draw();	
	return s;
}

#endif