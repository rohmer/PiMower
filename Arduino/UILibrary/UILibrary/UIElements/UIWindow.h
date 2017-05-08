#pragma once
#include <vector>
#include <string>
#include "../BaseItems/UIElement.h"
#include "../BaseItems/WindowManager.h"
#include "../Rectangle.h"
#include "../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "Fonts.h"
#include "UIText.h"
#include "../Utility/Logger.h"

class UIWindow : public UIElement
{
public:
	UIWindow(Rectangle location, Theme *theme);
	UIWindow(Rectangle location, std::string titleText, Theme *theme, bool hasTitleBar = true,
		bool hasCloseIcon = true, bool hasChrome = true, bool isModal = false);
	UIWindow(Rectangle location, std::string titleText, Theme *theme, bool hasTitleBar,
		bool hasCloseIcon, bool hasChrome, bool isModal, uint16_t titleBarColor,
		uint16_t titleTextColor, uint16_t chromeColor, uint16_t windowColor);

	~UIWindow();                          // Deletes all the childElements

	void addElement(UIElement *uiElement);

	void update(Adafruit_RA8875 *lcd) override;

	void setTouchArea() override;

	bool isActive = true;			// On drawing the main window is active

	void addChildElement(Point location, UIElement *element) override;

	std::pair<unsigned long, int> processTouch(Point pt) override;

private:
	uint16_t titleBarColor;
	uint16_t titleTextColor;
	uint16_t windowColor;
	uint16_t chromeColor;

	Rectangle *closeIcon;

	eUITextFont titleBarFont;

	bool hasTitleBar, hasCloseIcon, hasChrome, isModal, hasRoundCorners;
	std::string titleText;
	Rectangle location;
	void setDefaults();
	void drawChrome(Adafruit_RA8875 *lcd);	
};
