#include "WindowManager.h"
WindowManager *WindowManager::s_instance=0;
UIWindow *WindowManager::baseWindow;
std::map<unsigned long, UIElement *> WindowManager::elementMap;

WindowManager::WindowManager(const uint8_t CS, const uint8_t RST, 
	const uint8_t MOSI, const uint8_t SCLK, const uint8_t MISO,
	RA8875sizes lcdSize)
{
#ifdef TEENSY3X
	lcd = new Adafruit_RA8875(CS, RST, MOSI, SCLK, MISO);
#else
	lcd = new Adafruit_RA8875(CS, RST);
#endif
	int width = 800, height = 480;
	if (lcdSize == RA8875sizes::RA8875_480x272)
	{
		width = 480;
		height = 272;
	}
	lcd->touchEnable(true);
	lcd->begin(lcdSize);
	setDefaultTheme();
	createBaseWindow();
	Logger::Trace("Creating WindowManager", "WindowManager()");

}

void WindowManager::createBaseWindow()
{	
#ifndef DEBUG
	Logger::initLogger(Logger::WARN);
#endif
		
	baseWindow = new UIWindow(displaySize, theme);
	// The base window does not have a parent
	baseWindow->parentElement = NULL;	
	Logger::Trace("WindowManager Init");
}

WindowManager::~WindowManager()
{
	for (unsigned int i = 0; i < childElements.size(); i++)
	{
		delete(childElements[i]);
	}
	delete theme;
}

int WindowManager::GetThemeAttribute(eThemeObjType objType, eThemeObjState objState,
	eThemeObjAttribute objAttribute)
{
	return theme->GetThemeAttribute(objType, objState, objAttribute);
}

void WindowManager::SetThemeAttribute(eThemeObjType objType, eThemeObjState objState,
	eThemeObjAttribute objAttribute, uint16_t value)
{
	return theme->SetThemeAttribute(objType, objState, objAttribute, value);
}

void WindowManager::setDefaultTheme()
{
	if (theme == NULL)
		theme = new Theme();
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::bgColor, Color::Color32To565(16185078));
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::borderColor, Color::Color32To565(12961221));
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::textColor, Color::Color32To565(4539717));
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::iconColor, Color::Color32To565(7829367));
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::textScale, 1);
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::textInterlineSpacing, 0);
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::textSpacing, 0);
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::defaultState, eThemeObjAttribute::textFont, eUITextFont::AileronRegular12);

	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::activeState, eThemeObjAttribute::bgColor, Color::Color32To565(32767));
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::activeState, eThemeObjAttribute::borderColor, Color::Color32To565(16127));
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::activeState, eThemeObjAttribute::textColor, Color::Color32To565(16777215));
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::activeState, eThemeObjAttribute::iconColor, Color::Color32To565(16777215));
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::activeState, eThemeObjAttribute::textScale, 1);
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::activeState, eThemeObjAttribute::textInterlineSpacing, 0);
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::activeState, eThemeObjAttribute::textSpacing, 0);
	SetThemeAttribute(eThemeObjType::clickable, eThemeObjState::activeState, eThemeObjAttribute::textFont, eUITextFont::AileronRegular12);

	SetThemeAttribute(eThemeObjType::highlight, eThemeObjState::defaultState, eThemeObjAttribute::bgColor, Color::Color32To565(16775824));
	SetThemeAttribute(eThemeObjType::highlight, eThemeObjState::defaultState, eThemeObjAttribute::borderColor, Color::Color32To565(14341470));
	SetThemeAttribute(eThemeObjType::highlight, eThemeObjState::defaultState, eThemeObjAttribute::textColor, Color::Color32To565(7829024));
	SetThemeAttribute(eThemeObjType::highlight, eThemeObjState::defaultState, eThemeObjAttribute::iconColor, Color::Color32To565(7829024));
	SetThemeAttribute(eThemeObjType::highlight, eThemeObjState::defaultState, eThemeObjAttribute::textScale, 1);
	SetThemeAttribute(eThemeObjType::highlight, eThemeObjState::defaultState, eThemeObjAttribute::textInterlineSpacing, 0);
	SetThemeAttribute(eThemeObjType::highlight, eThemeObjState::defaultState, eThemeObjAttribute::textSpacing, 0);
	SetThemeAttribute(eThemeObjType::highlight, eThemeObjState::defaultState, eThemeObjAttribute::textFont, eUITextFont::AileronRegular12);

	SetThemeAttribute(eThemeObjType::error, eThemeObjState::defaultState, eThemeObjAttribute::bgColor, Color::Color32To565(16637919));
	SetThemeAttribute(eThemeObjType::error, eThemeObjState::defaultState, eThemeObjAttribute::borderColor, Color::Color32To565(15837337));
	SetThemeAttribute(eThemeObjType::error, eThemeObjState::defaultState, eThemeObjAttribute::textColor, Color::Color32To565(6242111));
	SetThemeAttribute(eThemeObjType::error, eThemeObjState::defaultState, eThemeObjAttribute::iconColor, Color::Color32To565(13369344));
	SetThemeAttribute(eThemeObjType::error, eThemeObjState::defaultState, eThemeObjAttribute::textScale, 1);
	SetThemeAttribute(eThemeObjType::error, eThemeObjState::defaultState, eThemeObjAttribute::textInterlineSpacing, 0);
	SetThemeAttribute(eThemeObjType::error, eThemeObjState::defaultState, eThemeObjAttribute::textSpacing, 0);
	SetThemeAttribute(eThemeObjType::error, eThemeObjState::defaultState, eThemeObjAttribute::textFont, eUITextFont::AileronRegular12);

	SetThemeAttribute(eThemeObjType::window, eThemeObjState::defaultState, eThemeObjAttribute::windowBGColor, Color::Color32To565(16777215));
	SetThemeAttribute(eThemeObjType::window, eThemeObjState::defaultState, eThemeObjAttribute::windowHeadingBGColor, Color::Color32To565(32767));
	SetThemeAttribute(eThemeObjType::window, eThemeObjState::defaultState, eThemeObjAttribute::windowHeadingTextColor, Color::Color32To565(16127));
	SetThemeAttribute(eThemeObjType::window, eThemeObjState::defaultState, eThemeObjAttribute::windowChromeColor, Color::Color32To565(6242111));
	SetThemeAttribute(eThemeObjType::window, eThemeObjState::defaultState, eThemeObjAttribute::windowFrameColor, Color::Color32To565(16777215));
	SetThemeAttribute(eThemeObjType::window, eThemeObjState::defaultState, eThemeObjAttribute::textScale, 2);
	SetThemeAttribute(eThemeObjType::window, eThemeObjState::defaultState, eThemeObjAttribute::textFont, eUITextFont::AileronRegular12);

	SetThemeAttribute(eThemeObjType::modalWindow, eThemeObjState::defaultState, eThemeObjAttribute::windowBGColor, Color::Color32To565(11184810));
	SetThemeAttribute(eThemeObjType::modalWindow, eThemeObjState::defaultState, eThemeObjAttribute::windowHeadingBGColor, Color::Color32To565(32767));
	SetThemeAttribute(eThemeObjType::modalWindow, eThemeObjState::defaultState, eThemeObjAttribute::windowHeadingTextColor, Color::Color32To565(16127));
	SetThemeAttribute(eThemeObjType::modalWindow, eThemeObjState::defaultState, eThemeObjAttribute::windowChromeColor, Color::Color32To565(0));
	SetThemeAttribute(eThemeObjType::modalWindow, eThemeObjState::defaultState, eThemeObjAttribute::windowFrameColor, Color::Color32To565(16777215));
	SetThemeAttribute(eThemeObjType::modalWindow, eThemeObjState::defaultState, eThemeObjAttribute::textScale, 2);
	SetThemeAttribute(eThemeObjType::modalWindow, eThemeObjState::defaultState, eThemeObjAttribute::textFont, eUITextFont::AileronRegular12);

	SetThemeAttribute(eThemeObjType::dropShadow, eThemeObjState::defaultState, eThemeObjAttribute::shadowColor, Color::Color32To565(11184810));
	SetThemeAttribute(eThemeObjType::dropShadow, eThemeObjState::defaultState, eThemeObjAttribute::shadowOpacity, 30);
	SetThemeAttribute(eThemeObjType::dropShadow, eThemeObjState::defaultState, eThemeObjAttribute::shadowThickness, 5);
	SetThemeAttribute(eThemeObjType::dropShadow, eThemeObjState::defaultState, eThemeObjAttribute::shadowInterpolated, 1);
}

std::vector<UIElement *> WindowManager::getChildUIElements(UIElement *element)
{
	std::vector<UIElement *> retVal;
	std::vector<UIElement *> children = element->getChildElements();
	for (unsigned int i = 0; i < children.size(); i++)
	{
		std::vector<UIElement *> cChildren = getChildUIElements(children[i]);
		for (int i = 0; i < cChildren.size(); i++)
			retVal.push_back(cChildren[i]);
	}
	return retVal;
}

void WindowManager::setActiveWindow(unsigned long windowID)
{
	// Get all descendants from the baseWindow (Which is everything)
	std::vector<UIElement *> uiElements = getChildUIElements(baseWindow);
	for (unsigned int i = 0; i < uiElements.size(); i++)
	{
		UIWindow * uiw = (UIWindow *)(uiElements[i]);
		if (uiw)
		{
			// This is a window, lets check the ID
			if (uiw->elementID == windowID)
			{
				if (uiw->isActive)
				{
					// its not, set active
					uiw->isActive = true;
					// Invalidate for redraw
					uiw->Invalidate();
				}
			}
			else
			{
				// This window WAS active, now needs invalidation
				if (uiw->isActive)
				{
					uiw->isActive = false;
					uiw->Invalidate();
				}
			}
		}
	}
}

// Returns touch point if the screen is being touched, -1,-1 if it is not
Point WindowManager::GetTouch()
{
	if (!lcd->touched())
	{
		return Point(-1, -1);
	}
	uint16_t x, y;
	lcd->touchRead(&x, &y);
	return Point(x, y);
}

void WindowManager::DeleteElement(unsigned long elementID)
{
	UIElement *elementToDelete = elementMap[elementID];
	if (!elementToDelete)
	{
		Logger::Crit("Attempt to delete non registered element", "WindowManager");
		return;
	}
	// Now find what this item occluded
	std::vector<UIElement *> occludedElements = ElementOccludes(elementToDelete);
	std::vector<UIElement *> elements = getChildUIElements(elementToDelete);
	// Add the original element to the delete list, not just the children of it
	elements.push_back(elementToDelete);
	// We delete them in reverse order, to delete children then parents
	for (int i = elements.size(); i >= 0; i--)
	{
		elementMap.erase(elements[i]->getElementID());
		delete(elements[i]);				
	}

	for (int i = 0; i < occludedElements.size(); i++)
	{
		// Invalidate the elements so that they can be redrawn on next update
		occludedElements[i]->Invalidate();
	}	
}

// Returns a list of UIElements occluded by the Element element
std::vector<UIElement *> WindowManager::ElementOccludes(UIElement *element)
{
	std::vector<UIElement *> occludedElements;
	std::vector<unsigned long> elementsChecked;
	for (unsigned int i = 0; i < elementMap.size(); i++)
	{
		if (element->getElementArea().occludes(elementMap[i]->getElementArea()))
		{
			if (std::find(elementsChecked.begin(), 
				elementsChecked.end(), 
				elementMap[i]->elementID)!=elementsChecked.end())

			{
				// First add all our children to the checked list
				for (int j = 0; j < elementMap[i]->getChildElements().size(); j++)
				{
					if (std::find(elementsChecked.begin(),
						elementsChecked.end(),
						elementMap[j]->elementID) != elementsChecked.end())
					{
						elementsChecked.push_back(elementMap[j]->elementID);
					}
				}
				// Lets work our way up and find the highest parent that occludes and isnt the 
				// window manager base window
				UIElement *currentPtr = elementMap[i];
				while (currentPtr->parentElement->parentElement != NULL &&	// Check that the parent isnt the base window
					element->getElementArea().occludes(currentPtr->parentElement->getElementArea()))
				{
					currentPtr = currentPtr->parentElement;
					// Add all those children if they dont exist
					for (int j = 0; j < currentPtr->getChildElements().size(); j++)
					{
						if (std::find(elementsChecked.begin(),
							elementsChecked.end(),
							currentPtr->elementID) != elementsChecked.end())
						{
							elementsChecked.push_back(currentPtr->elementID);
						}
					}				
				}
				occludedElements.push_back(currentPtr);
			}
		}
	}
	return (occludedElements);
}