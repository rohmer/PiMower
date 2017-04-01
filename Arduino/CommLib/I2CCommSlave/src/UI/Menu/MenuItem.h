#pragma once
#include "../Rectangle.h"

struct menuItem_s
{
  String itemText;
  int pageIdx;
  LCDPage *linkedPage;
  Rectangle touchArea;
};
