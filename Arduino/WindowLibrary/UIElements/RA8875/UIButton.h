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

class UIButton : public UIElement
{
public:	
	UIButton(Adafruit_RA8875 &tft, Rectangle location, std::string buttonText, 
		Theme &elementTheme, eThemeObjState state);
	UIButton(Adafruit_RA8875 &tft, Rectangle location, std::string buttonText,
		eUITextFont textFont, uint16_t textColor, uint8_t textScale, uint16_t buttonColor, 
		int16_t buttonBorderColor, uint8_t buttonBorderSize, uint16_t buttonActiveColor, 
		uint16_t buttonActiveTextColor, uint16_t buttonShadowColor, uint8_t buttonShadowSize, 
		uint16_t buttonActiveShadowColor, uint8_t buttonactiveShadowSize, bool buttonPressedOnRelease, 
		bool hasRoundCorners, uint8_t cornerRadius);

	void Update() override;
	void SetButtonText(std::string buttonText);
	sTouchResponse ProcessTouch(Point touchPoint) override;

	~UIButton();

private:
	void loadThemeSettings();

	sThemeSettings defaultTheme, activeTheme;
	std::string buttonText;
	eUITextFont textFont;
	uint16_t textColor, buttonColor, buttonActiveColor, buttonActiveTextColor, buttonBorderColor,
		buttonShadowColor, buttonShadowSize, buttonActiveShadowColor, buttonActiveShadowSize;
	bool buttonPressedOnRelease, hasRoundCorners;
	uint8_t buttonBorderSize, cornerRadius, textScale;
	Point *textLocation = NULL;
};
#endif