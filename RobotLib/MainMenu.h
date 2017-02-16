#pragma once
#include "UIElement.h"
#include "UILabel.h"
#include "UIGraphic.h"
#include <ctime>
#include <iostream>
#include "UIMenu.h"

class MainMenu : public UIElement
{
public:
	MainMenu();
	void update(DigoleLCD *lcd, RobotLib *robotLib) override;
	int processTouch(Point pt) override;
	
private:
	UIMenu *menu = NULL;
};
