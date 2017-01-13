#pragma once
#include "UIElement.h"
#include "../RobotController/SensorLib/DigoleLCD.h"
#include "UIFont.h"

class UILabel : UIElement
{
	public:
		UILabel(std::string text, Point location);
		UILabel(std::string text, Point location, UIFont::eFontName font, bool clickable);
		UILabel(std::string text, Point location, UIFont::eFontName font, bool clickable, uint8_t textColor);
		void update(DigoleLCD *lcdDriver) override;
		Rectangle calcSize() override;
		bool pointTouches(Point pt) override;
		
	private:
		UIFont::eFontName font = UIFont::u8g_font_unifont;
		std::string text;
		uint8_t textColor;		
};
