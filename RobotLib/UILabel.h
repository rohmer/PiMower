#pragma once
#include "UIElement.h"
#include <string>
#include "UIFont.h"

class UILabel : public UIElement
{
public:
	UILabel(Point position, std::string text);
	UILabel(Point position, std::string text, UIFont::eFontName  font, uint8_t textColor, uint8_t textBackgroundColor);
	void update(DigoleLCD *lcd, RobotLib *robotLib) override;
	int processTouch(Point pt) override
	{
		return -1;
	}

protected:
	void setArea() override;

private:
	std::string labelText;
	UIFont::eFontName labelFont;
	uint8_t textColor, textBGColor;
};
