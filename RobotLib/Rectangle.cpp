#include "Rectangle.h"

bool Rectangle::contains(Point pt) const
{
	int pointX = pt.x;
	int pointY = pt.y;
	if (pointX<(this->x1 + (0.5*this->width)) && pointX>(this->x1 - (0.5*this->width)) && 
		pointY < (this->y1 + (0.5*this->height)) && pointY < (this->y1 - (0.5*this->height)))
		return true;
	return false;
}
