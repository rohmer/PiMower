#include "UIWindow.h"

UIWindow::UIWindow(Rectangle location, Theme *theme) :
  UIElement(Point(location.x1, location.y1),false,true, theme)
{
  elementArea=location;
}

UIWindow::UIWindow(Rectangle location,std::string titleText, Theme *theme,
  bool hasTitleBar, bool hasCloseIcon, bool hasChrome, bool isModal) :
  UIElement(Point(location.x1, location.y1),false,true,theme)
{
  this->titleText=titleText;
  this->hasTitleBar=hasTitleBar;
  this->hasCloseIcon=hasCloseIcon;
  this->hasChrome=hasChrome;
  this->isModal=isModal;
  elementArea=location;
}

UIWindow::UIWindow(Rectangle location, std::string titleText,Theme *theme,
  bool hasTitleBar, bool hasCloseIcon, bool hasChrome, bool isModal,
  uint16_t titleBarColor, uint16_t titleTextColor, uint16_t chromeColor,
  uint16_t windowColor) :
  UIElement(Point(location.x1, location.y1),false,true,theme)
{
  this->titleText=titleText;
  this->hasTitleBar=hasTitleBar;
  this->hasCloseIcon=hasCloseIcon;
  this->titleBarColor=titleBarColor;
  this->titleTextColor=titleTextColor;
  this->chromeColor=chromeColor;
  this->windowColor=windowColor;
  this->hasChrome=hasChrome;
  elementArea=location;
}

void UIWindow::setDefaults()
{
  this->titleText="";
  this->hasTitleBar=false;
  this->hasCloseIcon=false;
  this->hasChrome=false;
  this->isModal=false;
  elementArea=location;
}

void UIWindow::addElement(UIElement *element)
{
  childElements.push_back(element);
  element->Invalidate();
}
