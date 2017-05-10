#include "ProgressBar.h"

Rectangle ProgressBar::Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width,
	uint16_t height, uint8_t progress, int32_t textColor, uint32_t barBGColor, uint32_t barProgressColor, 
	eUITextFont font, bool is3D = true, uint8_t cornerRadius = 4, uint8_t alpha = 255)
{
	bool horiz = (width >= height);
	if (horiz)
	{
		if (is3D)
		{
			// First background
			UIPrimitives::SunkenPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
			// Then used part
			float pct = progress / 100;
			UIPrimitives::RaisedPanel(tft, x, y, width*pct, height, cornerRadius, barProgressColor, alpha);
			// Now the text
			std::ostringstream s;
			s << progress;
			UIPrimitives::Text(tft, textColor, alpha, x + ((width*pct) / 2), y + (height / 2), font, true, s.str());
		}
		else
		{
			// First background
			UIPrimitives::FlatPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
			// Then used part
			float pct = progress / 100;
			UIPrimitives::FlatPanel(tft, x, y, width*pct, height, cornerRadius, barProgressColor, alpha);
			// Now the text
			std::ostringstream s;
			s << progress;
			UIPrimitives::Text(tft, textColor, alpha, x + ((width*pct) / 2), y + (height / 2), font,false, s.str());
		}
	}

	if (is3D)
	{
		// First background
		UIPrimitives::SunkenPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
		// Then used part
		float pct = progress / 100;
		UIPrimitives::RaisedPanel(tft, x, y, width, height*pct, cornerRadius, barProgressColor, alpha);
		// Now the text
		std::ostringstream s;
		s << progress;
		UIPrimitives::Text(tft, textColor, alpha, x + (width / 2), y + ((height*pct) / 2), font, true, s.str());
	}
	else
	{
		// First background
		UIPrimitives::FlatPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
		// Then used part
		float pct = progress / 100;
		UIPrimitives::FlatPanel(tft, x, y, width, height*pct, cornerRadius, barProgressColor, alpha);
		// Now the text
		std::ostringstream s;
		s << progress;
		UIPrimitives::Text(tft, textColor, alpha, x + (width / 2), y + ((height*pct) / 2), font, false, s.str());
	}
	return (Rectangle(x, y, x + width, y + height));
}

Rectangle ProgressBar::Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width,
	uint16_t height, uint8_t progress, uint32_t barBGColor, uint32_t barProgressColor,
	bool is3D = true, uint8_t cornerRadius = 4, uint8_t alpha = 255)
{
	bool horiz = (width >= height);
	if (horiz)
	{
		if (is3D)
		{
			// First background
			UIPrimitives::SunkenPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
			// Then used part
			float pct = progress / 100;
			UIPrimitives::RaisedPanel(tft, x, y, width*pct, height, cornerRadius, barProgressColor, alpha);			
		}
		else
		{
			// First background
			UIPrimitives::FlatPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
			// Then used part
			float pct = progress / 100;
			UIPrimitives::FlatPanel(tft, x, y, width*pct, height, cornerRadius, barProgressColor, alpha);			
		}
	}

	if (is3D)
	{
		// First background
		UIPrimitives::SunkenPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
		// Then used part
		float pct = progress / 100;
		UIPrimitives::RaisedPanel(tft, x, y, width, height*pct, cornerRadius, barProgressColor, alpha);		
	}
	else
	{
		// First background
		UIPrimitives::FlatPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
		// Then used part
		float pct = progress / 100;
		UIPrimitives::FlatPanel(tft, x, y, width, height*pct, cornerRadius, barProgressColor, alpha);		
	}
	return (Rectangle(x, y, x + width, y + height));
}
