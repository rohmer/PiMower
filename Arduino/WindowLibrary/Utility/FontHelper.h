#pragma once
#include "../Options.h"
#include "../Utility/Color.h"

#ifdef RA8875
#include "../External/Adafruit_GFX_Library/Adafruit_GFX.h"
#include "../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "../Utility/Rectangle.h"
#include "../Utility/Logger.h"
#include "../UIElements/RA8875/Fonts.h"
#include "../Driver/DriverBase.h"

class FontHelper
{
public:
	static void setLCDFont(Adafruit_RA8875 *lcd, eUITextFont font);	
	static Rectangle GetTextRect(DriverBase &tft,std::string text, eUITextFont font, Point textLoc);	
};

#endif

#ifdef FT8XX
#include "../Utility/Rectangle.h"
#include "../Utility/Logger.h"
#include "../UIElements/FT8XX/Fonts.h"
#include "../Driver/DriverBase.h"
class FontHelper
{
public:
	static Rectangle GetTextRect(DriverBase &lcd, std::string text, eUITextFont font, Point textLoc);
};

#endif
