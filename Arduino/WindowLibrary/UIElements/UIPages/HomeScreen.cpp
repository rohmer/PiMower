#include "HomeScreen.h"

HomeScreen::HomeScreen(DriverBase &tft) :
	UIElement(tft, Rectangle(0, 0, tft.width(), tft.height()), "HomeScreen", eElementType::Page)
{
	pageWindow = new UIWindow(tft, this->location, eUITextFont::None, "", false, false, false, false, false);
	this->AddChildElement(pageWindow);

	addButtons();
}

HomeScreen::~HomeScreen()
{
	delete (pageWindow);
}

void HomeScreen::addButtons()
{
	settingsButton = new SettingsButton(tft, Rectangle(535, 325, 785, 465));
	this->AddChildElement(settingsButton);
}

void HomeScreen::Update()
{
	UIElement::UpdateChildren();
	
}

sTouchResponse HomeScreen::ProcessTouch(Point pt)
{

	
}