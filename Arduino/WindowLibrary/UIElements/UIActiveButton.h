#pragma once
#include "../Options.h"

#ifdef useActiveButton

#include <string>
#include <map>
#include <vector>
#include "../Utility/Color.h"
#include "UIElement.h"
#include <SPI.h>
#include "ControlDisplay/Button.h"

class UIActiveButton : public UIElement
{
	UIActiveButton(DriverBase &tft, Rectangle location, std::string buttonText, eUITextFont font,
		tColor textColor, uint8_t textScale, tColor buttonBGColor, uint8_t cornerRadius = 4,
		bool is3D = true, bool raised = true, uint16_t updateInMillis=1000, std::string elementName="");
	sTouchResponse ProcessTouch(Point touchPoint) override;
	virtual void Update() override;

	void SetButtonText(std::string txt);
private:
	std::string buttonText;
	eUITextFont font;
	uint8_t cornerRadius;
	bool is3D, raised;
	uint16_t updateInterval;
	uint32_t updateTime = 0;

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
