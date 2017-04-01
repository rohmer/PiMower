#include "UIElement.h"

UIElement::UIElement(Point position, bool needsUpdate, bool uiTarget, RA8875 *ra8875)
{
	this->needsUpdate = needsUpdate;
	this->uiTarget = uiTarget;
	this->position = position;
	elementArea = Rectangle(0, 0, 0, 0);
}

bool UIElement::ptInElement(Point pt)
{
	if (!uiTarget)
		return false;
	return (elementArea.contains(pt));		
}