#pragma once
#include "UIElement.h"
#include "UIFont.h"
#include <vector>
#include <string>

class UIButton : UIElement
{
	public:
		UIButton(Rectangle location, std::string buttonText);
		UIButton(Rectangle location, std::string buttonText, UIFont::eFontName  font, 
			uint8_t buttonColor, uint8_t textColor, bool useButtonFrame, uint8_t buttonFrameColor);
		Rectangle calcSize();
		void update(DigoleLCD *lcdDriver);
		bool pointTouches(Point pt) override;
	
	private:
		uint8_t buttonColor, textColor, buttonFrameColor;
		std::string buttonText;
		UIFont::eFontName font;
		bool useButtonFrame;
		bool triggered = false;
};