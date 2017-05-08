#pragma once
#include "../../Options.h"
#ifdef RA8875

#include <vector>
#include <string>
#include "../UIElement.h"
#include "../../WindowManager/WindowManager.h"
#include "../../Utility/Rectangle.h"
#include "../../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "UIText.h"
#include "../../Utility/Logger.h"
#include "../../Options.h"

class UIWindow : public UIElement
{
public:
	UIWindow(DriverBase &tft, Rectangle location, Theme &theme, eThemeObjState state,
		std::string titleText = "", bool hasTitleBar = false, bool hasCloseIcon = false,
		bool hasChrome = false, bool isModal = false, bool hasRoundCorners = false);
	UIWindow(DriverBase &tft, Rectangle location, eUITextFont titleBarFont,
		std::string titleText = "",	bool hasTitleBar = false, bool hasCloseIcon = false, 
		bool hasChrome = false, bool isModal = false, bool hasRoundCorners=false, 
		bool hasShadow=true, uint16_t shadowColor=Color::DimGray, uint16_t titleBarColor=RA8875_BLUE, 
		uint16_t titleTextColor=RA8875_WHITE, uint16_t chromeColor=RA8875_WHITE, 
		uint16_t windowColor=RA8875_BLACK, uint8_t cornerRadius=5);
	void Update() override;	
	void SetWindowTitle(std::string title);
	void SetTitleBar(bool titleBar);
	void SetCloseIcon(bool closeIcon);
	void SetHasChrome(bool hasChrome);
	void SetModal(bool isModal);
	void SetHasRoundCorners(bool hasRoundCorners);
	
	void AddChildElement(UIElement *element) override;
	sTouchResponse ProcessTouch(Point touchPoint) override;

private:
	std::string titleText;
	bool hasTitleBar, hasCloseIcon, hasChrome, isModal, hasRoundCorners, hasShadow;
	uint16_t titleTextColor, chromeColor, titleBarColor, windowColor, shadowThickness, shadowColor;
	uint8_t cornerRadius;
	eUITextFont titleBarFont;
	Rectangle *closeIcon=NULL;
	Point *titleLocation=NULL;
	uint8_t getFontHeight();
	void drawChrome();		
};
#endif