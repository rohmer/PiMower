#pragma once
#include "UIElement.h"
#include "IdlePage.h"

class PageManager : public UIElement
{
public:
	enum ePageDisplayed
	{
		IDLE,
		MAINMENU
	};
	PageManager();	
	int processTouch(Point pt) override;
	void update(DigoleLCD *lcd, RobotLib *robotLib) override;
	
private:
	UIElement *currentPage=NULL;
	ePageDisplayed pageDisplayed;
	std::string returnStr;
	time_t lastTouch;
};