#pragma once
#include "../../Options.h"
#ifdef RA8875
#include <string>
#include <map>
#include <vector>
#include "../../Utility/Color.h"
#include "../UIElement.h"
#include "../../WindowManager/Theme.h"
#include <SPI.h>
#include "../../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "Fonts.h"
#include "../../Utility/FontHelper.h"
#include "../../Utility/Rectangle.h"

class BatteryIcon : public UIElement
{
public:
	BatteryIcon(Adafruit_RA8875 &tft, Rectangle location, uint8_t pctCharged, bool charging=false);

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
#endif