#include "UIElement.h"
UIElement::UIElement(DriverBase &tft, Rectangle location, eThemeObjState themeState) :	
	tft(tft)
{
	this->elementID = micros();
	this->objectThemeState = themeState;
	updatePending = true;
	location.update();
	this->location = location;
	Logger::Trace("UIElement((%d,%d,%d,%d)) created", location.x1, location.y1,
		location.x2,location.y2);
}
