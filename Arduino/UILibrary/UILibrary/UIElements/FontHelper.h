#pragma once
#include "../External/Adafruit_GFX_Library/Adafruit_GFX.h"
#include "../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "../Options.h"
#include "Fonts.h"

class FontHelper
{
public:
	static void setLCDFont(Adafruit_RA8875 *lcd, eUITextFont font);
};
