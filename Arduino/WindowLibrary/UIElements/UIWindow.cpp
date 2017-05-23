#include "UIWindow.h"

UIWindow::UIWindow(DriverBase &tft, Rectangle location, eUITextFont titleBarFont,
	std::string titleText = "", bool hasTitleBar = false, bool hasCloseIcon = false,
	bool hasChrome = false, bool isModal = false, bool is3D = true,
	uint32_t titleBarColor = Color::GetColor(Color::Blue),
	uint32_t titleTextColor = Color::GetColor(Color::White),
	uint32_t chromeColor = Color::GetColor(Color::White),
	uint32_t windowColor = Color::GetColor(Color::Black), uint8_t cornerRadius = 5,
	std::string elementName = "")
	: UIElement(tft, location, elementName, eElementType::Window)
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
	this->titleBarFont = titleBarFont;	
	this->cornerRadius = cornerRadius;
	this->is3D = is3D;
#ifdef DEBUG
	Logger::Trace("UIWindow(TFT, (%d,%d,%d,%d), %s,%s,%s,%s,%s,%d,%d,%d,%d",
		location.x1, location.y1, location.x2, location.y2, (int)titleBarFont,titleText.c_str(), 
		Logger::BoolToStr(hasTitleBar).c_str(),Logger::BoolToStr(hasCloseIcon).c_str(), 
		Logger::BoolToStr(hasChrome).c_str(),Logger::BoolToStr(isModal).c_str(), 
		titleBarColor, titleTextColor, chromeColor, windowColor);
#endif
}

void UIWindow::SetWindowTitle(std::string title)
{
	this->titleText = title;
	Invalidate();
}

void UIWindow::SetTitleBar(bool titleBar)
{
	this->hasTitleBar = titleBar;
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

void UIWindow::Update()
{
	if (!updatePending)
	{
#ifdef DEBUG
		Logger::Trace("Update not pending");
#endif
		return;
	}
	Window::Draw(tft, location.x1, location.y1, location.width, location.height, titleBarColor,
		titleTextColor, chromeColor, chromeColor, windowColor, titleText, titleBarFont, hasChrome,
		hasTitleBar, hasCloseIcon, true, 4, 255);
	UIElement::Update();
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

	if (!closeIcon == NULL && hasCloseIcon)
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