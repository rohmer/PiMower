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
		}
		else
		{
			// First background
			UIPrimitives::FlatPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
		}
	}
	else
	{
		if (is3D)
		{
			// First background
			UIPrimitives::SunkenPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
		}
		else
		{
			// First background
			UIPrimitives::FlatPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
		}
	}
	float pct = 0;
	if (progress>0)
		pct = static_cast<float>((static_cast<float>(progress * 100) / 10000.0));
	Logger::Trace("Progress Bar: pct: %d,  %d,%d,%d,%d", pct, x, y, width*pct, height);
	Rectangle progressRect = UIPrimitives::FlatPanel(tft, x + 5, y + 5, width*pct - 10, height - 10,
		cornerRadius, barProgressColor, alpha);	
	std::stringstream ss;
	ss << (pct*100) << " %";
	UIPrimitives::Text(tft, textColor, alpha, x+5+(width*pct)/2-10, y+height/2,
		font, is3D, ss.str());
	return (Rectangle(x, y, x + width, y + height));
}

Rectangle ProgressBar::Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width,
	uint16_t height, uint8_t progress, uint32_t barBGColor, uint32_t barProgressColor,
	bool is3D = true, uint8_t cornerRadius = 4, uint8_t alpha = 255)
{
#ifdef DEBUG
	Logger::Trace("ProgressBar::Dar(TFT,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d)",
		x, y, width, height, progress, barBGColor, barProgressColor, Logger::BoolToStr(is3D).c_str(),
		cornerRadius, alpha);
#endif
	bool horiz = (width >= height);
	if (horiz)
	{
		if (is3D)
		{
			// First background
			UIPrimitives::SunkenPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
			// Then used part			
		}
		else
		{
			// First background
			UIPrimitives::FlatPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
			// Then used part
		}
	}
	else
	{

		if (is3D)
		{
			// First background
			UIPrimitives::SunkenPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
			// Then used part
		}
		else
		{
			// First background
			UIPrimitives::FlatPanel(tft, x, y, width, height, cornerRadius, barBGColor, alpha);
			// Then used part
		}
	}
	float pct = 0;
	if (progress>0)
		pct = static_cast<float>((static_cast<float>(progress * 100) / 10000.0));
	Logger::Trace("Progress Bar: pct: %d,  %d,%d,%d,%d", pct, x, y, width*pct, height);
	Rectangle progressRect= UIPrimitives::FlatPanel(tft, x + 5, y + 5, width*pct - 10, height - 10, 
		cornerRadius, barProgressColor, alpha);

	return (Rectangle(x, y, x + width, y + height));
}
