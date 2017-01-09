#include "UIElement.h"

UIElement::UIElement(Point location)
	: clickable(false)
	, location(location)
	, updateCycle(-1)
	, elementArea(Rectangle(location.x, location.y,0,0))
{
	updateTime = std::chrono::system_clock::now();
}

UIElement::UIElement(Point location, bool clickable)
	: location(location)
	, clickable(clickable)
	, updateCycle(-1)
	, elementArea(Rectangle(location.x, location.y, 0, 0))
{	
	updateTime = std::chrono::system_clock::now();
}

bool UIElement::pointTouches(Point pt)
{
	if (!clickable)
		return false;
	return elementArea.contains(pt);
}

void UIElement::setClickable(bool value)
{
	clickable = value;
}

void UIElement::setUpdateCycle(int msBetweenUpdate)
{
	updateCycle = msBetweenUpdate;
}

bool UIElement::updateNeeded()
{
	if (!elementEnabled)
		return false;
	if (std::chrono::system_clock::now() > updateTime)
	{
		if (updateCycle == -1)
		{			
			updateTime = std::chrono::system_clock::now() + std::chrono::hours(12);
		}
		else
		{
			updateTime = std::chrono::system_clock::now() + std::chrono::milliseconds(updateCycle);
		}
		return true;
	}
	return false;
}

void UIElement::forceUpdate()
{
	updateTime = std::chrono::system_clock::now();
}

void UIElement::enabled(bool value)
{
	elementEnabled = value;
}