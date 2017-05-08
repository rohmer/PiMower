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
	this->width = abs(x2 - x1);
	this->height = abs(y2 - y1);
	center.x = x1 + width / 2;
	center.y = y1 + height / 2;
}

bool Rectangle::occludes(Rectangle backgroundRect)
{
	if (this->x1<backgroundRect.x2 && this->x2>backgroundRect.x1 &&
		this->y1 > backgroundRect.y2 && this->y2 < backgroundRect.y1)
		return true;
	return false;
}