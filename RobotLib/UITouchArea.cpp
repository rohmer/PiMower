#include "UITouchArea.h"

UITouchArea::UITouchArea(Point position,
	uint width,
	uint height)
	: UIElement(position, false, true)
{
	this->width = width;
	this->height = height;
	setArea();
}

void UITouchArea::setArea()
{
	elementArea = Rectangle(position.x, position.y, position.x + width, position.y + height);
}

void UITouchArea::update(DigoleLCD *lcd, RobotLib *robotLib)
{
	return;
}

int UITouchArea::processTouch(Point pt)
{
	return 1;
}