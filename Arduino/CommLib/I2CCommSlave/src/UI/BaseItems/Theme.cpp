#include "Theme.h"

Theme::Theme()
{
}

void Theme::SetThemeAttribute(eThemeObjType objType, eThemeObjState objState, eThemeObjAttribute objAttribute, uint16_t value)
{
  std::stringstream ss;
  ss << objType;
  ss << objState;
  ss << objAttribute;
  themeSettings.emplace(ss.str(), value);
}

int Theme::GetThemeAttribute(eThemeObjType objType, eThemeObjState objState, eThemeObjAttribute objAttribute)
{
  std::stringstream ss;
  ss << objType;
  ss << objState;
  ss << objAttribute;
  if(themeSettings.find(ss.str())==themeSettings.end())
  {
    return -1;
  }
  return themeSettings[ss.str()];
}

sThemeSettings Theme::LoadTheme(eThemeObjType objType, eThemeObjState objState)
{
    sThemeSettings themeSettings;
    int val;
    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::bgColor);
    if(val!=-1)
    {
      themeSettings.bgColor=val;
    } else
    {
      themeSettings.bgColor=Color::Color32To565(16185078);
    }

    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::textColor);
    if(val!=-1)
    {
      themeSettings.textColor=val;
    } else
    {
      themeSettings.textColor=Color::Color32To565(4539717);
    }

    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::borderColor);
    if(val!=-1)
    {
      themeSettings.borderColor=val;
    } else
    {
      themeSettings.borderColor=Color::Color32To565(12961221);
    }

    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::iconColor);
    if(val!=-1)
    {
      themeSettings.iconColor=val;
    } else
    {
      themeSettings.iconColor=Color::Color32To565(7829367);
    }

    val=GetThemeAttribute(eThemeObjType::dropShadow, eThemeObjState::defaultState, eThemeObjAttribute::shadowColor);
    if(val!=-1)
    {
      themeSettings.shadowColor=val;
    } else
    {
      themeSettings.shadowColor=Color::Color32To565(11184810);
    }

    val=GetThemeAttribute(eThemeObjType::dropShadow, eThemeObjState::defaultState, eThemeObjAttribute::shadowOpacity);
    if(val!=-1)
    {
      themeSettings.shadowOpacity=val;
    } else
    {
      themeSettings.shadowOpacity=30;
    }

    val=GetThemeAttribute(eThemeObjType::dropShadow, eThemeObjState::defaultState, eThemeObjAttribute::shadowThickness);
    if(val!=-1)
    {
      themeSettings.shadowThickness=val;
    } else
    {
      themeSettings.shadowThickness=5;
    }
    val=GetThemeAttribute(eThemeObjType::dropShadow, eThemeObjState::defaultState, eThemeObjAttribute::shadowInterpolated);
    if(val==1)
    {
      themeSettings.shadowInterpolated=true;
    } else
    {
      themeSettings.shadowInterpolated=false;
    }
    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::textScale);
    if(val!=-1)
    {
      if(val==0)
        themeSettings.textScale=RA8875tsize::X16;
        else
          if(val==1)
            themeSettings.textScale=RA8875tsize::X24;
            else
              if(val==2)
                themeSettings.textScale=RA8875tsize::X32;
                else
                  themeSettings.textScale=RA8875tsize::X24;
    }
    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::textSpacing);
    if(val!=-1)
    {
      themeSettings.textSpacing=val;
    } else
    {
      themeSettings.textSpacing=0;
    }
    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::textInterlineSpacing);
    if(val!=-1)
    {
      themeSettings.textInterlineSpacing=val;
    } else
    {
      themeSettings.textInterlineSpacing=0;
    }

    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::windowHeadingBGColor);
    if(val!=-1)
    {
      themeSettings.windowHeadingBGColor=val;
    } else
    {
      themeSettings.windowHeadingBGColor=0;
    }
    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::windowHeadingTextColor);
    if(val!=-1)
    {
      themeSettings.windowHeadingTextColor=val;
    } else
    {
      themeSettings.windowHeadingTextColor=0;
    }
    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::windowBGColor);
    if(val!=-1)
    {
      themeSettings.windowBGColor=val;
    } else
    {
      themeSettings.windowBGColor=0;
    }
    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::windowChromeColor);
    if(val!=-1)
    {
      themeSettings.windowChromeColor=val;
    } else
    {
      themeSettings.windowChromeColor=0;
    }
    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::windowFrameColor);
    if(val!=-1)
    {
      themeSettings.windowFrameColor=val;
    } else
    {
      themeSettings.windowFrameColor=0;
    }
    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::textAlignment);
    if(val!=-1)
    {
      themeSettings.textAlignment=static_cast<eTextAlignment>(val);
    } else
    {
      themeSettings.textAlignment=eTextAlignment::textCenter;
    }
    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::textInterlineSpacing);
    if(val!=-1)
    {
      themeSettings.textInterlineSpacing=val;
    } else
    {
      themeSettings.textInterlineSpacing=0;
    }
    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::textSpacing);
    if(val!=-1)
    {
      themeSettings.textSpacing=val;
    } else
    {
      themeSettings.textSpacing=eTextAlignment::textCenter;
    }
    val=GetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::textFont);
    if(val!=-1)
    {
      themeSettings.textFont=static_cast<eUITextFont>(val);
    } else
    {
      themeSettings.textFont=eUITextFont::Alef14;
    }
    return (themeSettings);
}
