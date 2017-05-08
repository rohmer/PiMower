#pragma once
#include "../Options.h"
#include <string>
#include <map>
#include <vector>
#include "../Utility/Color.h"
#include "UIElement.h"
#include "../WindowManager/Theme.h"
#include <SPI.h>
#ifdef RA8875 
#include "../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "RA8875/Fonts.h"
#endif
#ifdef FT8XX
#include "../External/GD3/GD3.h"
#include "FT8XX/Fonts.h"
#endif
#include "../Utility/FontHelper.h"
#include "../Utility/Rectangle.h"

class BatteryIcon : public UIElement
{
public:
	BatteryIcon(DriverBase &tft, Rectangle location, uint8_t pctCharged, bool charging=false);

	void SetPct(uint8_t pct);
	void SetCharging(bool isCharging);
	void Update() override;
	void SetChargeBars(uint8_t chargeBars);

	sTouchResponse ProcessTouch(Point pt);

private:
	uint8_t pctCharged;
	bool charging = false;
	uint8_t chargeBars = 6;

};
