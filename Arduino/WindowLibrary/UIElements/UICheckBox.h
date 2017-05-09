#pragma once
#include "../Options.h"
#include <string>
#include <map>
#include <vector>
#include "../Utility/Color.h"
#include "UIElement.h"
#include <SPI.h>
#include "ControlDisplay/CheckBox.h"

class UICheckBox : public UIElement
{
public:
	UICheckBox(DriverBase &tft, Rectangle location, std::string boxText, bool checked,
		eUITextFont textFont, uint16_t textColor, uint8_t textScale, uint16_t boxColor, 
		uint16_t boxShadowColor, uint8_t boxShadowSize,	uint8_t boxBorderSize, 
		uint16_t boxCheckColor, bool hasRoundCorners, uint8_t cornerRadius);
	~UICheckBox();

	sTouchResponse ProcessTouch(Point touchPoint) override;

	void Update() override;

private:
	std::string buttonText;
	eUITextFont textFont;
	uint16_t textColor, boxColor, boxShadowColor, boxCheckColor;
	uint8_t textScale, shadowSize, boxBorderSize, cornerRadius;
	bool hasRoundCorners;
	bool isChecked;
};
