#include "Button.h"

Rectangle Button::Draw(DriverBase &tft, bool sunken, uint16_t x, uint16_t y, uint16_t width,
	uint16_t height, int32_t textColor, uint32_t buttonColor, eUITextFont font, std::string text,
	bool is3D, uint8_t cornerRadius, uint8_t alpha)
{
	if (is3D)
	{
		UIPrimitives::RaisedPanel(tft, x, y, width, height, cornerRadius, buttonColor, alpha);
	}
	else
	{
		UIPrimitives::FlatPanel(tft, x, y, width, height, cornerRadius, buttonColor, alpha);
	}

	// Now we need to center the text
	UIPrimitives::Text(tft, textColor, alpha, x+width/2, y+height/2, font, is3D, text);	
}