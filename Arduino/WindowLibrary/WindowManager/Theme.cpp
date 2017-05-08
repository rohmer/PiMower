#include "Theme.h"

Theme::Theme()
{
}

void Theme::SetThemeAttribute(eThemeObjType objType, eThemeObjState objState, eThemeObjAttribute objAttribute, uint16_t value)
{
	std::string setting;
	setting.clear();
	setting += objType;
	setting += objState;
	setting += objAttribute;
	themeSettings[setting] = value;	
}

int Theme::GetThemeAttribute(eThemeObjType objType, eThemeObjState objState, eThemeObjAttribute objAttribute)
{
	std::string setting;
	setting.clear();
	setting += objType;
	setting += objState;
	setting += objAttribute;
	if (themeSettings.find(setting) == themeSettings.end())
	{
#ifdef DEBUG
		Logger::Trace("Theme setting for %d,%d,%d not found", objType, objState, objAttribute);
#endif
		return -1;
	}
	return themeSettings[setting];
}

sThemeSettings Theme::LoadTheme(eThemeObjType objType, eThemeObjState objState)
{
	sThemeSettings themeSettings;
	int val;
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::bgColor);
	if (val != -1)
	{
		themeSettings.bgColor = val;
	}
	else
	{
		themeSettings.bgColor = Color::Color32To565(16185078);
	}

	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::textColor);
	if (val != -1)
	{
		themeSettings.textColor = val;
	}
	else
	{
		themeSettings.textColor = Color::Color32To565(4539717);
	}

	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::borderColor);
	if (val != -1)
	{
		themeSettings.borderColor = val;
	}
	else
	{
		themeSettings.borderColor = Color::Color32To565(12961221);
	}

	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::iconColor);
	if (val != -1)
	{
		themeSettings.iconColor = val;
	}
	else
	{
		themeSettings.iconColor = Color::Color32To565(7829367);
	}

	val = GetThemeAttribute(eThemeObjType::dropShadow, objState, eThemeObjAttribute::shadowColor);
	if (val != -1)
	{
		themeSettings.shadowColor = val;
	}
	else
	{
		themeSettings.shadowColor = Color::Color32To565(11184810);
	}

	
	val = GetThemeAttribute(eThemeObjType::dropShadow, objState, eThemeObjAttribute::shadowThickness);
	if (val != -1)
	{
		themeSettings.shadowThickness = val;
	}
	else
	{
		themeSettings.shadowThickness = 5;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::textScale);
	if (val != -1)
	{
		if (val == 0)
			themeSettings.textScale = 1;
		else
			if (val == 1)
				themeSettings.textScale = 2;
			else
				if (val == 2)
					themeSettings.textScale = 3;
				else
					themeSettings.textScale = 1;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::textSpacing);
	if (val != -1)
	{
		themeSettings.textSpacing = val;
	}
	else
	{
		themeSettings.textSpacing = 0;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::textInterlineSpacing);
	if (val != -1)
	{
		themeSettings.textInterlineSpacing = val;
	}
	else
	{
		themeSettings.textInterlineSpacing = 0;
	}

	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::windowHeadingBGColor);
	if (val != -1)
	{
		themeSettings.windowHeadingBGColor = val;
	}
	else
	{
		themeSettings.windowHeadingBGColor = 0;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::windowHeadingTextColor);
	if (val != -1)
	{
		themeSettings.windowHeadingTextColor = val;
	}
	else
	{
		themeSettings.windowHeadingTextColor = 0;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::windowBGColor);
	if (val != -1)
	{
		themeSettings.windowBGColor = val;
	}
	else
	{
		themeSettings.windowBGColor = 0;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::windowChromeColor);
	if (val != -1)
	{
		themeSettings.windowChromeColor = val;
	}
	else
	{
		themeSettings.windowChromeColor = 0;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::windowFrameColor);
	if (val != -1)
	{
		themeSettings.windowFrameColor = val;
	}
	else
	{
		themeSettings.windowFrameColor = 0;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::textAlignmentHoriz);
	if (val != -1)
	{
		themeSettings.textAlignmentHoriz = static_cast<eTextAlignment>(val);
	}
	else
	{
		themeSettings.textAlignmentHoriz = eTextAlignment::Center;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::textAlignmentVertical);
	if (val != -1)
	{
		themeSettings.textAlignmentVertical = static_cast<eTextAlignment>(val);
	}
	else
	{
		themeSettings.textAlignmentVertical = eTextAlignment::Middle;
	}

	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::textInterlineSpacing);
	if (val != -1)
	{
		themeSettings.textInterlineSpacing = val;
	}
	else
	{
		themeSettings.textInterlineSpacing = 0;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::textSpacing);
	if (val != -1)
	{
		themeSettings.textSpacing = val;
	}
	else
	{
		themeSettings.textSpacing = 0;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::textFont);
	if (val != -1)
	{
		themeSettings.textFont = static_cast<eUITextFont>(val);
	}
	else
	{
		themeSettings.textFont = eUITextFont::AileronRegular12;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::cornerType);
	if (val != -1)
	{
		themeSettings.cornerType = static_cast<eCornerType>(val);
	}
	else
	{
		themeSettings.cornerType = eCornerType::Square;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::activeOnRelease);
	if (val != -1)
	{
		if (val == 1)
			themeSettings.activeOnRelease = true;
		else
			themeSettings.activeOnRelease = false;
	}
	else
	{
		themeSettings.activeOnRelease = true;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::borderSize);
	if (val != -1)
	{		
		themeSettings.borderSize= val;		
	}
	else
	{
		themeSettings.borderSize = 4;
	}
	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::borderColor);
	if (val != -1)
	{
		themeSettings.borderColor = val;
	}
	else
	{
		themeSettings.borderColor = Color::White;
	}

	val = GetThemeAttribute(objType, objState, eThemeObjAttribute::cornerRadius);
	if (val != -1)
	{
		themeSettings.cornerRadius = val;
	}
	else
	{
		themeSettings.cornerRadius= 5;
	}
	return (themeSettings);
}