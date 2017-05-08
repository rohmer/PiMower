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

class UIAlphaNumericEditor : public UIElement
{
public:

	UIAlphaNumericEditor(DriverBase &tft, Theme &elementTheme, std::string editorText="");
	UIAlphaNumericEditor(DriverBase &tft, std::string editorText,  eUITextFont textFont,
		uint16_t textColor,	uint16_t buttonBGColor, uint16_t chromeColor, uint8_t borderSize,
		uint16_t shadowColor, uint8_t shadowSize, uint8_t textScale=2);

	void Update() override;
	sTouchResponse ProcessTouch(Point pt) override;

private:
	enum eKeyboards
	{
		normal,
		shifted,
		symbol
	};
	enum eSpecialKeys
	{
		normalKey,
		backspace,
		caps,
		shift,
		enter,
		space,
		nullKey,			// Denotes whitespace
		symbolKeys,
		alpha
	};

	struct sKeys
	{
		char character;
		uint8_t keyWidth;				// in 8ths of a standard key, ex: 12=1.5		
		eSpecialKeys specialKey;
		sKeys(char character, uint8_t keyWidth)
		{
			this->character = character;
			this->keyWidth = keyWidth;
			this->specialKey = eSpecialKeys::normalKey;
		}
		sKeys(char character, uint8_t keyWidth, eSpecialKeys specialKey)
		{
			this->character = character;
			this->keyWidth = keyWidth;
			this->specialKey = specialKey;
		}
	};
	struct sKeyboard
	{
		eKeyboards keyBoardType;
		std::vector<std::vector<sKeys> >	keys;		// Outer is rows, inner is keys
	};

	std::string editorText;
	eUITextFont textFont;
	uint16_t textColor, buttonBGColor, chromeColor, shadowColor;
	uint8_t borderSize, shadowSize;
	uint16_t tftWidth, tftHeight;
	uint8_t tftRotation;
	uint8_t xCharPtr = 0;
	uint8_t textScale;

	std::vector<sKeyboard> keyboards;
	void setupScreenKeys();
	eKeyboards currentKeyboard = eKeyboards::normal;	
};

#endif