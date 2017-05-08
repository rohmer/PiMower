#pragma once
#include <string>
#include "../Color.h"
#include "../BaseItems/UIElement.h"
#include "../BaseItems/Theme.h"
#include "../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "../UIElements/UIText.h"

class UIButton : public UIElement
{
public:
	enum eButtonCornerType
	{
		Square,
		Rounded
	};

	UIButton(Rectangle location, Theme *theme);
	UIButton(Rectangle location, std::string buttonText, Theme *theme);
	UIButton(Rectangle location, std::string buttonText, eTextAlignment buttonTextAlign, Theme *theme);
	UIButton(Rectangle location, std::string buttonText, eTextAlignment buttonTextAlign,
		uint16_t clickableBGColor, uint16_t clickableBorderColor, uint16_t clickableTextColor,
		uint16_t clickableIconColor, Theme *theme);

	void setTouchArea() override;
	void update(Adafruit_RA8875 *lcd) override;
	void setButtonText(std::string buttonText, sThemeSettings currentSettings);

private:
	bool isClicked;

	bool shadowInterpolated;
	bool touched = false;
	sThemeSettings active, clickable;

	void drawBorder(Adafruit_RA8875 *lcd, sThemeSettings themeSettings);
	void drawShadow(Adafruit_RA8875 *lcd, sThemeSettings themeSettings);
	void fillButton(Adafruit_RA8875 *lcd, sThemeSettings themeSettings);

	UIText *buttonTextObj;
	Theme *theme;
};
