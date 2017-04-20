#pragma once
#include <string>
#include "../Color.h"
#include "../BaseItems/UIElement.h"
#include "../BaseItems/Theme.h"
#include <RA8875.h>

class UIButton : public UIElement
{
public:
  enum eButtonCornerType
  {
    Square,
    Rounded
  };

  UIButton(Rectangle location, Theme *theme);
  UIButton(Rectangle location, std::string buttonText, Theme *theme);
  UIButton(Rectangle location, std::string buttonText, eTextAlignment buttonTextAlign, Theme *theme);
  UIButton(Rectangle location, std::string buttonText, eTextAlignment buttonTextAlign,
    uint16_t clickableBGColor, uint16_t clickableBorderColor, uint16_t clickableTextColor,
    uint16_t clickableIconColor, Theme *theme);

  void setTouchArea() override;
  void setCornerType(eButtonCornerType cornerType);
  void update(RA8875 *lcd) override;
  void setButtonText(std::string buttonText);

private:
  bool isClicked;

  eButtonCornerType cornerType;
  bool shadowInterpolated;
  bool touched=false;
  sThemeSettings active, clickable;

  void drawBorder(RA8875 *lcd, sThemeSettings themeSettings);
  void drawShadow(RA8875 *lcd, sThemeSettings themeSettings);
  void fillButton(RA8875 *lcd, sThemeSettings themeSettings);  
};
