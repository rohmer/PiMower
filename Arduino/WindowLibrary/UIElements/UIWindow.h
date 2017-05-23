#pragma once
#include "../Options.h"

#include <vector>
#include <string>
#include "UIElement.h"
#include "../Utility/Rectangle.h"
#include "../Utility/Logger.h"
#include "ControlDisplay/Window.h"

class UIWindow : public UIElement
{
public:
	UIWindow(DriverBase &tft, Rectangle location, eUITextFont titleBarFont,
		std::string titleText = "",	bool hasTitleBar = false, bool hasCloseIcon = false, 
		bool hasChrome = false, bool isModal = false, bool is3D=true, 
		uint32_t titleBarColor= Color::GetColor(Color::Blue),
		uint32_t titleTextColor= Color::GetColor(Color::White), 
		uint32_t chromeColor= Color::GetColor(Color::White),
		uint32_t windowColor= Color::GetColor(Color::Black), uint8_t cornerRadius=5, 
		std::string elementName = "");
	void Update() override;	
	void SetWindowTitle(std::string title);
	void SetTitleBar(bool titleBar);
	void SetCloseIcon(bool closeIcon);
	void SetHasChrome(bool hasChrome);
	void SetModal(bool isModal);
	void SetCornerRadius(uint8_t cornerRadius);
	
	void AddChildElement(UIElement *element) override;
	sTouchResponse ProcessTouch(Point touchPoint) override;

private:
	std::string titleText;
	bool hasTitleBar, hasCloseIcon, hasChrome, isModal, is3D;
	uint32_t titleTextColor, chromeColor, titleBarColor, windowColor;
	uint8_t cornerRadius;
	eUITextFont titleBarFont;
	Rectangle *closeIcon=NULL;		
};
