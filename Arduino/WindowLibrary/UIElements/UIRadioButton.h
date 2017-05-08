#pragma once
#include "../Options.h"
#include <string>
#include <map>
#include <vector>
#include "../Utility/Color.h"
#include "UIElement.h"
#include "../WindowManager/Theme.h"
#include <SPI.h>
#ifdef RA8875 
#include "../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "RA8875/Fonts.h"
#endif
#ifdef FT8XX
#include "../External/GD3/GD3.h"
#include "FT8XX/Fonts.h"
#endif
#include "../Utility/FontHelper.h"
#include "../Utility/Rectangle.h"


class UIRadioButton : public UIElement
{
public:
	UIRadioButton(DriverBase &tft, Rectangle location, std::string text, bool checked, Theme &elementTheme, eThemeObjState state);
	UIRadioButton(DriverBase &tft, Rectangle location, std::string text, bool checked, eUITextFont textFont, 
		uint16_t textColor, uint8_t textScale, uint16_t controlColor, uint16_t checkColor);

	void Update() override;
	void SetText(std::string text);
	void SetChecked(bool checked);
	bool IsChecked()
	{
		return isChecked;
	}
	sTouchResponse ProcessTouch(Point touchPoint) override;
	~UIRadioButton();

private:
	std::string buttonText;
	bool isChecked;
	eUITextFont textFont;
	uint16_t textColor, controlColor, checkColor;
	uint8_t textScale;	

	Rectangle *checkRect = NULL;
};
