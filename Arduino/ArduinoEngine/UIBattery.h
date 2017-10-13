#pragma once
#include <map>
#include <vector>
#include "Utility/Color.h"
#include "UIElements/UIElement.h"
#include <SPI.h>
#include "UIElements/ControlDisplay/BatteryIcon.h"


class UIBattery : public UIElement
{
public:
	UIBattery(DriverBase &tft, Rectangle location, uint8_t pctCharged,
		std::vector<tColor> barColors, bool showPct = true, tColor borderColor = Color::White, tColor bgColor = Color::Black,
		eUITextFont pctFont = eUITextFont::AntiAliasFont27, tColor pctTextColor = Color::White,
		bool rightAlignment = true);

	sTouchResponse ProcessTouch(Point touchPoint)
	{
		return sTouchResponse(this->elementID, eTouchResponse::NoOp);
	};
	void Update() override;
	void SetPctCharged(uint8_t)
	{
		this->pctCharged = pctCharged;
	}

private:
	uint8_t pctCharged;
	tColor borderColor, pctTextColor, bgColor;
	std::vector<tColor> barColors;
	eUITextFont pctFont;
	bool rightAlignment, showPct;
};
