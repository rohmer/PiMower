#include "MainMenu.h"

MainMenu::MainMenu()
	: UIElement(Point(0, 0), false, false)
{
}

void MainMenu::update(DigoleLCD *lcd, RobotLib *robotLib)
{
	if (menu == NULL)
	{
		menu = new UIMenu(robotLib);
		int page1 = menu->createMenuPage("Main Menu");
		int page2 = menu->createMenuPage("Mower Status");
		int page3 = menu->createMenuPage("Mower Setup");
		menu->addMenuOption(page1, "Mower Status", UIMenu::PointerToPage, -1, page2);
		menu->addMenuOption(page1, "Mower Setup", UIMenu::PointerToPage, -1, page3);
	}
	menu->update(lcd, robotLib);
}

int MainMenu::processTouch(Point pt)
{
	int retval = menu->processTouch(pt);
	return retval;
}