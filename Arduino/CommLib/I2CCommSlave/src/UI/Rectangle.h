#pragma once
#include "Point.h"

struct Rectangle
{
public:
  Rectangle(int x1, int y1, int x2, int y2)
    : x1(x1)
    , y1(y1)
    , x2(x2)
    , y2(y2)
  {
    if(x2<x1)
    {
      int t=x1;
      x1=x2;
      x2=t;
    }
    if(y2<y1)
    {
      int t=y1;
      y1=y2;
      y2=t;
    }
    if (x1 < x2)
      width = x2 - x1;
    else
      width = x1 - x2;
    if (y1 < y2)
      height = y2 - y1;
    else
      height = y1 - y2;
  }
  Rectangle()
    : x1(0)
    , y1(0)
    , x2(0)
    , y2(0)
    , width(0)
    , height(0)
  {
  }

  bool hasArea()
  {
    if(x1==x2 && y1==y2)
      return false;
    return true;
  }

  Point center()
  {
    return Point((x2-x1)/2,(y2-y1)/2);
  }
  void update();
  bool contains(Point pt) const;
  int x1, y1, x2, y2, width, height;
};
