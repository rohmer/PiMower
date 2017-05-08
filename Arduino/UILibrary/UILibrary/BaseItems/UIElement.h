#pragma once
#define USE_RA8875_TOUCH
#include <vector>
#include "../Rectangle.h"
#include "../BaseItems/Theme.h"
#include "Arduino.h"
#include "../Utility/Logger.h"
#include <SPI.h>

class UIElement
{
public:
	UIElement(Point position, bool needsUpdate, bool uiTarget, Theme *theme);
	bool ptInElement(Point pt);
	virtual void update(Adafruit_RA8875 *lcd) = 0;
	bool updateRequired()
	{
		return needsUpdate;
	}
	int getElementID()
	{
		return this->elementID;
	}
	bool isUITarget()
	{
		return uiTarget;
	}

	bool isEnabled()
	{
		return enabled;
	}

	void setEnabled(bool val)
	{
		enabled = val;
	}

	void Invalidate()
	{
		needsUpdate = true;
		// Invalidate all children
		for (int i = 0; i < childElements.size(); i++)
			childElements[i]->Invalidate();
	}

	virtual std::pair<unsigned long, int> processTouch(Point pt) {}; 			// UL is elementID
																																			// int is value (-1 if not touched)
	virtual ~UIElement()
	{
		delete touchArea;
	};

	Rectangle *touchableArea()
	{
		return touchArea;
	}

public:
	UIElement *parentElement;
	bool needsUpdate, uiTarget;
	unsigned long elementID;
	std::vector<UIElement *> getChildElements()
	{
		return childElements;
	}

	virtual void addChildElement(Point location, UIElement *element)
	{
		childElements.push_back(element);
		position = location;
		element->parentElement = this;
	}

	Rectangle getElementArea()
	{
		return elementArea;
	}

	void setElementArea(Rectangle area)
	{
		this->elementArea = area;
	}

	void setPosition(Point position)
	{
		this->position = position;
	}

	Point getPosition()
	{
		return this->position;
	}

protected:
	virtual void setTouchArea() {};

	Rectangle *touchArea;

	Theme *theme;
	Point position;
	Rectangle elementArea;
	bool enabled = true;
	uint16_t backgroundColor, borderColor, textColor, iconColor, borderSize;
	std::vector<UIElement *> childElements;	
};
