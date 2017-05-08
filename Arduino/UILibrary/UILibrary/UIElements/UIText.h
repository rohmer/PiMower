#pragma once
#include <string>
#include <map>
#include <vector>
#include "../Color.h"
#include "../BaseItems/UIElement.h"
#include "../BaseItems/Theme.h"
#include <SPI.h>
#include "../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "Fonts.h"
#include "FontHelper.h"

class UIText : public UIElement
{
public:
	UIText(Rectangle location, std::string text, Theme *theme, eThemeObjState state);
	UIText(Rectangle location, std::string text, eUITextFont font);

	static Rectangle GetFontRect(std::string text, eUITextFont font);
	static Rectangle GetFontRect(std::string text, eUITextFont font, uint8_t interlineSpacing, uint8_t textSpacing);

	void setTouchArea() override;
	void update(Adafruit_RA8875 *lcd) override;

	void setText(std::string text);
	void setObjectState(eThemeObjState state);

private:
	std::vector<std::string> buttonTextLines;

	std::string buttonText;
	sThemeSettings themeSettings;

	void setButtonLines();
	static std::map<eUITextFont, UITextFont> fonts;
	static void loadFonts();
};
