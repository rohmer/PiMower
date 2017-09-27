#pragma once

#include "../../Options.h"
#include "../UIElement.h"

class ScreenSaver : public UIElement
{
public:
	ScreenSaver(DriverBase &tft);
	void Update() override;
	sTouchResponse ProcessTouch(Point touchPoint) override;

private:
	void draw();

	uint32_t updateTime = 0;
};