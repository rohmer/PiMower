#include <RA8875.h>
#include <vector>
#include "../LCDPage.h"
#include "MenuItem.h"

class Menu : public LCDPage
{
public:
  Menu(RA8875 *lcd, bool clearScreen, uint8_t pageIdx, String menuTitle);
  void addMenuItem(String itemName, uint8_t pageIndex);
  uint8_t getPageIdx()
  {
    return pageIdx;
  }

  void setPageIdx(uint8_t idx)
  {
    pageIdx=idx;
  }

  void drawScreen();

private:
  String menuTitle;
  std::vector<menuItem_s> menuItems;
  uint8_t pageIdx;
};
