#pragma once
#include "UIElement.h"
#include "UIFont.h"
#include "NavigationIcons.h"
#include <vector>
#include <string>
#include <map>
#include <utility>

typedef struct
{
	int pagePtr;						// Page menu item will display (Sub menu)
	std::string menuItemText;
	bool returnValue;					// if !0 this will end the menu and return to the main page
										// returning this value
} menuItem_t;

typedef struct
{
	Rectangle target;
	int menuItemNum;
} menuTarget_t;

class UIMenuPage : UIElement
{
	public:
		UIMenuPage(Rectangle location
		,std::vector<menuItem_t> menuItems
			, std::string menuTitle);
		UIMenuPage(Rectangle location
		, std::vector<menuItem_t> menuItems
			, std::string menuTitle
			, UIFont::eFontName font
			, uint8_t fontColor);
		UIMenuPage(Rectangle location
			, std::vector<menuItem_t> menuItems
			, std::string menuTitle
			, UIFont::eFontName font
			, uint8_t fontColor
			, bool windowUseBorder
			, uint8_t windowBorderColor
			, bool windowStatusBar
			, std::string windowStatusText
			, uint8_t windowStatusBarBGColor
			, uint8_t windowStatusBarTextColor
			, uint8_t windowBGColor);
		Rectangle calcSize() override;
		void update(DigoleLCD *lcdDriver) override;
		bool pointTouches(Point pt) override;
		
		~UIMenuPage() 
		{
		}
		
		int menuReturnValue=-1;
		int selectedItem;
		
	private:
		void initMenu();	
		void drawWindow(DigoleLCD *lcdDriver);
		std::vector<menuItem_t> menuItems;		
		std::vector<menuTarget_t> menuTargets;
		std::string menuTitle;
		UIFont::eFontName font;
		uint8_t fontColor;
		bool useWindow, windowUseBorder, windowBorderColor, windowStatusBar;
		std::string windowStatusText;
		uint8_t windowStatusBarBGColor, windowStatusBarTextColor, windowBGColor;					
		uint8_t fontHeight, fontWidth;
		int menuY = 1;
		int rowsAvailable;
		bool pageDirty;
		Rectangle upButton, downButton;
};