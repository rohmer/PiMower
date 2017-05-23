#include "Window.h"

#ifdef RA8875
Rectangle Window::Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
	uint16_t titleBarBGColor, uint16_t titleBarTextColor, uint16_t controlColor, uint16_t borderColor,
	uint16_t windowBGColor,
	std::string titleText, eUITextFont font, bool hasChrome, bool hasTitleBar, bool hasCloseIcon,
	bool is3D = true, uint8_t cornerRadius = 4, uint8_t alpha = 255)
#endif
#ifdef FT8XX
	static Rectangle Window::Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
		uint32_t titleBarBGColor, uint16_t titleBarTextColor, uint32_t controlColor, uint32_t borderColor,
		uint32_t windowBGColor,
		std::string titleText, eUITextFont font, bool hasChrome, bool hasTitleBar, bool hasCloseIcon,
		bool is3D = true, uint8_t cornerRadius = 4, uint8_t alpha = 255)
#endif
{
	Rectangle r;
	if (is3D)
		r = UIPrimitives::RaisedPanel(tft, x, y, width, height, cornerRadius, windowBGColor, alpha);
	else
		r = UIPrimitives::FlatPanel(tft, x, y, width, height, cornerRadius, windowBGColor, alpha);

	if (hasChrome)
	{
		if (hasTitleBar)
		{
			Rectangle txtRect = FontHelper::GetTextRect(tft, titleText, font, Point(0, 0));
			uint8_t fontHeight = txtRect.height;
			uint8_t fontWidth = txtRect.width;
			Rectangle titleBarRect = UIPrimitives::FlatPanel(tft, x + 1, y + 1, width - 2, fontHeight*3, cornerRadius,
				titleBarBGColor, alpha);
			// Now center the text in that
			UIPrimitives::Text(tft, titleBarTextColor, alpha, titleBarRect.center().x-fontWidth, 
				titleBarRect.center().y, font,is3D, titleText);
			if (hasCloseIcon)
			{
				// Draw an X in a box in the upper right hand corner
				uint16_t x0 = titleBarRect.x2 - 2 - cornerRadius - fontHeight*2;
				uint16_t y0 = titleBarRect.y1 + cornerRadius;
				uint16_t x1 = x0 + fontHeight*2;
				uint16_t y1 = y0 + fontHeight*2;
				tft.drawRect(x0, y0,fontHeight*2, fontHeight*2, controlColor);
				tft.drawRect(x0+1,y0+1, fontHeight * 2 - 2, fontHeight * 2 - 2, controlColor);
				
				// Draw X
				tft.drawLine(x0, y0, x1, y1, controlColor);
				tft.drawLine(x0 + 1, y0, x1, y1 - 1, controlColor);
				tft.drawLine(x0, y0 + 1, x1 - 1, y1, controlColor);
				tft.drawLine(x0, y1, x1, y0, controlColor);
				tft.drawLine(x0 + 1, y1, x1, y0 + 1, controlColor);
				tft.drawLine(x0, y1 - 1, x1 - 1, y0, controlColor);
			}
		}

		// Draw Border
		tft.drawRect(x, y, width, height, borderColor);
		tft.drawRect(x + 1, y + 1, width - 2, height - 2, borderColor);
	}
	return r;
}