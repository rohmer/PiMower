#include "LCDPage.h"

class IdleScreen : public LCDPage
{
public:
  IdleScreen(RA8875 *lcd, bool clearScreen);
  void drawScreen() override;
  
private:

    
};

