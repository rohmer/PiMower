#pragma once
#define USE_RA8875_TOUCH
#include <vector>
#include <utility>
#include "../Rectangle.h"
#include "Theme.h"
#include "Arduino.h"
#include <SPI.h>

class RA8875;

class UIElement
{
	public:
		UIElement(Point position, bool needsUpdate, bool uiTarget, Theme *theme);
		bool ptInElement(Point pt);
		virtual void update(RA8875 *lcd)
		{
		};
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
			enabled=val;
		}

		void Invalidate()
	  {
	    	needsUpdate=true;
	  }

		virtual std::pair<unsigned long, int> processTouch(Point pt); 			// UL is elementID
																																				// int is value (-1 if not touched)
    virtual ~UIElement()
		{
			delete touchArea;
		};

		Rectangle *touchableArea()
		{
			return touchArea;
		}

	protected:
		virtual void setTouchArea(){};

		Rectangle *touchArea;

		Theme *theme;
		unsigned long elementID;
		bool needsUpdate, uiTarget;
		Point position;
		Rectangle elementArea;
		bool enabled=true;
		uint16_t backgroundColor, borderColor, textColor, iconColor, borderSize;
		std::vector<UIElement *> childElements;
};
