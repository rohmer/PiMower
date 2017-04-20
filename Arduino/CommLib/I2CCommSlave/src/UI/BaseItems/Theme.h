#pragma once
#include <map>
#include <sstream>
#include "../Color.h"
#include <SPI.h>
#include <RA8875.h>
#include "../UIElements/Fonts.h"

enum eTextAlignment
{
	textLeft     =0,
	textCenter   =1,
	textRight    =2
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
  textAlignment,
	textFont
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
  eTextAlignment textAlignment;
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
  std::map<std::string,uint16_t> themeSettings;
};
