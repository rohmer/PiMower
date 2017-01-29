#pragma once
#include "UIElement.h"
#include "UIFont.h"
#include "UIKeyboardIcons.h"
#include <string>
#include <array>
#include <vector>

class UIInput : public UIElement
{
public:
	UIInput();
		
	void update(DigoleLCD *lcd, RobotLib *robotLib) override;
	
private:
	struct keyTarget_s
	{
		keyTarget_s(Rectangle area, char character)
		{
			this->area = area;
			this->character = character;
		}
		Rectangle area;
		char character;
	};
	
enum eKeyboardShown
	{
		alpha,
		symbol1,
		symbol2
	};
	// Special Keys: C=Change Page, P=Space, B=BackSpace, S Shift
	std::string alphaPort[5] = { "abcdef","ghijkl", "mnopqr","stuvwx", "SyPzCB" };
	
	bool redraw = false;
	
	eKeyboardShown currentKeyboard = eKeyboardShown::alpha;
	bool shiftedKeys = false;
	void drawPortrait(DigoleLCD *lcd, RobotLib *robotLib);
	std::vector<keyTarget_s> touchTargets;
};