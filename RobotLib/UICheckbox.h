#pragma once
#include "UIElement.h"
#include "UIFont.h"

class UICheckbox : UIElement
{
	public:
		UICheckbox(std::string text, Point location);
		UICheckbox(std::string text, Point location, UIFont::eFontName font);
		UICheckbox(std::string text, Point location, UIFont::eFontName font, bool textRightAlign);
		UICheckbox(std::string text, Point location, UIFont::eFontName font, bool textRightAlign, bool isChecked);
		void update(DigoleLCD *lcdDriver) override;
		Rectangle calcSize() override;
		bool isChecked();
		void setValue(bool checked);
		void setTextColor(uint8_t textColor);
		void setCheckColor(uint8_t checkColor);
	
	private:
		bool textRightAlign = true;
		UIFont::eFontName font = UIFont::u8g_font_unifont;
		std::string text;
		bool value;
		uint8_t textColor;
		uint8_t checkColor;
};