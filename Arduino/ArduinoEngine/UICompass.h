#pragma once
#include <map>
#include <vector>
#include "Utility/Color.h"
#include "UIElements/UIElement.h"
#include <SPI.h>
#include "UIElements/ControlDisplay/Compass.h"


class UICompass : public UIElement
{
public:
	UICompass(DriverBase &tft, Rectangle location, float direction, tColor controlColor,
		tColor pointerColor, eUITextFont controlFont, bool showNSEW, tColor textColor);

	sTouchResponse ProcessTouch(Point touchPoint)
	{
		return sTouchResponse(this->elementID, eTouchResponse::NoOp);
	};
	void Update() override;	
	void SetDirection(float direction)
	{
		this->direction = direction;
	}

private:
	float direction;
	tColor controlColor, pointerColor, textColor;
	eUITextFont controlFont;
	bool showNSEW;
};
