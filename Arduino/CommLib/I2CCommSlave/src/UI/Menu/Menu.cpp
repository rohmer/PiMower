#include "Menu.h"

Menu::Menu(RA8875 *lcd, bool clearScreen, uint8_t pageIdx, String menuTitle) :
  LCDPage(lcd,clearScreen,pageIdx)
{
  this->menuTitle=menuTitle;
  pageDirty=true;
}

void Menu::drawScreen()
{
  if(!pageDirty)
    return;
  LCDPage::drawScreen();

  // Our screen is from 41 to 480 vertically
  lcd->setTextColor(lcd->Color565(255,255,0));
  lcd->setFontSize(RA8875tsize::X32);
  lcd->setCursor(10,41,false);
  lcd->print(menuTitle);
  lcd->setColor(lcd->Color565(255,255,255),lcd->Color565(0,0,0));
  lcd->setTextColor(lcd->Color565(255,255,255));
  lcd->drawLine(0,73,800,73,lcd->Color565(0,0,0));
  lcd->drawLine(0,74,800,74,lcd->Color565(0,0,0));
  int lineHeight=32;
  int interlineSpace=2;
  int startY=76;
  for(int y=0; y<menuItems.size(); y++)
  {
    lcd->setCursor(10,startY+((lineHeight+interlineSpace)*y));
    lcd->print(menuItems[y].itemText);
  }
}

void Menu::addMenuItem(String itemName, uint8_t pageIndex)
{
  menuItem_s menuItem;
  menuItem.itemText=itemName;
  menuItem.pageIdx=pageIndex;
  menuItems.emplace(menuItems.end(),menuItem);
}
