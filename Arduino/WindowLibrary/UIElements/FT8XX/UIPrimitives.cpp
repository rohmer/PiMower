#include "UIPrimitives.h"

#ifdef FT8XX
Rectangle UIPrimitives::SunkenPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t cornerRadius, uint32_t color, uint8_t alpha)
{
	uint16_t lw = (cornerRadius << 4) + 8;
	uint16_t x0 = (x << 2) + (cornerRadius << 2) + 4;
	uint16_t y0 = (y << 2) + (cornerRadius << 2) + 4;
	uint16_t x1 = (x << 2) + (width << 2) - 4 - (cornerRadius << 2);
	uint16_t y1 = (y << 2) + (height << 2) - 4 - (cornerRadius << 2);
	GD.ColorA(alpha);
	GD.Begin(RECTS);
#ifdef FT81X
	GD.VertexFormat(2);
#endif
	GD.ColorRGB(0xFFFFFF);
	GD.LineWidth(lw);
	GD.Vertex2f(x0 + 2, y0 + 2);
	GD.Vertex2f(x1 + 4, y1 + 4);
	GD.ColorRGB(0x000000);
	GD.Vertex2f(x0 - 5, y0 - 5);
	GD.Vertex2f(x1 - 1, y1 - 1);
	GD.ColorRGB(color);
	GD.Vertex2f(x0 - 2, y0 - 2);
	GD.Vertex2f(x1 + 2, y1 + 2);
	GD.End();
	GD.swap();
	return (Rectangle(x0 - 5, y0 - 5, x1 + 2, y1 + 2));
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
	GD.End();
	GD.swap();
	return (Rectangle(x0 - 5, y0 - 5, x1 + 3, y1 + 3));
}

Rectangle UIPrimitives::FlatPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
	uint8_t cornerRadius, uint32_t color, uint8_t alpha = 255)
{
	GD.ColorA(alpha);
	GD.ColorRGB(color);
	GD.Begin(RECTS);
	GD.Vertex2f(x, y);
	GD.Vertex2f(x + width, y);
	GD.Vertex2f(x + width, y + height);
	GD.Vertex2f(x, y + height);
	GD.End();
	GD.swap();
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
	GD.End();
	GD.swap();
	return (Rectangle(x2 - 3 - ps, y2 - 3 - ps, x2 + 2 + ps, y2 + 2 + ps));
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
	GD.End();
	GD.swap();
	return (Rectangle(x2 - 2 - ps, y2 - 2 - ps, x2 + 4 + ps, y2 + 4 + ps));
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
	GD.End();
	GD.swap();
	return (Rectangle(x2 - ps, y2 - ps, x2 + ps, y2 + ps));
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
	baseRect.x2 += 2;
	baseRect.y2 += 2;
	GD.swap();
	return (baseRect);
}

Rectangle Polygon(DriverBase &tft, std::vector<Point> points, uint16_t color, uint8_t alpha)
{
	Rectangle s(0,0,0,0);
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
	GD.swap();
}
#endif