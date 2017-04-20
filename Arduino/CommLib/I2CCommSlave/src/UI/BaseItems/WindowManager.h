#pragma once
#include "../DisplayConst.h"
#include <vector>
#include "../UIElements/UIWindow.h"
#include "../Rectangle.h"
#include "Theme.h"
#include "../Color.h"

/*
 * Handles drawing, updating, processing of touch for all displayed items
 */
class WindowManager
{
private:
  static WindowManager *s_instance;
  WindowManager(const uint8_t CS, const uint8_t RST=255, const uint8_t MOSI=11,
    const uint8_t SCLK=13, const uint8_t MISO=12);
  WindowManager(Rectangle displaySize, const uint8_t CS,const uint8_t RST=255,
    const uint8_t MOSI=11,const uint8_t SCLK=13,const uint8_t MISO=12);

public:
  static WindowManager *instance()
  {
    return s_instance;
  }
  static WindowManager *instance(const uint8_t CS,const uint8_t RST=255,const uint8_t MOSI=11,const uint8_t SCLK=13,const uint8_t MISO=12)
  {
    if(!s_instance)
    {
      s_instance=new WindowManager(CS, RST, MOSI, SCLK, MISO);
    }
    return s_instance;
  }
  static WindowManager *instance(Rectangle displaySize, const uint8_t CS,const uint8_t RST=255,const uint8_t MOSI=11,const uint8_t SCLK=13,const uint8_t MISO=12)
  {
    if(!s_instance)
    {
      s_instance=new WindowManager(displaySize, CS, RST, MOSI, SCLK, MISO);
    }
    return s_instance;
  }

  static void SetThemeAttribute(eThemeObjType objType, eThemeObjState objState, eThemeObjAttribute objAttribute, uint16_t value);
  static int GetThemeAttribute(eThemeObjType objType, eThemeObjState objState, eThemeObjAttribute objAttribute);

  ~WindowManager();

private:
  UIWindow *baseWindow;     // All other windows, items, etc will be child elements
                            // of this chromeless window
  RA8875 *lcd;
  Rectangle displaySize;
  std::vector<UIElement *> childElements;

  void createBaseWindow();
  static void setDefaultTheme();

  static Theme *theme;

};
