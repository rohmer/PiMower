#pragma once
#include <map>
#include <sstream>
#include <SPI.h>

#include "../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "../UIElements/Fonts.h"
#include "../Color.h"

struct UITextFont
{
	uint8_t width;
	uint8_t height;
};

enum eTextAlignment
{
	// Vertical
	Top,
	Middle,
	Bottom,
	Left,
	Center,
	Right
};

enum eThemeObjType
{
	clickable,
	highlight,
	error,
	window,
	modalWindow,
	dropShadow
};

enum eThemeObjState
{
	defaultState,
	activeState
};

enum eCornerType
{
	Square = 0,
	Rounded = 1
};

enum eThemeObjAttribute
{
	bgColor,
	borderColor,
	textColor,
	iconColor,
	windowHeadingBGColor,
	windowHeadingTextColor,
	windowBGColor,
	windowChromeColor,
	windowFrameColor,
	borderSize,
	shadowColor,
	shadowOpacity,
	shadowThickness,
	shadowInterpolated,
	textScale,
	textInterlineSpacing,
	textSpacing,
	textAlignmentHoriz,
	textAlignmentVertical,
	textFont,
	cornerType
};

struct sThemeSettings
{
	uint16_t bgColor,
		borderColor,
		textColor,
		iconColor,
		windowHeadingBGColor,
		windowHeadingTextColor,
		windowBGColor,
		windowChromeColor,
		windowFrameColor,
		borderSize,
		shadowColor,
		shadowOpacity,
		shadowThickness,
		shadowInterpolated,
		textScale,
		textInterlineSpacing,
		textSpacing;
	eTextAlignment textAlignmentHoriz;
	eTextAlignment textAlignmentVertical;
	eCornerType cornerType;
	eUITextFont textFont;
};

class Theme
{
public:
	Theme();
	void SetThemeAttribute(eThemeObjType objType, eThemeObjState objState, eThemeObjAttribute objAttribute, uint16_t value);
	int GetThemeAttribute(eThemeObjType objType, eThemeObjState objState, eThemeObjAttribute objAttribute);
	sThemeSettings LoadTheme(eThemeObjType objType, eThemeObjState objState);

private:
	std::map<std::string, uint16_t> themeSettings;
};
