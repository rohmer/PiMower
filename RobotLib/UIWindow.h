#pragma once	
#include "UIElement.h"
#include "UIFont.h"
#include <vector>
#include <string>

class UIWindow : UIElement
{
	public:
		UIWindow(Rectangle location, std::string statusText);
		UIWindow(Rectangle location, bool useBorder, uint8_t borderColor, bool statusBar, 
			std::string statusText, uint8_t statusBarBGColor, uint8_t statusBarTextColor,
			UIFont::eFontName font, uint8_t windowBGColor);
		~UIWindow();
		void update(DigoleLCD *lcdDriver) override;
		Rectangle calcSize() override;
		void resize(Rectangle newSize);
		bool addElement(UIElement *element);
	
	private:
		std::string statusText;
		bool border, statusBar;		
		uint8_t borderColor, statusBarBGColor, statusBarTextColor, windowBGColor;
		UIFont::eFontName font;
		uint8_t fontHeight, fontWidth;
		std::vector<UIElement *> childElements;		
		// This is the drawable area of the window for elements
		// elementArea - border and statusBar, all the child elements will
		// be relative to this
		Rectangle windowArea;
	
		Rectangle getWindowArea();
};