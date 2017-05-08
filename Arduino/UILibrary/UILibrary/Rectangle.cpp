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

void Rectangle::update()
{
	if (x1 < x2)
		this->width = x2 - x1;
	else
		this->width = x1 - x2;
	if (y1 < y2)
		this->height = y2 - y1;
	else
		this->height = y1 - y2;
}

bool Rectangle::occludes(Rectangle backgroundRect)
{
	if (this->x1<backgroundRect.x2 && this->x2>backgroundRect.x1 &&
		this->y1 > backgroundRect.y2 && this->y2 < backgroundRect.y1)
		return true;
	return false;
}