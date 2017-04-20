#include "UIWindow.h"

UIWindow::UIWindow(Rectangle location, Theme *theme) :
	UIElement(Point(location.x1, location.y1), false, true, theme)
{
	elementArea = location;
	this->hasCloseIcon = false;
	this->hasChrome = false;
	this->hasTitleBar = false;	
}

UIWindow::UIWindow(Rectangle location, std::string titleText, Theme *theme,
	bool hasTitleBar, bool hasCloseIcon, bool hasChrome, bool isModal) :
	UIElement(Point(location.x1, location.y1), false, true, theme)
{
	this->titleText = titleText;
	this->hasTitleBar = hasTitleBar;
	this->hasCloseIcon = hasCloseIcon;
	this->hasChrome = hasChrome;
	this->isModal = isModal;
	elementArea = location;
	debugPrint("Creating UI Window", "UIWindow()");
}

UIWindow::UIWindow(Rectangle location, std::string titleText, Theme *theme,
	bool hasTitleBar, bool hasCloseIcon, bool hasChrome, bool isModal,
	uint16_t titleBarColor, uint16_t titleTextColor, uint16_t chromeColor,
	uint16_t windowColor) :
	UIElement(Point(location.x1, location.y1), false, true, theme)
{
	this->titleText = titleText;
	this->hasTitleBar = hasTitleBar;
	this->hasCloseIcon = hasCloseIcon;
	this->titleBarColor = titleBarColor;
	this->titleTextColor = titleTextColor;
	this->chromeColor = chromeColor;
	this->windowColor = windowColor;
	this->hasChrome = hasChrome;
	elementArea = location;
	debugPrint("Creating UI Window", "UIWindow()");
}

void UIWindow::setTouchArea()
{
	touchArea = new Rectangle(elementArea.x1, elementArea.y1, elementArea.x2, elementArea.y2);
}

void UIWindow::setDefaults()
{
	sThemeSettings themeSettings;
	if (isModal)
	{
		themeSettings = theme->LoadTheme(eThemeObjType::modalWindow, eThemeObjState::defaultState);
	}
	else
	{
		eThemeObjState state;
		if (isActive)
			state = eThemeObjState::activeState;
		else
			state = eThemeObjState::defaultState;
		themeSettings = theme->LoadTheme(eThemeObjType::window, state);
	}
	titleBarColor = themeSettings.windowHeadingBGColor;
	titleTextColor = themeSettings.windowHeadingTextColor;
	windowColor = themeSettings.windowBGColor;
	chromeColor = themeSettings.borderColor;
	titleBarFont = themeSettings.textFont;
	hasRoundCorners = true;
	if (themeSettings.cornerType == eCornerType::Square)
	{
		hasRoundCorners = false;
	}
	elementArea = location;
}

void UIWindow::addElement(UIElement *element)
{
	childElements.push_back(element);
	element->Invalidate();
}

void UIWindow::drawChrome(RA8875 *lcd)
{
	// Draw Chrome

	// draw window border
	if (!hasRoundCorners)
	{
		lcd->fillRect(elementArea.x1, elementArea.y1, elementArea.x2, elementArea.y2, windowBGColor);
		lcd->drawRect(elementArea.x1, elementArea.y1, elementArea.x2, elementArea.y2, windowChromeColor);
	}
	else
	{
		lcd->fillRoundRect(elementArea.x1, elementArea.y1, elementArea.x2, elementArea.y2, 4, windowBGColor);
		lcd->drawRoundRect(elementArea.x1, elementArea.y1, elementArea.x2, elementArea.y2, 4, windowChromeColor);
	}
	if (hasCloseIcon)
	{
		if (!closeIcon)
		{
			Rectangle textRect = UIText::GetFontRect("X", titleBarFont);
			textRect.update();
			// Close Rectangle is a square based on the size of the text in Y
			unsigned int closeSize = (abs(textRect.x2 - textRect.x1));
			closeIcon = new Rectangle(elementArea.x2 - 2 - closeSize, elementArea.y1 + 2, elementArea.x2 - 2, elementArea.y1 + 2 + closeSize);
		}
		// Now draw a square with an X in it
		lcd->setColor(chromeColor, titleBarColor);
		lcd->drawRect(closeIcon->x1, closeIcon->y1, closeIcon->x2, closeIcon->y2, chromeColor);
		lcd->drawLine(closeIcon->x1, closeIcon->y1, closeIcon->x2, closeIcon->y2, chromeColor);
		lcd->drawLine(closeIcon->x2, closeIcon->y1, closeIcon->x1, closeIcon->y2, chromeColor);
	}
	if (hasTitleBar)
	{
		// Draw Title Bar Background
		Rectangle textRect = UIText::GetFontRect(titleText, titleBarFont);
		textRect.update();
		if(!hasRoundCorners)
			lcd->fillRect(elementArea.x1, elementArea.y1, elementArea.x2, elementArea.y1 + textRect.height + 4, titleBarColor);
		else
			lcd->fillRoundRect(elementArea.x1, elementArea.y1, elementArea.x2, elementArea.y1 + textRect.height + 4, 4, titleBarColor);

		// Draw Title Bar Text
		int startX = (abs(elementArea.x2 - elementArea.x1) / 2) - (abs(textRect.x2 - textRect.x1) / 2);
		FontHelper::setLCDFont(lcd, titleBarFont);
		lcd->setTextColor(titleTextColor);
		lcd->setCursor(startX, elementArea.y1 + 2, false);
		lcd->write(titleText.c_str());
	}
}

void UIWindow::update(RA8875 *lcd)
{
	if (hasChrome && needsUpdate)
	{
		setDefaults();
		drawChrome(lcd);
	}
	for (unsigned int i = 0; i < childElements.size(); i++)
	{
		if (childElements[i]->needsUpdate)
			childElements[i]->update(lcd);
	}
}

UIWindow::~UIWindow()
{
	for (unsigned int i = 0; i < childElements.size(); i++)
	{
		delete(childElements[i]);
	}
	if (closeIcon)
	{
		delete(closeIcon);
	}
}

void UIWindow::addChildElement(Point location, UIElement *element)
{
	// For a window its a bit different, we transcribe the location based on the window location
	unsigned int childWidth = abs(element->getElementArea().x2 - element->getElementArea().x1);
	unsigned int childHeight = abs(element->getElementArea().y2 - element->getElementArea().y1);
	// Set the relative position
	element->setPosition(Point(element->getPosition().x + this->position.x, element->getPosition().x + this->position.y));

	// Set the relative element Area
	element->setElementArea(Rectangle(element->getPosition().x, element->getPosition().y,
		element->getPosition().x + childWidth, element->getPosition().y + childHeight));
	UIElement::addChildElement(element->getPosition(), element);
	WindowManager::instance()->RegisterElement(element->elementID, element);
}

// Returns:
//	-1 non-touch 
//	0 touch but not close
//  Nothing if closed (As this will get deleted)
std::pair<unsigned long, int> UIWindow::processTouch(Point pt)
{
	// We didnt touch this.
	if (!elementArea.contains(pt))
		return (std::make_pair(this->elementID, -1));

	// We touched somewhere in here, so make it active if it wasnt, and invalidate
	if (!isActive)
	{
		isActive = true;
		this->Invalidate();
	}
	// Finally did we click on the close window button
	if (hasCloseIcon)
	{
		// We did, request the Window Mananger Kill this
		if (closeIcon->contains(pt))
			WindowManager::instance()->DeleteElement(this->elementID);
	}

	return std::make_pair(this->elementID, 0);
}