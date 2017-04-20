#pragma once
#include <string>
#include <map>
#include <vector>
#include "../Color.h"
#include "../BaseItems/UIElement.h"
#include "../BaseItems/Theme.h"
#include <RA8875.h>
#include "Fonts.h"

struct UITextFont
{
  uint8_t width;
  uint8_t height;
};

class UIText : public UIElement
{
public:
  UIText(Rectangle location, std::string text, Theme *theme);
  UIText(Rectangle location, std::string text, eUITextFont font);

  static Rectangle GetFontRect(std::string text, eUITextFont font);
  static Rectangle GetFontRect(std::string text, eUITextFont font, uint8_t interlineSpacing, uint8_t textSpacing);

  void setTouchArea() override;
  void update(RA8875 *lcd) override;

  void setText(std::string text);

private:
  std::vector<std::string> buttonTextLines;

  std::string buttonText;
  sThemeSettings themeSettings;

  void setButtonLines();
  static std::map<eUITextFont,UITextFont> fonts;
  static void loadFonts();
};
