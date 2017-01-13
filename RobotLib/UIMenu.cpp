#include "UIMenu.h"

UIMenu::UIMenu(Rectangle location, std::vector<menuPage_t> pages) 
	: UIElement(Point(location.x1, location.y1), true)
{
	// Initalize the pages
	for (int a = 0; a < pages.size(); a++)
	{		
		std::vector<menuItem_t> menuItems;
		for (int b = 0; b < pages[a].menuItems.size(); b++)
		{
			menuItem_t menuItem;
			menuItem.menuItemText = pages[a].menuItems[b].menuItemText;
			menuItem.pagePtr = pages[a].menuItems[b].pagePtr;
			menuItems.push_back(menuItem);		
		}
		
		pageData.emplace(a, pages[a]);		
		
			new UIMenuPage(elementArea,
				menuItems,
				pages[a].pageName,
				pages[a].font,
				pages[a].fontColor,
				pages[a].windowUseBorder,
				pages[a].windowBorderColor,
				pages[a].windowStatusBar,
				pages[a].windowStatusText,
				pages[a].windowStatusBarBGColor,
				pages[a].windowStatusBarTextColor,
				pages[a].windowBGColor);
		
	}
	setUpdateCycle(-1);
	forceUpdate();		
}

void UIMenu::update(DigoleLCD *lcdDriver)
{
	if (pages[activePage] == NULL)
	{
		// We havent created a new page
		pages[activePage] = new UIMenuPage(elementArea,
			pageData[activePage].menuItems,
			pageData[activePage].pageName,
			pageData[activePage].font,
			pageData[activePage].fontColor,
			pageData[activePage].windowUseBorder,
			pageData[activePage].windowBorderColor,
			pageData[activePage].windowStatusBar,
			pageData[activePage].windowStatusText,
			pageData[activePage].windowStatusBarBGColor,
			pageData[activePage].windowStatusBarTextColor,
			pageData[activePage].windowBGColor);			
	}
	
	pages[activePage]->update(lcdDriver);		
}

bool UIMenu::pointTouches(Point pt)
{
	if (pages[activePage]->pointTouches(pt))
	{
		// We have done something with the page, this could be
		//	A) Display a different page: pages[activePage]->selectedItem != -1
		//  B) We exit out of the menu system with a return value from pages[activePage]->menuReturnValue != -1
		if (pages[activePage]->selectedItem != -1)
		{
			if (pageData[activePage].menuItems[pages[activePage]->selectedItem].pagePtr)
			{
				activePage = pages[activePage]->selectedItem;
				return true;
			}
		}
		if (pageData[activePage].menuItems[pages[activePage]->selectedItem].returnValue != -1)
		{
			
		}
		
	}
}

Rectangle UIMenu::calcSize()
{
	return Rectangle(0, 0, 320, 240);
}