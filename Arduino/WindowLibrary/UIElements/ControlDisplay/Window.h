#pragma once
#include "../../Options.h"
#include "../../Utility/Color.h"
#ifdef FT8XX
#include "../FT8XX/UIPrimitives.h"
#endif
#ifdef RA8875
#include "../RA8875/UIPrimitives.h"
#endif

// Window is simply required, as the window manager uses it
// therefore there is no ifdef to remove it

class Window
{
public:
#ifdef RA8875
	static Rectangle Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height, 
		uint16_t titleBarBGColor, uint16_t titleBarTextColor, uint16_t controlColor, uint16_t borderColor,
		uint16_t windowBGColor,
		std::string titleText, eUITextFont font, bool hasChrome, bool hasTitleBar, bool hasCloseIcon, 
		bool is3D = true, uint8_t cornerRadius = 4, uint8_t alpha = 255);
#endif 

#ifdef FT8XX
	static Rectangle Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
		uint32_t titleBarBGColor, uint16_t titleBarTextColor, uint32_t controlColor, uint32_t borderColor,
		uint32_t windowBGColor,
		std::string titleText, eUITextFont font, bool hasChrome, bool hasTitleBar, bool hasCloseIcon,
		bool is3D = true, uint8_t cornerRadius = 4, uint8_t alpha = 255);
#endif
};