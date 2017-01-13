#include "UIWindow.h"

UIWindow::UIWindow(Rectangle location, std::string statusText) 
	: UIElement(Point(location.x1, location.y1))
	, statusText(statusText)
	, border(true)
	, statusBar(true)
	, borderColor(1)
	, statusBarBGColor(35)
	, statusBarTextColor(252)	
	, windowBGColor(255)
{
	elementArea = location;
	getWindowArea();
	// Update Cycle will be based on lowest added child element
	setUpdateCycle(-1);
	forceUpdate();
}

UIWindow::UIWindow(Rectangle location,
	bool useBorder,
	uint8_t borderColor,
	bool statusBar, 
	std::string statusText,
	uint8_t statusBarBGColor,
	uint8_t statusBarTextColor,
	UIFont::eFontName font,
	uint8_t windowBGColor) 
	: UIElement(Point(location.x1, location.y1))
	, statusText(statusText)
	, border(useBorder)
	, statusBar(statusBar)
	, borderColor(borderColor)
	, statusBarBGColor(statusBarBGColor)
	, statusBarTextColor(statusBarTextColor)	
	, font(font)
	, windowBGColor(windowBGColor)
{
	elementArea = location;
	getWindowArea();
	// Update Cycle will be based on lowest added child element
	setUpdateCycle(-1);
	forceUpdate();
}

// Size is defined by user on init or be resize
Rectangle UIWindow::calcSize()
{
	getWindowArea();
	return elementArea;
}

Rectangle UIWindow::getWindowArea()
{
	Rectangle windowArea = elementArea;
	if (border)
	{
		windowArea.x1++;
		windowArea.y1++;
		windowArea.x1--;
		windowArea.y1--;		
	}
	fontHeight = UIFont::getFontHeight(font);
	fontWidth = UIFont::getFontWidth(font);
	if (statusBar)
	{
		windowArea.y1 += fontHeight + 2;
	}
}

void UIWindow::resize(Rectangle newSize)
{
	elementArea = newSize;
	getWindowArea();
	forceUpdate();
}

void UIWindow::update(DigoleLCD *lcdDriver)
{
	if (!this->updateNeeded())
		return;
	// First we draw the window
	if (border)
	{
		lcdDriver->setColor(borderColor);			
		if (elementArea.width == 0)
		{
			if (elementArea.x1 < elementArea.x2)
			{
				elementArea.width = elementArea.x2 - elementArea.y1;
			}
			else
			{
				elementArea.width = elementArea.x1 - elementArea.y1;
			}
		}
		if (elementArea.height == 0)
		{
			if (elementArea.y1 < elementArea.y2)
			{
				elementArea.height = elementArea.y2 - elementArea.y1;
			}
			else
			{
				elementArea.height = elementArea.y1 - elementArea.y2;
			}
		}
		lcdDriver->drawBox(elementArea.x1, elementArea.y1, elementArea.width, elementArea.height);
	}
	if (statusBar)
	{
		lcdDriver->setColor(statusBarBGColor);
		lcdDriver->drawBoxFill(elementArea.x1 + 1, elementArea.y1 + 1, elementArea.width - 2, fontHeight + 2);
		if (statusText.length() > 0)
		{			
			lcdDriver->setColor(statusBarTextColor);
			int textSize = ((statusText.length() * fontWidth) / 2);
			lcdDriver->printxy_abs(elementArea.x1 + (elementArea.width / 2) - textSize, elementArea.y1 + 2, statusText);
		}
	}
	lcdDriver->setColor(windowBGColor);
	lcdDriver->drawBoxFill(windowArea.x1, windowArea.y1, windowArea.x2, windowArea.y2);
	
	// Now update all children
	for (int a = 0; a < childElements.size(); a++)
	{
		// Set this windows cycle time to the minimum of the child elements
		if (childElements[a]->getUpdateCycle() < this->updateCycle)
			this->updateCycle = childElements[a]->getUpdateCycle();
		childElements[a]->update(lcdDriver);
	}
		
}

bool UIWindow::addElement(UIElement *element)
{
	// element is defined based on the window, so lets set the abs
	Rectangle newArea = element->calcSize();
	newArea.x1 += elementArea.x1;
	newArea.y1 += elementArea.y1;
	newArea.x2 += elementArea.x2;
	newArea.y2 += elementArea.y2;
	// If the element is completely off the map, we wont add it (As it wont ever be shown)
	if (newArea.x1 > elementArea.x2)
		return false;
	if (newArea.y2 > elementArea.y2)
		return false;
	element->setElementArea(newArea);
	childElements.emplace(childElements.begin(), element);
	element->forceUpdate();	
}

UIWindow::~UIWindow()
{
	for (int a = 0; a < childElements.size(); a++)
	{
		delete(childElements[a]);
	}
}