#pragma once
#include "../../Options.h"
#ifdef RA8875

#include <string>
#include <map>
#include <vector>
#include "../../Utility/Color.h"
#include "../UIElement.h"
#include "../../WindowManager/Theme.h"
#include <SPI.h>
#include "../../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "Fonts.h"
#include "../../Utility/FontHelper.h"
#include "../../Utility/Rectangle.h"

class UICheckBox : public UIElement
{
public:
	UICheckBox(Adafruit_RA8875 &tft, Rectangle location, std::string boxText, bool checked,
		Theme &elementTheme, eThemeObjState state);
	UICheckBox(Adafruit_RA8875 &tft, Rectangle location, std::string boxText, bool checked,
		eUITextFont textFont, uint16_t textColor, uint8_t textScale, uint16_t boxColor, 
		uint16_t boxShadowColor, uint8_t boxShadowSize,	uint8_t boxBorderSize, 
		uint16_t boxCheckColor, bool hasRoundCorners, uint8_t cornerRadius);
	~UICheckBox();

	sTouchResponse ProcessTouch(Point touchPoint) override;

	void Update() override;

private:
	sThemeSettings theme;
	std::string buttonText;
	eUITextFont textFont;
	uint16_t textColor, boxColor, boxShadowColor, boxCheckColor;
	uint8_t textScale, shadowSize, boxBorderSize, cornerRadius;
	bool hasRoundCorners;
	Rectangle *checkRect = NULL;
	bool isChecked;
};
#endif