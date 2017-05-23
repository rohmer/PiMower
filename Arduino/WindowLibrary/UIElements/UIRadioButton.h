#pragma once
#include "../Options.h"
#include <string>
#include <map>
#include <vector>
#include "../Utility/Color.h"
#include "UIElement.h"
#include <SPI.h>
#include "../Utility/Rectangle.h"
#include "ControlDisplay/RadioButton.h"


class UIRadioButton : public UIElement
{
public:
#ifdef RA8875
	UIRadioButton(DriverBase &tft, Rectangle location, std::string text, bool checked, eUITextFont textFont, 
		uint16_t textColor, uint8_t textScale, uint16_t controlColor, uint16_t checkColor, bool is3D=true, 
		bool textToRight=true, std::string elementName = "");
#endif
#ifdef FT8XX
	UIRadioButton(DriverBase &tft, Rectangle location, std::string text, bool checked, eUITextFont textFont,
		uint32_t textColor,  uint32_t controlColor, uint32_t checkColor, bool is3D = true,
		bool textToRight = true, std::string elementName = "");
#endif
	void Update() override;
	void SetText(std::string text);
	void SetChecked(bool checked);
	bool IsChecked()
	{
		return isChecked;
	}
	sTouchResponse ProcessTouch(Point touchPoint) override;
	
private:	
	std::string buttonText;
	bool isChecked, is3D, textRight;
	eUITextFont textFont;
#ifdef RA8875
	uint16_t textColor, controlColor, checkColor;
	uint8_t textScale;	
#endif
#ifdef FT8XX
	uint32_t textColor, controlColor, checkColor;
#endif
	Rectangle *checkRect = NULL;
};
