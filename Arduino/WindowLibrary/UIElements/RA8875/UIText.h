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

#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
#define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
#define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif

class UIText : public UIElement
{
public:
	UIText(Adafruit_RA8875 &tft, Rectangle location, std::string text, Theme &elementTheme, eThemeObjState state);	
	UIText(Adafruit_RA8875 &tft, Rectangle location, std::string text, eThemeObjState state, 
		eUITextFont textFont, uint8_t textScale, uint16_t textColor);
	void Update() override;

	void SetText(std::string text);	
	sTouchResponse ProcessTouch(Point touchPoint) override;

private:
	std::vector<std::string> textLines;

	std::string text;
	
	eUITextFont textFont;
	uint16_t textColor;
	uint8_t textScale;

	void setButtonLines();
	static std::map<eUITextFont, UITextFont> fonts;	
	uint8_t getFontHeight();
};


#endif