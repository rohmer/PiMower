#pragma once
#pragma once
#include "UIElement.h"
#include "UIFont.h"
#include <vector>

class UIRadioGroup : UIElement
{
	public:
		UIRadioGroup(Point location);
		UIRadioGroup(Point location, bool rightTextAlign);
		
		bool pointTouches(Point pt) override;
		void update(DigoleLCD *lcdDriver) override;
		Rectangle calcSize() override;
		void addButton(std::string text, int value, bool isChecked);
		int getValue();
	
	private:
		struct radioButton
		{
			radioButton(int value, bool isChecked, std::string text)
				: value(value)
				, isChecked(isChecked)
				, text(text)
			{
			}
			int value;
			bool isChecked;
			std::string text;
			Rectangle boundingBox;
		};
		
		bool textRightAlign = true;
		UIFont::eFontName font = UIFont::u8g_font_unifont;
		int value;
		uint8_t textColor;
		uint8_t checkColor;
		std::vector<radioButton> buttons;		
		uint8_t maxTextWidth = 0;
};