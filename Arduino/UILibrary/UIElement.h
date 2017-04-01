#pragma once
#include <RA8875/RA8875.h>
#include "Point.h"
#include "Rectangle.h"

enum eTextAlignment
{
	textLeft,
	textRight
};

class UIElement
{
	UIElement(Point position, bool needsUpdate, bool uiTarget, RA8875 *ra8875);	
	bool ptInElement(Point pt);	
	virtual void update();
	bool updateRequired()
	{
		return needsUpdate;
	}
	bool isUITarget()
	{
		return uiTarget;
	}
	virtual int processTouch(Point pt) {} 		// -1 if not touching a control, otherwise the control
	void setElementID(int elementID)
	{
		this->elementID = elementID;
	}
	int getElementID()
	{
		return this->elementID;
	}

protected:
	virtual void setArea() {}
	int elementID;	
	bool needsUpdate, uiTarget;
	Point position;
	Rectangle elementArea;
	RA8875 *ra8875;
	
private:
	
};