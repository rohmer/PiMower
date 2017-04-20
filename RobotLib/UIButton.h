#pragma once
#include "UIElement.h"
#include <string>
#include "UIFont.h"

class UIButton : public UIElement
{
public:
	UIButton(Point position, std::string text);
	UIButton(Point position, std::string text, UIFont::eFontName  font, uint8_t textColor, uint8_t buttonColor, uint8_t buttonFrameColor,
		Rectangle buttonSize);
	void update(DigoleLCD *lcd, RobotLib *robotLib) override;
	int processTouch(Point pt) override;

protected:
	void setArea() override;

private:
	bool areaSet = false;
	std::string labelText;
	UIFont::eFontName labelFont;
	uint8_t textColor, buttonColor, buttonFrameColor;
};
