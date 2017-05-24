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
	UIRadioButton(DriverBase &tft, Rectangle location, std::string text, bool checked, eUITextFont textFont, 
		tColor textColor, uint8_t textScale, tColor  controlColor, tColor  checkColor, bool is3D=true,
		bool textToRight=true, std::string elementName = "");
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
