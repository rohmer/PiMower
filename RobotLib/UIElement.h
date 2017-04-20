#pragma once
#include <vector>
#include <chrono>
#include "Rectangle.h"
#include "../RobotController/SensorLib/DigoleLCD.h"

enum eTextAlignment
{
	textLeft,
	textRight
};

class UIElement
{
	public:
		UIElement(Point position, bool needsUpdate, bool uiTarget);
		bool ptInElement(Point pt);
		virtual void update(DigoleLCD *lcd, RobotLib *robotLib)
		{
			robotLib->Log("Calling base");
		};
		bool updateRequired()
		{
			return needsUpdate;
		}
		void setElementID(int elementID)
		{
			this->elementID = elementID;
		}
		int getElementID()
		{
			return this->elementID;
		}
		bool isUITarget()
		{
			return uiTarget;
		}
		virtual int processTouch(Point pt) {} 		// -1 if not touching a control, otherwise the control
													// value;
	protected:
		virtual void setArea(){};
		int elementID;
		bool needsUpdate, uiTarget;
		Point position;
		Rectangle elementArea;
};
