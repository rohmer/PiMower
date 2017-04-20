#include "UIMenu.h"

UIMenu::UIMenu(RobotLib *robotLib)
	: UIElement(Point(0, 0), false, true)
{
	this->robotLib = robotLib;
	pageCounter = 0;
}

uint8_t UIMenu::createMenuPage(std::string title)
{
	MenuPage page(title);
	menuPages[pageCounter] = page;
	pageCounter++;
	return (pageCounter - 1);
}

uint8_t UIMenu::createMenuPage(std::string title,
	uint8_t titleColor,
	UIFont::eFontName titleFont,
	UIFont::eFontName itemsFont,
	uint8_t itemsColor)
{
	MenuPage page(title, titleColor, titleFont, itemsFont, itemsColor);
	menuPages[pageCounter] = page;
	pageCounter++;

	return (pageCounter - 1);
}

uint8_t UIMenu::addMenuOption(uint8_t menuPage,
	std::string itemText,
	MenuItemType itemType,
	int returnValue,
	int pageLink)
{
	std::map<uint8_t, MenuPage>::iterator it;
	it = menuPages.find(menuPage);
	if (it == menuPages.end())
	{
		std::stringstream ss;
		ss << "Page: " << menuPage << " isnt defined yet.  Define the page before adding menu options. This option will *NOT* be added";
		robotLib->LogError(ss.str());
		return -1;
	}
	int ctr = it->second.menuItems.size();

	if (itemType == MenuItemType::PointerToPage && pageLink == -1)
	{
		std::stringstream ss;
		ss << "This item (" << ctr << ") is defined as a PointerToPage and pageLink==-1, this will create a broken link.";
		robotLib->LogWarn(ss.str());
	}
	if (itemType == MenuItemType::ReturnsValue && returnValue == -1)
	{
		std::stringstream ss;
		ss << "This item (" << ctr << ") is defined as a ReturnsValue and returnValue==-1, this is the default, did you mean this?";
		robotLib->LogWarn(ss.str());
	}
	MenuItem menuItem(ctr, itemText, itemType, returnValue, pageLink);
	it->second.menuItems.emplace_back(menuItem);
}

// Checks to make sure all links work and go to proper pages, and return values are set
bool UIMenu::checkMenu()
{
	std::map<uint8_t, MenuPage>::iterator it, it2;
	for (it = menuPages.begin(); it != menuPages.end(); it++)
	{
		for (int a = 0; a < it->second.menuItems.size(); a++)
		{
			if (it->second.menuItems[a].itemType == MenuItemType::PointerToPage)
			{
				it2 = menuPages.find(it->second.menuItems[a].pageLink);
				if (it2 == menuPages.end())
				{
					std::stringstream ss;
					ss << "Page #" << it->first << ", item #" << a << " has a link to Page #" << it->second.menuItems[a].pageLink << ".  That page doesnt exist.";
					robotLib->LogError(ss.str());
					return false;
				}
			}
			else
			{
				if (it->second.menuItems[a].returnValue == -1)
				{
					std::stringstream ss;
					ss << "Page #" << it->first << ", item #" << a << " is defined as return and has the default -1 returnValue";
					robotLib->LogError(ss.str());
					return false;
				}
			}
		}
	}
	return true;
}

void UIMenu::update(DigoleLCD *lcd, RobotLib *robotLib)
{
	lcd->clearScreen();
	lcd->setColor(menuPages[currentPage].titleColor);
	lcd->setFont(menuPages[currentPage].titleFont);
	int width = 319;
	int height = 239;
	if (lcd->getOrientation() == DigoleLCD::Portrait)
	{
		width = 239;
		height = 319;
	}
	lcd->printxy(0, 0, menuPages[currentPage].title);
	int yCtr = UIFont::getFontHeight(menuPages[currentPage].titleFont) + 2;
	lcd->drawLine(0, yCtr, width, yCtr);
	yCtr++;
	lcd->drawLine(0, yCtr, width, yCtr);
	// Top row will be the scroll up line
	int row = (yCtr / UIFont::getFontHeight(menuPages[currentPage].itemsFont)) + 2;
	int totalRowsAvail = (height / UIFont::getFontHeight(menuPages[currentPage].itemsFont)) - row - 2;
	touchPoints.clear();
	if (menuPages[currentPage].menuItems.size() > totalRowsAvail)
	{
		if (cpRow > 0)
		{
			// Add scroll up
			lcd->printxy(0, row - 1, "Scroll Up");
			touchPoints[-1] = Rectangle(0,
				(row - 1)*UIFont::getFontHeight(menuPages[currentPage].itemsFont),
				width,
				row*UIFont::getFontHeight(menuPages[currentPage].itemsFont));
		}
		if (cpRow + menuPages[currentPage].menuItems.size() > totalRowsAvail)
		{
			// Add scroll down
			lcd->printxy(0, totalRowsAvail + 2 + row, "Scroll Down");
			touchPoints[-1] = Rectangle(0,
				(totalRowsAvail + 2 + row)*UIFont::getFontHeight(menuPages[currentPage].itemsFont),
				width,
				height);
		}
	}
	lcd->setFont(menuPages[currentPage].itemsFont);
	lcd->setColor(menuPages[currentPage].itemsColor);
	for (int a = 0; a < menuPages[currentPage].menuItems.size(); a++)
	{
		lcd->printxy(2, row + a, menuPages[currentPage].menuItems[a].itemText);
		touchPoints[menuPages[currentPage].menuItems[a].itemNumber] = Rectangle(0,
			(row + a)*UIFont::getFontHeight(menuPages[currentPage].itemsFont),
			width,
			(row + a + 1)*UIFont::getFontHeight(menuPages[currentPage].itemsFont));
	}
}