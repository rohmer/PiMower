#include "Button.h"

#if defined(useButton) || defined(useActiveButton)

Rectangle Button::Draw(DriverBase &tft, bool sunken, uint16_t x, uint16_t y, uint16_t width,
	uint16_t height, int32_t textColor, uint32_t buttonColor, eUITextFont font, std::string text,
	bool is3D, uint8_t cornerRadius, uint8_t alpha, eVertAlign vertAlign)
{
	Rectangle r;
	if (is3D)
	{
		if (sunken)
		{
			r = UIPrimitives::SunkenPanel(tft, x, y, width, height, cornerRadius, buttonColor, alpha);
		}
		else
		{
			r = UIPrimitives::RaisedPanel(tft, x, y, width, height, cornerRadius, buttonColor, alpha);
		}
	}
	else
	{
		r=UIPrimitives::FlatPanel(tft, x, y, width, height, cornerRadius, buttonColor, alpha);
	}

	r.update();
	// Now we need to center the text
	Logger::Trace("Button (%d,%d,%d,%d) text(%d,%d)", r.x1, r.y1, r.x2, r.y2, x+width/2, y+height/2);
	uint8_t tHeight = FontHelper::GetTextRect(tft, text, font, Point(0, 0)).height;
	uint16_t yText = y + height / 2 - tHeight / 2;
	if (vertAlign == eVertAlign::Top)
		yText = y + 3;
	if (vertAlign == eVertAlign::Bottom)
	{
		yText = y + height - 3 - tHeight;
	}	
#ifdef RA8875
	UIPrimitives::Text(tft, textColor, alpha, x+width/4, yText, font, 
		is3D, text, UIPrimitives::Center);	
#endif
#ifdef FT8XX	
	UIPrimitives::Text(tft, textColor, alpha, x + width / 2, yText, font,
		is3D, text, UIPrimitives::Center);
#endif
	return r;
}

#endif