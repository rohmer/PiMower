#include "UIWindow.h"

UIWindow::UIWindow(DriverBase &tft, Rectangle location, Theme &theme,
	eThemeObjState state, std::string titleText, bool hasTitleBar, bool hasCloseIcon,
	bool hasChrome, bool isModal, bool hasRoundCorners) :
	UIElement(tft, location, state)
{
	this->titleText = titleText;
	this->hasTitleBar = hasTitleBar;
	this->hasChrome = hasChrome;
	this->hasCloseIcon = hasCloseIcon;
	this->isModal = isModal;
	this->theme = theme;
	this->hasRoundCorners = false;

#ifdef DEBUG
	Logger::Trace("UIWindow(TFT, (%d,%d,%d,%d), THEME, %d, %s, %s, %s, %s, %s, %s)",
		location.x1, location.y1, location.x2, location.y2,
		state, titleText.c_str(), Logger::BoolToStr(hasTitleBar).c_str(),
		Logger::BoolToStr(hasCloseIcon).c_str(), Logger::BoolToStr(hasChrome).c_str(),
		Logger::BoolToStr(isModal).c_str(), Logger::BoolToStr(hasRoundCorners).c_str());
#endif
	eThemeObjType winType = eThemeObjType::window;
	if (isModal)
		winType = eThemeObjType::modalWindow;
	titleTextColor = theme.GetThemeAttribute(winType, state, eThemeObjAttribute::windowHeadingTextColor);
	chromeColor= theme.GetThemeAttribute(winType, state, eThemeObjAttribute::windowChromeColor); 
	titleBarColor= theme.GetThemeAttribute(winType, state, eThemeObjAttribute::windowHeadingBGColor); 
	windowColor = theme.GetThemeAttribute(winType, state, eThemeObjAttribute::windowBGColor);
	titleBarFont = (eUITextFont)theme.GetThemeAttribute(winType, state, eThemeObjAttribute::textFont);
	shadowColor = theme.GetThemeAttribute(winType, state, eThemeObjAttribute::shadowColor);
	shadowThickness = theme.GetThemeAttribute(winType, state, eThemeObjAttribute::shadowThickness);
}

UIWindow::UIWindow(DriverBase &tft, Rectangle location, eUITextFont titleBarFont,
	std::string titleText, bool hasTitleBar, bool hasCloseIcon, bool hasChrome, bool isModal, 
	bool hasRoundCorners, bool hasShadow, uint16_t shadowColor,	uint16_t titleBarColor,	
	uint16_t titleTextColor, uint16_t chromeColor, uint16_t windowColor, uint8_t cornerRadius) :
	UIElement(tft, location, eThemeObjState::defaultState)
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
	location.update();
	if (hasShadow)
	{
		if (hasRoundCorners)
		{
			tft.fillRoundRect(location.x1 + shadowThickness, location.y1 + shadowThickness,
				location.width, location.height, cornerRadius, shadowColor);
		}
		else
		{
			tft.fillRect(location.x1 + shadowThickness, location.y1 + shadowThickness,
				location.width, location.height, shadowColor);
		}
	}
	
	// Draw windowbg
	if (hasRoundCorners)
	{
		tft.fillRoundRect(location.x1 + 2, location.y1 + 2, 
			location.width-cornerRadius, location.height - cornerRadius, cornerRadius, windowBGColor);
	}
	else
	{
		tft.fillRect(location.x1 + 2, location.y1 + 2, location.width-4, location.height-4, windowBGColor);
	}

	if (hasTitleBar)
	{

		uint8_t height = FontHelper::GetTextRect(tft, "X", titleBarFont, Point(0, 0)).height;

		if (!hasRoundCorners)
			tft.fillRect(location.x1+1, location.y1+1, location.width-2, height+1, titleBarColor);
		else
		{
			tft.fillRoundRect(location.x1+1, location.y1+1, location.width-2, 
				height+cornerRadius+1, cornerRadius, titleBarColor);
		}

		if (hasCloseIcon)
		{
			if (closeIcon==NULL)
			{				
				closeIcon = new Rectangle(location.x2 - height-2, location.y1+3, location.x2-2 , location.y1 + height+3);
			}
			// Now draw a square with an X in it		
			tft.drawRect(closeIcon->x1, closeIcon->y1, height, height, chromeColor);
			tft.drawLine(closeIcon->x1, closeIcon->y1, closeIcon->x2, closeIcon->y2, chromeColor);
			tft.drawLine(closeIcon->x2, closeIcon->y1, closeIcon->x1, closeIcon->y2, chromeColor);
		}

		// TODO: Get width, and height and center it in the titleRect.
		if (titleLocation==NULL)
		{
			Rectangle r = FontHelper::GetTextRect(tft, titleText, titleBarFont, Point(0, 0));			
			uint16_t startX = location.center.x-(abs(r.x2-r.x1)/4);
			titleLocation = new Point(startX, location.center.y);
		}
		tft.textWrite(titleLocation->x, titleLocation->y, titleBarFont, titleTextColor,0, titleText);

		// Finally draw the border
		if (hasRoundCorners)
		{
			tft.drawRoundRect(location.x1, location.y1, location.width, location.height, cornerRadius, windowChromeColor);
		}
		else
		{
			tft.drawRect(location.x1, location.y1, location.width, location.height, windowChromeColor);
		}

	}

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