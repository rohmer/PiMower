#include "UIMenuPage.h"

UIMenuPage::UIMenuPage(Rectangle location
	, std::vector<menuItem_t> menuItems
	, std::string menuTitle)
	: UIElement(Point(location.x1, location.y1), true)
	, menuTitle(menuTitle)
	, font(UIFont::u8g_font_unifont)
	, fontColor(1)
	, useWindow(false)
	, windowUseBorder(false)
	, windowBorderColor(0)
	, windowStatusBar(false)
	, windowStatusText("")
	, windowStatusBarBGColor(0)
	, windowStatusBarTextColor(1)
	, windowBGColor(0)
{
	initMenu();
}

UIMenuPage::UIMenuPage(Rectangle location,
	std::vector<menuItem_t> menuItems
	, std::string menuTitle
	, UIFont::eFontName font
	, uint8_t fontColor
	, bool windowUseBorder
	, uint8_t windowBorderColor
	, bool windowStatusBar
	, std::string windowStatusText
	, uint8_t windowStatusBarBGColor
	, uint8_t windowStatusBarTextColor
	, uint8_t windowBGColor)
	: UIElement(Point(location.x1, location.y1), true)
	, menuTitle(menuTitle)
	, font(UIFont::u8g_font_unifont)
	, fontColor(1)
	, useWindow(true)
	, windowUseBorder(windowUseBorder)
	, windowBorderColor(windowBorderColor)
	, windowStatusBar(windowStatusBar)
	, windowStatusText(windowStatusText)
	, windowStatusBarBGColor(windowStatusBarBGColor)
	, windowStatusBarTextColor(windowStatusBarTextColor)
	, windowBGColor(windowBGColor)
{
	initMenu();
}

void UIMenuPage::initMenu()
{
	calcSize();
	// Ok at this point we have our menu real estate, lets figure how many we can show
	rowsAvailable = (elementArea.y2 - elementArea.y1) / (fontHeight + 2);			
	// Set page dirty to draw it
	pageDirty = true;
	// Set updateCycle and force an update
	setUpdateCycle(-1);
	forceUpdate();
}

Rectangle UIMenuPage::calcSize()
{
	// First set the elementArea to the maximum size
	elementArea = Rectangle(0, 0, 319, 239);
	fontHeight = UIFont::getFontHeight(font);
	fontWidth = UIFont::getFontWidth(font);
	// If we are using a window, then the chrome for the window takes up some of the page
	if (useWindow)
	{
		if (windowUseBorder)
		{
			elementArea.x1++;
			elementArea.y1++;
			elementArea.y2--;
			elementArea.x2--;
		}
		if (windowStatusBar)
		{			
			// Status bar uses the top, font.height + 2
			elementArea.y1 += (fontHeight + 2);
		}
	}
	else
	{
		// Menu title and a window (That would eat up too much real estate
		if (menuTitle.length() > 0)
		{
			elementArea.y1 += (fontHeight + 2);
		}
	}
	return elementArea;
}

void UIMenuPage::drawWindow(DigoleLCD *lcdDriver)
{
	if (windowUseBorder)	
	{
		lcdDriver->setColor(windowBorderColor);
		lcdDriver->drawBox(0, 0, 319, 239);
	}
	if (windowStatusBar)
	{
		lcdDriver->setColor(windowStatusBarBGColor);
		lcdDriver->drawBoxFill(1, 1, 318, 238);
	}
	if (windowStatusText.length() > 0)
	{
		lcdDriver->setColor(windowStatusBarTextColor);
		// Center the text
		int x = 159 - ((windowStatusText.length()*fontWidth) / 2);
		lcdDriver->printxy_abs(x, 3, windowStatusText);
	}
}

void UIMenuPage::update(DigoleLCD *lcdDriver) 
{	
	// Page doesnt need redraw
	if (!pageDirty)
		return;
	menuTargets.clear();
	lcdDriver->setFont(UIFont::getFontNum(font));
	lcdDriver->clearScreen();
	if (useWindow)
		drawWindow(lcdDriver);
	int maxY = (menuY-menuItems.size())-1;
	if (maxY > rowsAvailable)
	{
		//TODO: this could be off by one
		maxY = menuY + rowsAvailable - 1;
	}
	for (int y = 0; y <= maxY-menuY; y++)
	{		
		int adjY = menuY + y;
		lcdDriver->printxy_abs(3, elementArea.y1 + (y*fontHeight), menuItems[adjY].menuItemText);
		Rectangle rect = Rectangle(0, elementArea.y1 + (y*fontHeight), 319, elementArea.y1 + ((y + 1)*fontHeight - 1));
		menuTarget_t target;
		target.target = rect;
		target.menuItemNum = adjY;
		menuTargets.push_back(target);
			
	}
	
	// Now we have to have an up and down menu button, if needed
	if (menuItems.size() > maxY)
	{
		// Draw down button
		lcdDriver->drawBitmap(286, 206, 32, 32, downIcon);
		downButton = Rectangle(286, 206, 32, 32);
	}
	else
	{
		downButton = Rectangle(-1, -1, -1, -1);
	}
		
	if (menuY > 0)
	{
		// Draw up button
		lcdDriver->drawBitmap(286, elementArea.y1 + 2, 32, 32, upIcon);
		upButton = Rectangle(286, elementArea.y1 + 2, 32, 32);
	}
	else
	{
		upButton = Rectangle(-1, -1, -1, -1);
	}	
}
	
// Returns true if a menu item was pressed, if a up/down was pressed we will handle it here
bool UIMenuPage::pointTouches(Point pt)
{
	// We havent processed a previous click that should close this menu
	if (menuReturnValue != -1)
		return false;
	selectedItem = -1;
	if (upButton.contains(pt))
	{
		menuY--;
		if (menuY < 0)
			menuY = 0;
		return false;		
	}
	if (downButton.contains(pt))
	{
		menuY++;
		if (menuY > (menuItems.size() - 1))
			menuY = menuItems.size() - 1;
		return false;
	}
		
	for (int a=0; a<menuTargets.size(); a++)
	{
		if (menuTargets[a].target.contains(pt))
		{
			selectedItem = menuTargets[a].menuItemNum;
			menuReturnValue = menuItems[menuTargets[a].menuItemNum].returnValue != -1;
			return true;
		}
	}
	return false;
}