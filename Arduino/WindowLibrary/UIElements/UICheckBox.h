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
		eUITextFont textFont, tColor  textColor, uint8_t textScale, tColor  boxColor,
		tColor  boxShadowColor, uint8_t boxShadowSize,	uint8_t boxBorderSize,
		tColor  boxCheckColor, bool hasRoundCorners, uint8_t cornerRadius, std::string elementName = "");
	~UICheckBox();

	sTouchResponse ProcessTouch(Point touchPoint) override;

	void Update() override;

private:
	std::string buttonText;
	eUITextFont textFont;
#ifdef RA8875
	uint16_t textColor, boxColor, boxShadowColor, boxCheckColor;
#endif
#ifdef FT8XX
	uint32_t textColor, boxColor, boxShadowColor, boxCheckColor;
#endif

	uint8_t textScale, shadowSize, boxBorderSize, cornerRadius;
	bool hasRoundCorners;
	bool isChecked;
};
