#include "Slider.h"

Rectangle Slider::Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
	uint32_t textColor, uint32_t sliderBarColor, uint32_t sliderControlColor, eUITextFont font,
	int16_t value, int16_t minValue, int16_t maxValue, bool is3D,
	uint8_t alpha)
{
	bool horiz = (width >= height);
	
	uint16_t fifth;
	if (horiz)
		fifth = height / 5;
	else
		fifth = width / 5;

	if (fifth < 1)
		fifth = 1;

	Logger::Trace("0");
	// Draw the main bar
	if (horiz)
	{
		if (is3D)
			UIPrimitives::RaisedPanel(tft, x, y + fifth, width, fifth, 0, sliderBarColor, alpha);
		else
			UIPrimitives::FlatPanel(tft, x, y + fifth, width, fifth, sliderBarColor, alpha);
	}
	else
	{
		if (is3D)
			UIPrimitives::RaisedPanel(tft, x + fifth, y, fifth, height, 0, sliderBarColor, alpha);
		else
			UIPrimitives::FlatPanel(tft, x + fifth, y, fifth, height, 0, sliderBarColor, alpha);
	}
	// Get the percentage	
	double pct;	
	
	int denom = minValue + maxValue;
	int num = minValue + value;
	if (denom > 0)
		pct = ((double)num / (double)denom);
	else
		pct = 0.0;
	
	// Draw the slider control
	uint16_t startX = x + (width*pct);
	uint16_t startY = y + (width*pct);
	if (horiz)
	{
		if (is3D)
			UIPrimitives::RaisedPanel(tft, startX, y, 10, fifth * 3, 0, sliderControlColor, alpha);
		else
			UIPrimitives::FlatPanel(tft, startX, y, 10, fifth * 3, 0, sliderControlColor, alpha);		
	}
	else
	{
		if (is3D)
			UIPrimitives::RaisedPanel(tft, x, startY, fifth * 3, 10, 0, sliderControlColor, alpha);
		else
			UIPrimitives::FlatPanel(tft, x, startY, fifth * 3, 10, 0, sliderControlColor, alpha);
	}

	// Now draw the value
	std::stringstream ss;
	ss << (pct * 100);
	int halfWidth = FontHelper::GetTextRect(tft, ss.str(), font, Point(0, 0)).width / 2;
	UIPrimitives::Text(tft, textColor, alpha, x + (width*0.5)-halfWidth, y+fifth * 4, font, is3D, ss.str());
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