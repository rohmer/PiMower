#pragma once

#include "Options.h"
#include "PageBase.h"
#include "UIElements/UIButton.h"
#include "WindowManager/WindowManager.h"
#include "UICompass.h"
#include "UIBattery.h"
#include "UIMower.h"
#include "UIStopButton.h"

class MainPage : public PageBase
{
public:
	MainPage(DriverBase &tft, UIData *data);
	void Update() override;
	
	sTouchResponse ProcessTouch(Point touchPoint) override;
	
private:
	bool itemsGenerated = false;
	void generatePageItems();
	UICompass *compass;
	UIButton *navButton;
	UIButton *battButton;
	UIButton *statusButton;
	UIBattery *batteryIcon;	
	UIMower *mowerIcon;
	UIStopButton *stopText;
};