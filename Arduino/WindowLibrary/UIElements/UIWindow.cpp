#include "UIWindow.h"

UIWindow::UIWindow(DriverBase &tft, Rectangle location, eUITextFont titleBarFont,
	std::string titleText, bool hasTitleBar, bool hasCloseIcon, bool hasChrome, bool isModal, 
	bool hasRoundCorners, bool hasShadow, uint16_t shadowColor,	uint16_t titleBarColor,	
	uint16_t titleTextColor, uint16_t chromeColor, uint16_t windowColor, uint8_t cornerRadius) :
	UIElement(tft, location)
{
	this->titleText = titleText;
	this->hasTitleBar = hasTitleBar;
	this->hasChrome = hasChrome;
	this->hasCloseIcon = hasCloseIcon;
	this->isModal = isModal;
	this->titleTextColor = titleTextColor;
	this->titleBarColor = titleBarColor;
	this->chromeColor = chromeColor;
	this->windowColor = windowColor;
	this->hasRoundCorners = hasRoundCorners;
	this->titleBarFont = titleBarFont;	
	this->shadowColor = shadowColor;
	this->shadowThickness = 4;
	this->hasShadow = hasShadow;
	this->cornerRadius = cornerRadius;
#ifdef DEBUG
	Logger::Trace("UIWindow(TFT, (%d,%d,%d,%d), %d, %s, %s, %s, %s, %s, %s, %s, %d, %d, %d, %d,%d)",location.x1, location.y1, location.x2, location.y2, (int)titleBarFont,titleText.c_str(), Logger::BoolToStr(hasTitleBar).c_str(),Logger::BoolToStr(hasCloseIcon).c_str(), Logger::BoolToStr(hasChrome).c_str(),Logger::BoolToStr(isModal).c_str(), Logger::BoolToStr(hasRoundCorners).c_str(),Logger::BoolToStr(hasShadow).c_str(), shadowColor, titleBarColor, titleTextColor, chromeColor, windowColor);
#endif
}

void UIWindow::SetWindowTitle(std::string title)
{
	this->titleText = title;
	if (titleLocation)
		delete(titleLocation);
	Invalidate();
}

void UIWindow::SetTitleBar(bool titleBar)
{
	this->hasTitleBar = titleBar;
	Invalidate();
}

void UIWindow::SetHasRoundCorners(bool RoundCorners)
{
	this->hasRoundCorners = RoundCorners;
	Invalidate();
}

void UIWindow::SetCloseIcon(bool closeIcon)
{
this->hasCloseIcon = closeIcon;
Invalidate();
}

void UIWindow::SetHasChrome(bool hasChrome)
{
	this->hasChrome = hasChrome;
	Invalidate();
}

void UIWindow::SetModal(bool isModal)
{
	this->isModal = isModal;
	Invalidate();
}

void UIWindow::drawChrome()
{
#ifdef DEBUG
	Logger::Trace("Drawing Window");
#endif

	updatePending = false;
}

void UIWindow::Update()
{
	if (!updatePending)
	{
#ifdef DEBUG
		Logger::Trace("Update not pending");
#endif
		return;
	}
	if (hasChrome)
	{
		drawChrome();
	}

	// Now draw children
	for (int i = 0; i < childElements.size(); i++)
	{
		// Invalidate children, they need to be drawn
		childElements[i]->Invalidate();
		childElements[i]->Update();
	}
}

/// <summary>
/// Adds a child element to a window.
///		For Windows it is special (Hence override), as the location is relative to the window size
/// </summary>
/// <param name="element">The element to be added</param>
void UIWindow::AddChildElement(UIElement *element)
{
	Rectangle elementLocation=element->GetLocation();
	elementLocation.x1 += location.x1;
	elementLocation.x2 += location.x2;
	elementLocation.y1 += location.y1;
	elementLocation.y2 += location.y2;
	elementLocation.update();
	element->SetLocation(elementLocation);
	childElements.push_back(element);
	element->SetParent(this);
}


sTouchResponse UIWindow::ProcessTouch(Point touchPoint)
{
	if (!location.contains(touchPoint))
	{
#ifdef DEBUG
		Logger::Trace("Touch point(%d,%d) not in this control", touchPoint.x, touchPoint.y);
#endif
		return sTouchResponse(this->elementID, eTouchResponse::NoOp);
	}

	if (!closeIcon == NULL)
	{
		// We have a close icon, did we touch it?
		if (closeIcon->contains(touchPoint))
		{
#ifdef DEBUG
			Logger::Trace("Close requested by touch");
#endif
			return sTouchResponse(this->elementID, eTouchResponse::CloseControl);
		}
	}

	// Otherwise, the window should be brought to the front
	return sTouchResponse(this->elementID, eTouchResponse::BringToFront);
}