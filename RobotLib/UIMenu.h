#pragma once
#include "UIElement.h"
#include "UIFont.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>

class UIMenu : public UIElement
{
public:
	enum MenuItemType
	{
		ReturnsValue,
		PointerToPage
	};
	
	struct MenuItem
	{
		MenuItem(uint8_t itemNumber, 
			std::string itemText, 
			MenuItemType itemType, 
			int returnValue, 
			int pageLink)
		{
			this->itemNumber = itemNumber;
			this->itemText = itemText;
			this->itemType = itemType;
			this->returnValue = returnValue;
			this->pageLink = pageLink;
		}
		uint8_t itemNumber;
		std::string itemText;
		MenuItemType itemType;
		int returnValue;
		int pageLink;
	};
	
	struct MenuPage
	{		
		MenuPage()
		{
		}
		MenuPage(std::string title)
		{
			this->title = title;
			this->titleColor = DigoleLCD::WHITE;
			this->titleFont = UIFont::defaultFont;
			this->itemsFont = UIFont::defaultFont;
			itemsColor = DigoleLCD::YELLOW;
		}
		MenuPage(std::string title, 
			uint8_t titleColor, 
			UIFont::eFontName titleFont, 
			UIFont::eFontName itemsFont,
			uint8_t itemsColor)
		{
			this->title = title;
			this->titleColor = titleColor;
			this->titleFont = titleFont;
			this->itemsFont = itemsFont;
			this->itemsColor = itemsColor;
		}
		std::string title;
		uint8_t titleColor;
		UIFont::eFontName titleFont;
		UIFont::eFontName itemsFont;
		uint8_t itemsColor;
		std::vector<MenuItem> menuItems;						
	};
	
	UIMenu(RobotLib *robotLib);
	uint8_t createMenuPage(std::string title);
	uint8_t createMenuPage(std::string title,
		uint8_t titleColor,
		UIFont::eFontName titleFont,
		UIFont::eFontName itemsFont,
		uint8_t itemsColor);
	uint8_t addMenuOption(uint8_t menuPage,
		std::string itemText, 
		MenuItemType itemType, 
		int returnValue = -1, 
		int pageLink=-1);
	bool checkMenu();
	void update(DigoleLCD *lcd, RobotLib *robotLib);
		
private:
	RobotLib *robotLib;
	std::map<uint8_t, MenuPage> menuPages;		// uint - page number, returned in createMenuPage
	uint8_t pageCounter = 0, currentPage = 0, cpRow = 0;
	std::map<int, Rectangle> touchPoints;
};
