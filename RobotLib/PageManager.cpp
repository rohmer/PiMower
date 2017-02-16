#include "PageManager.h"
#include "MainMenu.h"


PageManager::PageManager()
	: UIElement(Point(0, 0), true, true)
{
	// We start Idle
	currentPage = static_cast<UIElement *>(new IdlePage());
	pageDisplayed = IDLE;
	lastTouch = time(0);
}

void PageManager::update(DigoleLCD *lcd, RobotLib *robotLib)
{
	if (currentPage != NULL)
		currentPage->update(lcd, robotLib);
	
	if (pageDisplayed == IDLE)
		return;
	if (time(0) > (lastTouch + 60))
	{
		// Display Idle Page
		delete(currentPage);
		currentPage = new IdlePage();
		currentPage->update(lcd, robotLib);
	}
}
int PageManager::processTouch(Point pt)
{
	lastTouch = time(0);
	// first any touch on idle shows main menu
	if (pageDisplayed == IDLE)	
	{
		delete(currentPage);
		currentPage = new MainMenu();		
	}
	else
	{
		int val = currentPage->processTouch(pt);		
	}	
}
