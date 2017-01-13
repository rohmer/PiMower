#pragma once
#include "UIElement.h"
#include "UIFont.h"
#include <vector>
#include <string>
#include <map>
#include "UIMenuPage.h"

typedef struct
{
	std::string pageName;
	UIFont::eFontName font;
	uint8_t fontColor;
	bool windowUseBorder;
	uint8_t windowBorderColor;
	bool windowStatusBar;
	std::string windowStatusText;
	uint8_t windowStatusBarBGColor;
	uint8_t windowStatusBarTextColor;
	uint8_t windowBGColor;
	std::vector<menuItem_t> menuItems;
} menuPage_t;

class UIMenu : UIElement
{
public:
	UIMenu(Rectangle location, std::vector<menuPage_t> pages);	
	std::pair<int, int> getMenuResult();			// Returns an int from page, item
	int currentPageIndex = 0;
	Rectangle calcSize() override;
	void update(DigoleLCD *lcdDriver) override;
	bool pointTouches(Point pt) override;
	~UIMenu()
	{
	}
	
private:
	std::map<int, menuPage_t> pageData;
	std::map<int, UIMenuPage*> pages;
	int activePage = 0;	
};
