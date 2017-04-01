#include "PageDriver.h"

PageDriver::PageDriver()
{
  lcd=new RA8875(RA8875_CS,RA8875_RESET);
  lastTouchTime=millis();
  checkSleep();
  setInterval(250);
}

/****************************************
 * Turns on and off the backlight and sleep mode
 * based on the time since the device was last accessed
 */
void PageDriver::checkSleep()
{
  unsigned long currentTime=millis();
  uint16_t timeSinceTouch=((currentTime-lastTouchTime)/1000);
  if(timeSinceTouch>SECONDS_TO_BACKLIGHT_OFF)
  {
    if(timeSinceTouch>SECONDS_TO_SLEEP && !lcdSleep)
    {
      lcdSleep=true;
      lightOff=true;
      lcd->sleep(true);
#ifdef DEBUG
      Serial.println("Putting LCD to sleep");
#endif
    } else
    {
      lcdSleep=false;
      if(!lightOff)
      {
        lightOff=true;
        lcd->sleep(false);
        lcd->backlight(false);
#ifdef DEBUG
      Serial.println("Shutting off LCD backlight");
#endif
      }
    }
  } else
  {
    if(lcdSleep)
    {
#ifdef DEBUG
      Serial.println("LCD comming out of sleep mode");
#endif        
      lcd->sleep(false);
      lcdSleep=false;
    }
    if(lightOff)
    {
#ifdef DEBUG
      Serial.println("Turning on LCD back light");
#endif
      lcd->backlight(true);
      lightOff=true;
    }
  }
}

