#pragma once
#include "UIElement.h"
#include <string>
#include <vector>
#include "UIFont.h"
#include "ScreenManager.h"

class UIRadioGroup : public UIElement
{
public:
	enum GroupAlignment
	{
		Vertical,
		Horizontal
	};

	UIRadioGroup(Point position);
	UIRadioGroup(Point position,
		uint8_t radioColor,
		uint8_t textColor,
		UIFont::eFontName  font,
		GroupAlignment alignment,
		eTextAlignment textAlignment);
	void update(DigoleLCD *lcd, RobotLib *robotLib) override;
	bool addRadioItem(std::string label, int value, bool isSelected);

private:
	struct sRadioValue
	{
		std::string label;
		int value;
		Point checkPoint;
		Point textStart;
		Rectangle touchPoint;
		bool isSelected;
	};

	void setArea();
	uint8_t radioColor = DigoleLCD::LIGHT_RED;
	uint8_t textColor = DigoleLCD::WHITE;
	UIFont::eFontName font = UIFont::defaultFont;
	GroupAlignment alignment=GroupAlignment::Horizontal;
	eTextAlignment textAlignment=eTextAlignment::textRight;
	std::vector<sRadioValue> values;
};
