#pragma once
#include "../Options.h"

#include <vector>
#include <string>
#include "UIElement.h"
#include "../WindowManager/WindowManager.h"
#include "../Utility/Rectangle.h"
#ifdef RA8875 
#include "../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "RA8875/Fonts.h"
#endif
#ifdef FT8XX
#include "../External/GD3/GD3.h"
#include "FT8XX/Fonts.h"
#endif
#include "../Utility/Logger.h"
#include "../Options.h"
#include "../Utility/FontHelper.h"
#include "../Utility/Color.h"

class UIWindow : public UIElement
{
public:
	UIWindow(DriverBase &tft, Rectangle location, eUITextFont titleBarFont,
		std::string titleText = "",	bool hasTitleBar = false, bool hasCloseIcon = false, 
		bool hasChrome = false, bool isModal = false, bool hasRoundCorners=false, 
		bool hasShadow=true, uint16_t shadowColor=Color::GetColor(Color::DimGray), 
		uint16_t titleBarColor= Color::GetColor(Color::Blue),
		uint16_t titleTextColor= Color::GetColor(Color::White), 
		uint16_t chromeColor= Color::GetColor(Color::White),
		uint16_t windowColor= Color::GetColor(Color::Black), uint8_t cornerRadius=5);
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
	void drawChrome();		
};
