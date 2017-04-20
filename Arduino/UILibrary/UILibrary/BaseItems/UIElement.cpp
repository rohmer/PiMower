#include "UIElement.h"

UIElement::UIElement(Point position, bool needsUpdate, bool uiTarget, Theme *theme)
{
	this->needsUpdate = needsUpdate;
	this->uiTarget = uiTarget;
	this->position = position;
	elementArea = Rectangle(0, 0, 0, 0);
	this->elementID = micros();
	touchArea = new Rectangle(-1, -1, -1, -1);
	this->theme = theme;
	needsUpdate = true;
}

bool UIElement::ptInElement(Point pt)
{
	if (!uiTarget)
		return false;
	return (elementArea.contains(pt));
}