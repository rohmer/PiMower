#pragma once

#include "../../Options.h"

#ifdef useIconButton
#include "../ControlDisplay/IconButton.h"
#include "Icons.h"

class SettingsButton : public UIElement
{
public:
	SettingsButton(DriverBase &tft, Rectangle location);
	void Update() override;
	sTouchResponse ProcessTouch(Point pt) override;

	~SettingsButton();

private:
	uint32_t updateTime = 0;
	uint8_t gearIcon = 1;	
};

#endif