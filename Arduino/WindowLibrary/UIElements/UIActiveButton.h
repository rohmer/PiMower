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
#ifdef RA8875
	UIActiveButton(DriverBase &tft, Rectangle location, std::string buttonText, eUITextFont font,
		uint16_t textColor, uint8_t textScale, uint16_t buttonBGColor, uint8_t cornerRadius = 4,
		bool is3D = true, bool raised = true, uint16_t updateInMillis=1000);
#endif
#ifdef FT8XX
	UIActiveButton(DriverBase &tft, Rectangle location, std::string buttonText, eUITextFont font,
		uint32_t textColor, uint32_t buttonBGColor, uint8_t cornerRadius = 4, bool is3D = true,
		bool raised = true, uint8_t alpha = 255, uint16_t updateInMillis = 1000);
#endif
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
