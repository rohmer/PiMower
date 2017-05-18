#include "../Options.h"
#include "BatteryIcon.h"

BatteryIcon::BatteryIcon(DriverBase &tft, Rectangle location, uint8_t pctCharged, bool charging)
	: UIElement(tft, location)
{
	this->pctCharged = pctCharged;
	this->charging = charging;
}

void BatteryIcon::SetPct(uint8_t pct)
{
	if (pct == pctCharged)
		return;
	this->pctCharged = pct;
	updatePending = true;
}

void BatteryIcon::SetCharging(bool isCharging)
{
	if (isCharging == charging)
		return;
	this->charging = isCharging;
	updatePending = true;
}

void BatteryIcon::SetChargeBars(uint8_t chargeBars)
{
	if (this->chargeBars == chargeBars)
		return;
	this->chargeBars = chargeBars;
	updatePending = true;
}

void BatteryIcon::Update()
{
	if (!updatePending)
	{
#ifdef DEBUG
		Logger::Trace("No update necessary");
#endif
	}

	Rectangle positiveChargeRect(location.x2 - location.width / 10, location.center().y - location.width / 8, location.x2 - 1, location.center().y + location.width / 8);	
	tft.fillRoundRect(positiveChargeRect.x1, positiveChargeRect.y1,
		positiveChargeRect.width, positiveChargeRect.height, location.height/50,
		Color::GetColor(Color::White));
	uint16_t batteryBodyWidth = location.width - positiveChargeRect.width+(location.height/50*2);
	Rectangle batteryBodyRect(location.x1 + 1, location.y1 + 1, batteryBodyWidth, location.height - 2);
	for (int i = 0; i < location.height/50; i++)
		tft.drawRoundRect(batteryBodyRect.x1 + i, batteryBodyRect.y1 + i,
			batteryBodyRect.width - 2 * i, batteryBodyRect.height - 2 * i,
			location.height / 50,
			Color::GetColor(Color::White));

	Rectangle batterySliceRect(0, 0, (batteryBodyRect.width / chargeBars)-location.width/50, batteryBodyRect.height - (location.height / 50));
	uint8_t chargeBarsToShow;
	if (pctCharged > 0)
		chargeBarsToShow = chargeBars*(100 / pctCharged);
	else
		chargeBarsToShow = 0;

	uint8_t briteRedThresh = chargeBars*0.1;
	uint8_t orangeThresh = chargeBars*.2;
	uint8_t yellowThresh = chargeBars*.8;
	uint8_t darkGreenThresh = chargeBars*.9;
	
	uint16_t brightRed, orange, yellow, darkGreen, lightGreen;
#ifdef FT8XX
	brightRed = Color::Crimson;
	orange = Color::OrangeRed;
	yellow = Color::Yellow;
	darkGreen = Color::DarkGreen;
	lightGreen = Color::LightGreen;
#endif
#ifdef RA8875
	brightRed = Color::BrightRed;
	orange = Color::LightOrange;
	yellow = Color::Yellow;
	darkGreen = Color::Green;
	lightGreen = Color::LightGreen;
#endif

	for (int i = 1; i <= chargeBarsToShow; i++)
	{
		uint32_t color = lightGreen;
		if (i < briteRedThresh)
			color = brightRed;
		else
			if (i < orangeThresh)
				color = orange;
			else
				if (i < yellowThresh)
					color = yellow;
				else
					if (i < darkGreenThresh)
						color = darkGreen;
			uint16_t startX = (batterySliceRect.width)*(i - 1) + location.width / 45;
			uint16_t width = batterySliceRect.width - location.width / 50;
#ifdef FT8XX
			tft.fillRect(startX, batteryBodyRect.y1 + location.width / 50,width,batteryBodyRect.height - location.width / 25, color);
#endif
#ifdef RA8875
			tft.fillRect(startX, batteryBodyRect.y1 + location.width / 50, width, batteryBodyRect.height - location.width / 25, Color::Color32To565(color));
#endif
	}
	updatePending = false;
}

sTouchResponse BatteryIcon::ProcessTouch(Point pt)
{

}
