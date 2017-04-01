#include <RA8875.h>
#include <StaticThreadController.h>
#include <Thread.h>
#include <ThreadController.h>
#include <map>
#include "Menu\Menu.h"
#include "Settings.h"

class PageDriver : public Thread
{
  public:
    PageDriver();

  private:
    RA8875 *lcd;
    std::map<uint8_t,LCDPage*> pages;
    void reconcilePages();
    bool pagesDirty=false;              // If we add or remove any pages, set to true so we can update the links
    unsigned long lastTouchTime;

    bool lcdSleep=false;
    bool lightOff=false;

    void checkSleep();
    void run();

};
