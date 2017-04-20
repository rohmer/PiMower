#pragma once
#include <vector>
#include <string>
#include "../BaseItems/UIElement.h"
#include "../Rectangle.h"
#include <RA8875.h>

class UIWindow : public UIElement
{
public:
  UIWindow(Rectangle location, Theme *theme);
  UIWindow(Rectangle location, std::string titleText, Theme *theme, bool hasTitleBar=true,
    bool hasCloseIcon=true, bool hasChrome=true, bool isModal=false);
  UIWindow(Rectangle location, std::string titleText,Theme *theme, bool hasTitleBar,
    bool hasCloseIcon, bool hasChrome, bool isModal, uint16_t titleBarColor,
    uint16_t titleTextColor, uint16_t chromeColor, uint16_t windowColor);

  ~UIWindow();                          // Deletes all the childElements

  void addElement(UIElement *uiElement);

  void update(RA8875 *lcd) override
  {
    needsUpdate=false;
  };

  private:
    uint16_t titleBarColor;
    uint16_t titleTextColor;
    uint16_t windowColor;
    uint16_t chromeColor;
    bool hasTitleBar, hasCloseIcon, hasChrome, isModal;
    std::string titleText;
    Rectangle location;
    void setDefaults();
};
