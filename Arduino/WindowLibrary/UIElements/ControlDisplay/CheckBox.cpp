#include "CheckBox.h"

Rectangle CheckBox::Draw(DriverBase &tft, bool sunken, bool isChecked, uint16_t x, uint16_t y,
	uint32_t textColor, uint32_t uncheckedColor, uint32_t checkColor, eUITextFont font,
	std::string text, bool textRight = true, bool is3D = true, uint8_t cornerRadius)
{
	// We need the size of the text, to get the size of the radio button
	Rectangle r = FontHelper::GetTextRect(tft, text, font, Point(x, y));
	uint16_t radius = r.height;

	Rectangle boxR;
	if (is3D)
	{
		if(sunken)
			boxR = UIPrimitives::SunkenPanel(tft, x, y, radius, radius, cornerRadius, uncheckedColor, 255);
		else
			boxR = UIPrimitives::RaisedPanel(tft, x, y, radius, radius, cornerRadius, uncheckedColor, 255);
	}
	else
	{		
		boxR = UIPrimitives::FlatPanel(tft, x, y, radius, radius, cornerRadius, uncheckedColor, 255);
	}

	if (isChecked)
	{
		UIPrimitives::FlatPanel(tft, x, y, radius / 2, radius / 2, 0, checkColor, 255);
	}

	int16_t textX;
	if (textRight)
	{
		textX = boxR.x2 + (radius / 2);
	}
	else
	{
		textX = boxR.x1 - (radius / 2) - r.width;
	}

	Rectangle retVal = UIPrimitives::Text(tft, textColor, 255, textX, y, font, is3D, text);
	if (textRight)
	{
		retVal.x1 = boxR.x1;
	}
	else
	{
		retVal.x2 = boxR.x2;
	}

	return retVal;
}