#pragma once
#include "../Options.h"

#ifdef useButton

#include <string>
#include <map>
#include <vector>
#include "../Utility/Color.h"
#include "UIElement.h"
#include <SPI.h>
#include "ControlDisplay\Button.h"

class UIButton : public UIElement
{
public:
	UIButton(DriverBase &tft, Rectangle location, std::string buttonText, eUITextFont font,
		tColor textColor, uint8_t textScale, tColor buttonBGColor, uint8_t cornerRadius = 4,
		bool is3D=true, bool raised=true, std::string elementName = "");
	sTouchResponse ProcessTouch(Point touchPoint) override;
	void Update() override;

	void SetButtonText(std::string txt);

private:
	std::string buttonText;
	eUITextFont font;
	uint8_t cornerRadius;
	bool is3D, raised;
#ifdef RA8875
	uint16_t textColor, buttonBGColor;
	uint8_t textScale;
	uint8_t alpha = 255;
	
#endif
#ifdef FT8XX
	uint32_t textColor, buttonBGColor;		
#endif
};

#endif