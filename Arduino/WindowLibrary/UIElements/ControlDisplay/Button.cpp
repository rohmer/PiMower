#include "Button.h"

#if defined(useButton) || defined(useActiveButton)

Rectangle Button::Draw(DriverBase &tft, bool sunken, uint16_t x, uint16_t y, uint16_t width,
	uint16_t height, int32_t textColor, uint32_t buttonColor, eUITextFont font, std::string text,
	bool is3D, uint8_t cornerRadius, uint8_t alpha)
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
	UIPrimitives::Text(tft, textColor, alpha, x+width/4, y+height/2, font, 
		is3D, text, UIPrimitives::Center);	
}

#endif