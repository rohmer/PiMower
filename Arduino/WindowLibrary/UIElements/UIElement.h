#pragma once
#include <vector>
#include <memory>

#include "../Utility/Rectangle.h"
#include "../Utility/Logger.h"
#include "../Driver/DriverBase.h"

#ifdef FT8XX
#include "FT8XX/UIPrimitives.h"
#endif
#ifdef RA8875
#include "RA8875/UIPrimitives.h"
#endif

enum eTouchResponse
{
	NoOp					= 0,		// Touch didnt do anything
	ControlTouched			= 1,
	BringToFront			= 2,
	ControlTouchedInactive	= 3,
	CloseControl			= 100		// The control should be closed
};

enum eElementType
{
	Button,
	CheckBox,
	RadioButton,
	RadioGroup,
	Window,
	ActiveButton,
	Page,
	Slider
};

enum eVertAlign
{
	Top,
	Middle,
	Bottom
};

struct sTouchResponse
{
	sTouchResponse(unsigned long cID, eTouchResponse tr)
	{
		controlID = cID;
		touchReponse = tr;
	}	
	sTouchResponse()
	{
		controlID = 0;
	}
	unsigned long controlID;
	eTouchResponse touchReponse;
};

class UIElement
{
public:
	UIElement(DriverBase &tft, Rectangle location, std::string elementName, eElementType elementType) :
		tft(tft)
	{
		this->childElements.reserve(10);
		this->elementID = micros();
		if (elementName == "")
			this->elementName = this->elementID;
		else
			this->elementName = elementName;
		this->location = location;
		this->elementType = elementType;
#ifdef DEBUG
		Logger::Trace("UIElement(TFT,(%d,%d,%d,%d), %s, %s)",
			location.x1, location.y1, location.x2, location.y2,
			elementName.c_str(), elementType);
#endif
	}

	UIElement(const UIElement &other) :
		tft(tft)
	{
		location.x1 = other.location.x1;
		location.y1 = other.location.y1;
		location.x2 = other.location.x2;
		location.y2 = other.location.y2;
	}
	// All inherited UI classes should call this update after they draw 
	// This puts children on top of parents
	virtual void Update()=0;
	
	eElementType GetElementType()
	{
		return elementType;
	}

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
		{
			UIElement &uie = *childElements[i];
			uie.Invalidate();
		}			
	}
	Rectangle GetLocation()
	{
		return location;
	}

	Rectangle SetLocation(Rectangle newLoc)
	{
		location = newLoc;
	}
	
	std::vector<UIElement *> GetChildElements()
	{
		return childElements;
	}
	
	
	/// <summary>
	/// If a child UI element overrides this, it must call this as well
	/// </summary>
	/// <param name="element">The element.</param>
	virtual void AddChildElement(UIElement *element)
	{
		element->parentElement = this;

		// Add the size to this
		this->location = this->location.add(element->location);
		childElements.push_back(element);

	}

	void SetParent(UIElement *element)
	{
		this->parentElement = element;
	}

	virtual sTouchResponse ProcessTouch(Point touchPoint)=0;

	std::string getElementName()
	{
		return this->elementName;
	}
	
	void UpdateChildren()
	{
		for (int i = 0; i < childElements.size(); i++)
		{
			UIElement &uie = *childElements[i];			
			uie.Update();
		}
	}

	~UIElement()
	{
	}

private:
	std::vector<UIElement *> getChildElements()
	{
		return childElements;
	}
	
protected:
	std::string elementName;

	Rectangle location;
	UIElement *parentElement;
	bool updatePending, enabled;
	uint32_t elementID;
	DriverBase &tft;
	eElementType elementType;
	
	std::vector<UIElement *> childElements;
};