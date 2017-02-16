#include <iostream>
#include "../RobotLib.h"
#include "../../RobotController/SensorLib/DigoleLCD.h"
#include "../UIFont.h"
#include "../ScreenManager.h"
#include "../UILabel.h"
#include "../UIButton.h"
#include "../UIMenu.h"
#include "../UIToggle.h"
#include "../UIRadioGroup.h"
#include "../UIInput.h"
#include "img256.h"
#include "../PageManager.h"
using namespace std;

int main(int argc, char *argv[])
{
	RobotLib *robotLib = new RobotLib();
	DigoleLCD *lcd = new DigoleLCD(robotLib, 0x27);	
	//lcd->drawBitmap256(0, 0, 160, 108, img_256);
    //sleep(50);
	
	ScreenManager *screenManager = new ScreenManager(robotLib,lcd);
	PageManager *pageManager = new PageManager();
	screenManager->addElement(pageManager);
	/*UIMenu *uiMenu = new UIMenu(robotLib);
	int pg1 = uiMenu->createMenuPage("Page 1");	
	int pg2 =  uiMenu->createMenuPage("Page 2");
	int pg3 =  uiMenu->createMenuPage("Page 2");
	int pg4 =  uiMenu->createMenuPage("Page 2");
	uiMenu->addMenuOption(pg1, "Item 1", UIMenu::MenuItemType::PointerToPage, -1, pg2);
	uiMenu->addMenuOption(pg1, "Item 2", UIMenu::MenuItemType::ReturnsValue, 2, -1);
	uiMenu->addMenuOption(pg1, "Item 3", UIMenu::MenuItemType::ReturnsValue, 3, -1);
	uiMenu->addMenuOption(pg1, "Item 4", UIMenu::MenuItemType::ReturnsValue, 4, -1);
	uiMenu->addMenuOption(pg1, "Item 5", UIMenu::MenuItemType::ReturnsValue, -5, -1);
	screenManager->addElement(uiMenu);
	*/
	/*UIToggle *uit = new UIToggle(Point(10, 10), "Toggle On",DigoleLCD::LIGHT_RED, DigoleLCD::WHITE,UIFont::defaultFont,true, eTextAlignment::textRight);
	screenManager->addElement(uit);
	
	UIRadioGroup *uirg = new UIRadioGroup(Point(10, 50), DigoleLCD::LIGHT_BLUE, DigoleLCD::WHITE, UIFont::defaultFont, UIRadioGroup::GroupAlignment::Vertical,eTextAlignment::textRight);
	uirg->addRadioItem("Yes", 0, true);
	uirg->addRadioItem("No", 1, false);
	uirg->addRadioItem("Maybe", 2, false);
	uirg->addRadioItem("4", 3, false);
	screenManager->addElement(uirg);
	
	*/
	UIInput *uii = new UIInput();
	screenManager->addElement(uii);
	
	screenManager->start();
	while (true)
	{
		
	}
 	return 0;
}