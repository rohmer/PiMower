#include "UIPrimitives.h"

#ifdef RA8875
Rectangle UIPrimitives::SunkenPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
	uint8_t cornerRadius, uint32_t color, uint8_t alpha)
{
	// First draw the bg color
	if (cornerRadius > 0)
		tft.drawRoundRect(x, y, width, height, cornerRadius, Color::Color32To565(color));
	else
		tft.drawRect(x, y, width, height, Color::Color32To565(color));
	uint8_t shadowOffset = height / 5;
	if (height > width)
		shadowOffset = width / 5;
	if (shadowOffset > 4)
		shadowOffset = 4;
	if (shadowOffset < 1)
		shadowOffset = 1;
	// Now draw the indention
	if (cornerRadius > 0)
	{
		drawHLine(tft, x + cornerRadius + shadowOffset, y + shadowOffset, 
			width - 2 * (cornerRadius + shadowOffset), Color::Gray192); // Top
		drawHLine(tft, x + cornerRadius + shadowOffset, y + shadowOffset+1, 
			width - 2 * (cornerRadius + shadowOffset), Color::Gray192); // Top
		drawHLine(tft, x + cornerRadius + shadowOffset, y + shadowOffset+2, 
			width - 2 * (cornerRadius + shadowOffset), Color::Gray192); // Top
		
		drawHLine(tft, x+ cornerRadius + shadowOffset  , y+height-(1+shadowOffset),
			width-2*(cornerRadius+shadowOffset), Color::Gray160); // Bottom

		// Ok, we need to average the color on the vertical from 0x111111 to 0xAAAAAA on the right and left
		float diffPerPixel = (Color::Gray160 - Color::Gray192) / (height - 2 * (cornerRadius + shadowOffset));
		
		uint32_t lineColor = 0x111111;
		for (int i = 0; i < (height - 2 * (cornerRadius + shadowOffset)); i++)
		{
			tft.drawPixel(x + width - (1 + shadowOffset), y + cornerRadius + shadowOffset+i, lineColor); // Right
			tft.drawPixel(x + shadowOffset, y + cornerRadius + shadowOffset+i, lineColor);				// Left
			lineColor += diffPerPixel;
		}

		 // Now draw the curves
		// Upper Left
		drawCircleHelper(tft, x + cornerRadius + shadowOffset, y + cornerRadius + shadowOffset, 
			cornerRadius, 1, Color::Gray192);		
		// Upper Right
		drawCircleHelper(tft, x + width - cornerRadius - shadowOffset -1, y + cornerRadius + shadowOffset, 
			cornerRadius, 1, Color::Gray192);		
		// Lower Right
		drawCircleHelper(tft, x + width - cornerRadius - shadowOffset -1, 
			y + height-cornerRadius-shadowOffset-1,	cornerRadius, 1, 
			Color::Color32To565(0x999999));		
		// Lower Left
		drawCircleHelper(tft, x + cornerRadius+shadowOffset, y + height-cornerRadius-shadowOffset-1,
			cornerRadius, 1, Color::Color32To565(0x999999));				
	}
	else  
	{
		// Square Corners
		drawHLine(tft, x + shadowOffset, y+shadowOffset, 
			width - 2 * shadowOffset, Color::Gray192); // Top
		drawHLine(tft, x + shadowOffset, y+shadowOffset+1, 
			width - 2 * shadowOffset, Color::Gray192); // Top
		drawHLine(tft, x + shadowOffset, y+shadowOffset+2, 
			width - 2 * shadowOffset, Color::Gray192); // Top
		drawHLine(tft, x+ shadowOffset  , y+height-(1+shadowOffset),
			width-2*shadowOffset, Color::Gray160); // Bottom
		// Ok, we need to average the color on the vertical from 0x111111 to 0xAAAAAA on the right and left
		float diffPerPixel = (Color::Gray160 - Color::Gray192) / (height - 2 * (cornerRadius + shadowOffset));
		
		uint32_t lineColor = 0x111111;
		for (int i = 0; i < (height - 2 * shadowOffset); i++)
		{
			tft.drawPixel(x + width - (1 + shadowOffset), y + shadowOffset + i, lineColor); // Right
			tft.drawPixel(x + shadowOffset, y + shadowOffset + i, lineColor);				// Left
			lineColor += diffPerPixel;
		}
	}
	// Draw BG
	if (cornerRadius > 0)
		tft.fillRoundRect(x + shadowOffset, y + shadowOffset, width - shadowOffset * 2, height - shadowOffset * 2, cornerRadius, color);
	else
		tft.fillRect(x +shadowOffset, y + shadowOffset, width-shadowOffset*2, height - shadowOffset * 2, color);

	Rectangle r = Rectangle(x, y, x + width + shadowOffset, y + height + shadowOffset);
	return (r);
	
}

Rectangle UIPrimitives::RaisedPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
	uint8_t cornerRadius, uint32_t color, uint8_t alpha)
{
#ifdef DEBUG
	Logger::Trace("RaisedPanel(tft,%d,%d,%d,%d,%d,%d,%d)",
		x, y, width, height, cornerRadius, color, alpha);
#endif
	uint8_t shadowOffset = height / 5;
	if (height > width)
		shadowOffset = width / 5;
	if (shadowOffset > 4)
		shadowOffset = 4;
	if (shadowOffset < 1)
		shadowOffset = 1;
	if (cornerRadius > 0)
	{		
		tft.fillRect(x + shadowOffset, y + shadowOffset, width, height, Color::Black);		
	}
	else
		tft.fillRect(x+shadowOffset,y+shadowOffset,width,height,  Color::Black);
	if (cornerRadius>0)
		tft.fillRoundRect(x,y, width,height, cornerRadius,
			color);
	else
		tft.fillRect(x,y,width,height,
			color);	
	Rectangle r = Rectangle(x, y, x + width+shadowOffset, y + height+shadowOffset);
	return (r);
}

Rectangle UIPrimitives::FlatPanel(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
	uint8_t cornerRadius, uint32_t color, uint8_t alpha)
{
	if (cornerRadius > 0)
		tft.fillRoundRect(x, y, width, height, cornerRadius, color);
	else
		tft.fillRect(x, y, width, height, color);
	return Rectangle(x, y, x + width, y + height);
}

Rectangle UIPrimitives::CircleSunken(DriverBase &tft, uint32_t color, uint8_t alpha, 
	uint16_t x, uint16_t y, uint16_t radius)
{
	uint8_t dropShadow = radius / 5;
	if (dropShadow > 4)
		dropShadow = 4;
	tft.fillCircle(x - dropShadow, y - dropShadow, radius, Color::Black);
	tft.fillCircle(x, y, radius, color);
	return (Rectangle(x-dropShadow, y-dropShadow, x + radius - dropShadow, y + radius - dropShadow));
}

Rectangle UIPrimitives::CircleRaised(DriverBase &tft, uint32_t color, uint8_t alpha, 
	uint16_t x, uint16_t y, uint16_t radius)
{
	uint8_t dropShadow = radius / 5;
	if (dropShadow > 4)
		dropShadow = 4;
	tft.fillCircle(x + dropShadow, y + dropShadow, radius, Color::Black);
	tft.fillCircle(x, y, radius, color);
	return (Rectangle(x,y,x+radius+dropShadow,y+radius+dropShadow));
}

Rectangle UIPrimitives::CircleFlat(DriverBase &tft, uint32_t color, uint8_t alpha, 
	uint16_t x, uint16_t y, uint16_t radius)
{
	tft.fillCircle(x, y, radius, color);	
	return (Rectangle(x-radius, y-radius, x + radius, y+radius));
}

Rectangle UIPrimitives::Text(DriverBase &tft, uint32_t color, uint8_t alpha, uint16_t x, uint16_t y, uint8_t font,
		bool dropShadow, std::string text, eTextHJustify justify)
{
	// We need to center the text on x,y
	Rectangle baseRect = FontHelper::GetTextRect(tft, text, (eUITextFont)font, Point(x, y));
#ifdef DEBUG
	Logger::Trace("Text: %s", text.c_str());
	Logger::Trace("Font Rect: (%d,%d,%d,%d), Width: %d, Height: %d", 
		baseRect.x1, baseRect.y1, baseRect.x2, baseRect.y2, baseRect.width, baseRect.height);
#endif
	Point *drawPoint;
	switch (justify)
	{
	case(eTextHJustify::Left):
		drawPoint = new Point(x,y);
		break;
	case(eTextHJustify::Center):
		drawPoint = new Point(baseRect.x1, y+baseRect.height/2 );
		break;
	case(eTextHJustify::Right):
		drawPoint = new Point(x + baseRect.width*2, y - baseRect.height / 2);
		break;
	}
	
	if (dropShadow)
	{
		tft.textWrite(drawPoint->x + 2, drawPoint->y + 2, (eUITextFont)font, Color::Black, 0, text);
	}
	tft.textWrite(drawPoint->x, drawPoint->y, (eUITextFont)font, color, 0, text);
	delete (drawPoint);
	
	baseRect.x2 += 2;
	baseRect.y2 += 2;
	return (baseRect);
}

Rectangle UIPrimitives::Polygon(DriverBase &tft, std::vector<Point> points, uint16_t color, uint8_t alpha)
{
	// Lazy hack for now
	if (points.size() != 3)
		return;
	tft.fillTriangle(points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y, color);
}

void UIPrimitives::drawVLine(DriverBase &tft, int16_t x, int16_t y, int16_t h, int16_t color)
{
	tft.drawLine(x, y, x, y + h - 1, color);
}

void UIPrimitives::drawHLine(DriverBase &tft, int16_t x, int16_t y, int16_t w, int16_t color)
{
	tft.drawLine(x, y, x + w - 1, y, color);
}

void UIPrimitives::drawCircleHelper(DriverBase &tft,uint16_t x0, uint16_t y0, 
	uint8_t r, uint8_t corner, uint16_t color)
{
	int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;
	    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (corner & 0x4) {
            tft.drawPixel(x0 + x, y0 + y, color);
            tft.drawPixel(x0 + y, y0 + x, color);
        }
        if (corner & 0x2) {
            tft.drawPixel(x0 + x, y0 - y, color);
            tft.drawPixel(x0 + y, y0 - x, color);
        }
        if (corner & 0x8) {
            tft.drawPixel(x0 - y, y0 + x, color);
            tft.drawPixel(x0 - x, y0 + y, color);
        }
        if (corner & 0x1) {
            tft.drawPixel(x0 - y, y0 - x, color);
            tft.drawPixel(x0 - x, y0 - y, color);
        }
    }
}
#endif
