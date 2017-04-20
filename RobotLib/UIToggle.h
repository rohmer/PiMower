#pragma once
#include "UIElement.h"
#include <string>
#include "UIFont.h"
#include "ScreenManager.h"

class UIToggle : public UIElement
{
public:
	UIToggle(Point position,
		std::string text);
	UIToggle(Point position,
		std::string text,
		uint8_t checkColor,
		uint8_t textColor,
		UIFont::eFontName font,
		bool state,
		eTextAlignment textAlign);

	bool getState();
	void setState(bool state, ScreenManager *screenManager);
	void update(DigoleLCD *lcd, RobotLib *robotLib) override;

protected:
	void setArea();

private:
	bool toggleState;
	std::string text;
	uint8_t checkColor = DigoleLCD::LIGHT_RED;
	uint8_t textColor = DigoleLCD::WHITE;
	UIFont::eFontName font = UIFont::defaultFont;
	eTextAlignment textAlign = eTextAlignment::textRight;
	Rectangle touchTarget;
	Rectangle checkArea;
	Point textArea;
};
