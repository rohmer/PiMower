#pragma once
#include <map>
#include <vector>
#include "Utility/Color.h"
#include "UIElements/UIElement.h"
#include "UIElements/ControlDisplay/Button.h"

class UIStopButton : public UIElement
{
public:
	UIStopButton(DriverBase &tft, Rectangle location);
	sTouchResponse ProcessTouch(Point touchPoint)
	{
		return sTouchResponse(this->elementID, eTouchResponse::ControlTouched);
	};
	void Update() override;

private:
	uint16_t textWidth, textHeight;
};