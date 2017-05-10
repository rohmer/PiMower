#include "Slider.h"

Rectangle Slider::Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
	uint32_t textColor, uint32_t sliderBarColor, uint32_t sliderControlColor, eUITextFont font,
	int16_t value, int16_t minValue, int16_t maxValue, bool is3D, uint8_t cornerRadius,
	uint8_t alpha)
{
	bool horiz = (width >= height);
	Rectangle barRect;
	if (is3D)
	{
		if (horiz)
		{
			barRect = UIPrimitives::RaisedPanel(tft, x, (height / 5) + y, width, height*0.4, cornerRadius, sliderBarColor, alpha);
		}
		else
		{
			barRect = UIPrimitives::RaisedPanel(tft, (width / 5) + 5, y, width*0.4, height, cornerRadius, sliderBarColor, alpha);
		}
	}
	else
	{
		if (horiz)
		{
			barRect = UIPrimitives::FlatPanel(tft, x, (height / 5) + y, width, height*0.4, cornerRadius, sliderBarColor, alpha);
		}
		else
		{
			barRect = UIPrimitives::FlatPanel(tft, (width / 5) + 5, y, width*0.4, height, cornerRadius, sliderBarColor, alpha);
		}
	}

	// Next draw the slider control

	// Find out where we are
	float pct = (value + abs(minValue)) / abs(minValue) + abs(maxValue);
	uint16_t centerX, centerY;
	if (horiz)
	{
		centerX = barRect.x1 + (barRect.width*pct);
		centerY = barRect.center().y;
	}
	else
	{
		centerX = barRect.center().x;
		centerY = barRect.y1 + (barRect.height*pct);
	}

	// Now draw the actual slider control
	if (horiz)
	{
		if (is3D)
		{
			UIPrimitives::RaisedPanel(tft, centerX - 5, centerY - (barRect.height), 10, barRect.height * 2, 
				cornerRadius, sliderControlColor, alpha);
		}
		else
		{
			UIPrimitives::FlatPanel(tft, centerX - 5, centerY - (barRect.height), 10, barRect.height * 2,
				cornerRadius, sliderControlColor, alpha);
		}
	}
	else
	{
		if (is3D)
		{
			UIPrimitives::RaisedPanel(tft, centerY - (barRect.width), centerY - 5, barRect.width*2, 10,
				cornerRadius, sliderControlColor, alpha);
		}
		else
		{
			UIPrimitives::FlatPanel(tft, centerY - (barRect.width), centerY - 5, barRect.width * 2, 10,
				cornerRadius, sliderControlColor, alpha);
		}
	}
	std::ostringstream s;
	s << value;
	// Now draw the value below or to the right of it
	if (horiz)
	{
		UIPrimitives::Text(tft, textColor, alpha, barRect.center().x, barRect.center().y + barRect.height * 3, font, is3D, s.str());
	}
	else
	{
		UIPrimitives::Text(tft, textColor, alpha, barRect.center().x + barRect.width * 3, barRect.center().y, font, is3D, s.str());
	}

	// Return the total size
	if (horiz)
	{
		return Rectangle(barRect.x1, 
			centerY - (barRect.width), 
			barRect.x2, 
			barRect.center().y + barRect.height * 3 + FontHelper::GetTextRect(tft, "1234567890", font, Point(0, 0)).height*0.5);
	}
	return Rectangle(centerX-(barRect.height),
		barRect.y1,
		barRect.center().x+barRect.width*3+ FontHelper::GetTextRect(tft, "1234567890", font, Point(0, 0)).width*0.5,
		barRect.y1);
}

// Figures out what the value should be based on a touchpoint
uint16_t Slider::GetValue(Rectangle controlLocation, int16_t minValue, int16_t maxValue, Point pt)
{
	bool horiz = (controlLocation.width >= controlLocation.height);
	if (horiz)
	{
		if (pt.x < controlLocation.x1)
		{
			return minValue;
		}
		if (pt.x > controlLocation.x2)
		{
			return maxValue;
		}

		// Ok now we need to figure out the percetage
		float pct = (abs(pt.x - controlLocation.x1)) / (abs(controlLocation.x2 - controlLocation.x1));
		return (pct*(abs(minValue) + abs(maxValue)) + minValue);
	}

	if (pt.y < controlLocation.y1)
	{
		return minValue;
	}
	if (pt.y > controlLocation.y2)
	{
		return maxValue;
	}

	// Ok now we need to figure out the percetage
	float pct = (abs(pt.y - controlLocation.y1)) / (abs(controlLocation.y2 - controlLocation.y1));
	return (pct*(abs(minValue) + abs(maxValue)) + minValue);
}