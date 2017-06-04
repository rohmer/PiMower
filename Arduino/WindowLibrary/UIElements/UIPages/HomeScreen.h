#pragma once

#include "../../Options.h"
#include "../UIWindow.h"
#include "SettingsButton.h"

/// <summary>
/// The home screen for the PiMower
/// A screen is an element that contains the window and all the elements as children
/// </summary>
/// <seealso cref="UIElement" />
class HomeScreen : public UIElement
{
public:
	HomeScreen(DriverBase &tft);
	~HomeScreen();
	
	void Update() override;
	sTouchResponse ProcessTouch(Point pt) override;

private:
	void addButtons();

	UIWindow *pageWindow;
	SettingsButton *settingsButton;
};
