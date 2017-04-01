#include "LCDPage.h"

LCDPage::LCDPage(RA8875 *lcd, bool clearScreen,uint8_t pageIdx)
{
  this->lcd=lcd;
  if(clearScreen)
    lcd->clearActiveWindow(true);
   this->pageIndex=pageIdx;
}

/*
 * Draws standard header info (Battery, if wifi is connected, and the time)
 * The header bar is 800x40
 */
void LCDPage::drawScreen()
{
  if(!pageDirty)
    return;
  lcd->fillRect(0,0,800,40,0xA65A);
  if(wifiConnected)
  {
    lcd->drawPixels(wifiOn,1620,670,5);
  } else
  {
    lcd->drawPixels(wifiOff,1225,675,5);
  }
  if(batteryPct>85)
  {
     lcd->drawPixels(battery100pct,2040,720,5);
  } else if(batteryPct>60)
  {
     lcd->drawPixels(battery85pct,2040,720,5);
  } else if(batteryPct>45)
  {
     lcd->drawPixels(battery60pct,2040,720,5);
  } else if(batteryPct>30)
  {
     lcd->drawPixels(battery45pct,2040,720,5);
  } else if(batteryPct>15)
  {
     lcd->drawPixels(battery30pct,2040,720,5);
  }  else if(batteryPct>7)
  {
     lcd->drawPixels(battery15pct,2040,720,5);
  }else 
  {
     lcd->drawPixels(battery0pct,2040,720,5);
  }  

  // Draw the date and time
  time_t now=time(0);
  String timeStr=ctime(&now);
  lcd->setTextColor(0xFFFF);
  lcd->setFontSize(RA8875tsize::X32);
  lcd->setCursor(10,5,false);
  lcd->print(timeStr);
  pageDirty=false;
}

