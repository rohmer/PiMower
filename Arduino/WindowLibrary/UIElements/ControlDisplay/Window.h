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

	static Rectangle Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
		tColor titleBarBGColor, tColor titleBarTextColor, tColor controlColor, tColor borderColor,
		tColor windowBGColor, std::string titleText, eUITextFont font, bool hasChrome, bool hasTitleBar,
		bool hasCloseIcon, bool is3D = true, uint8_t cornerRadius = 4, uint8_t alpha = 255);
};