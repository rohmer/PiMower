#pragma once
#include <vector>
#include "../Utility/Rectangle.h"
#include "../Utility/Logger.h"
#include "../WindowManager/Theme.h"
#include "../Driver/DriverBase.h"

enum eTouchResponse
{
	NoOp			 = 0,		// Touch didnt do anything
	ControlTouched	 = 1,
	BringToFront	 = 2,

	CloseControl	 = 100		// The control should be closed
};

struct sTouchResponse
{
	sTouchResponse(unsigned long cID, eTouchResponse tr)
	{
		controlID = cID;
		touchReponse = tr;
	}
	unsigned long controlID;
	eTouchResponse touchReponse;
};

class UIElement
{
public:
	UIElement(DriverBase &tft, Rectangle location, eThemeObjState themeState);
	virtual void Update() = 0;
	bool UpdatePending()
	{
		return updatePending;
	}
	int getElementID()
	{
		return this->elementID;
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
		updatePending = true;
		// Invalidate all children
		for (int i = 0; i < childElements.size(); i++)
			childElements[i]->Invalidate();
	}
	Rectangle GetLocation()
	{
		return location;
	}

	Rectangle SetLocation(Rectangle newLoc)
	{
		location = newLoc;
	}
	void virtual SetObjectState(eThemeObjState objState)
	{
		if (objectThemeState == objState)
			return;
		this->objectThemeState = objState;
		Invalidate();
	}

	std::vector<UIElement *> GetChildElements()
	{
		return childElements;
	}

	virtual void AddChildElement(UIElement *element)
	{
		childElements.push_back(element);
		element->parentElement = this;
	}

	void SetParent(UIElement *element)
	{
		this->parentElement = element;
	}

	virtual sTouchResponse ProcessTouch(Point touchPoint)=0;

protected:
	sThemeSettings themeSettings;

private:
	std::vector<UIElement *> getChildElements()
	{
		return childElements;
	}
	
protected:
	Theme &theme;
	eThemeObjState objectThemeState;
	Rectangle location;
	UIElement *parentElement;
	bool updatePending, enabled;
	uint32_t elementID;
	DriverBase &tft;

	std::vector<UIElement *> childElements;
};