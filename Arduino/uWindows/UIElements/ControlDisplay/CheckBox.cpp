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
	boxR.update();
	if (isChecked)
	{		
		uint16_t boxDelta = boxR.width / 5;
		if (boxDelta < 1)
			boxDelta = 1;

		UIPrimitives::FlatPanel(tft, boxR.x1+boxDelta, boxR.y1+boxDelta, boxR.width-boxDelta*2, boxR.height-boxDelta*2,
			cornerRadius, checkColor, 255);
	}

	int16_t textX;
	if (textRight)
	{
		textX = boxR.x2 + (radius)+FontHelper::GetTextRect(tft,text,font,Point(0,0)).center().x/2;
	}
	else
	{
		uint16_t textWidth = FontHelper::GetTextRect(tft, text, font, Point(0, 0)).width;
		textX = boxR.x1 - textWidth / 2;
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