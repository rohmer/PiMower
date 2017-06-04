#include "RadioButton.h"

Rectangle RadioButton::Draw(DriverBase &tft, bool sunken, bool isChecked, uint16_t x, uint16_t y,
	uint32_t textColor, uint32_t uncheckedColor, uint32_t checkColor, eUITextFont font,
	std::string text, bool textRight = true, bool is3D = true)
{
	// We need the size of the text, to get the size of the radio button
	Rectangle r=FontHelper::GetTextRect(tft, text, font, Point(x, y));
	uint16_t radius = r.height/2;
	x = x + radius;
	y = y + radius;
	Rectangle circleR;
	if (is3D)
	{
		if (sunken)
		{
			circleR = UIPrimitives::CircleSunken(tft, uncheckedColor, 255, x, y, radius);
		}
		else
		{
			circleR = UIPrimitives::CircleRaised(tft, uncheckedColor, 255, x, y, radius);
		}
	}
	else
	{
		circleR=UIPrimitives::CircleFlat(tft, uncheckedColor, 255, x, y, radius);
	}

	if (isChecked)
	{
		UIPrimitives::CircleFlat(tft, checkColor, 255, x, y, radius / 2);
	}
	
	int16_t textX;
	Rectangle fontRect = FontHelper::GetTextRect(tft, text, font, Point(0, 0));

	if (textRight)
	{
		textX = circleR.x2 + (radius)+fontRect.center().x / 2;
	}
	else
	{
		uint16_t textWidth = fontRect.width;
		textX = circleR.x2 - textWidth / 2;
	}
		
	Rectangle retVal = UIPrimitives::Text(tft, textColor, 255, textX, y-fontRect.height/2, font, is3D, text);
	return;
	if (textRight)
	{
		retVal.x1 = circleR.x1;
	}
	else
	{
		retVal.x2 = circleR.x2;
	}
	return retVal;
}
