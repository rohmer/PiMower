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
#ifdef RA8875
	UIButton(DriverBase &tft, Rectangle location, std::string buttonText, eUITextFont font,
		uint16_t textColor, uint8_t textScale, uint16_t buttonBGColor, uint8_t cornerRadius = 4,
		bool is3D=true, bool raised=true);
#endif
#ifdef FT8XX
	UIButton(DriverBase &tft, Rectangle location, std::string buttonText, eUITextFont font,
		uint32_t textColor, uint32_t buttonBGColor, uint8_t cornerRadius = 4, bool is3D = true,
		bool raised = true, uint8_t alpha=255);
#endif
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