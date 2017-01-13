#pragma once
#include "UIElement.h"
#include "UIFont.h"
#include "NavigationIcons.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <utility>

// Displays a window with a text box and a keyboard
class UITextEntry : UIElement
{
	UITextEntry(Rectangle location, std::string inputValue);
	Rectangle calcSize() override;
	void update(DigoleLCD *lcdDriver) override;
	bool pointTouches(Point pt) override;
	
private:
	enum eKeyboardShown
	{
		Normal,
		SpecialChars
	};
	
	std::string keys = "0123456789abcdefghijklmnopqrstuvwxyz";
	std::string specialChars = "-=`~!@#$%^&*()_+<>,.;:'\"";
	
	void drawLandscape(DigoleLCD *lcd);
	void drawPortrait(DigoleLCD *lcd);
	
	struct key
	{
		Rectangle buttonRect;
		std::string value;	
	};
	
	std::map<std::string, Rectangle> keyTargets;
	
	bool shiftedKeys = false;
	eKeyboardShown keyboardShown = eKeyboardShown::Normal;
	std::vector<key> keyRowDisplayed;
	std::string returnVal;
	bool isDirty = true;
};
