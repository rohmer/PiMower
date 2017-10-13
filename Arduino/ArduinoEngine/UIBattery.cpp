#include "UIBattery.h"

UIBattery::UIBattery(DriverBase &tft, Rectangle location, uint8_t pctCharged,
	std::vector<tColor> barColors, bool showPct, tColor borderColor, tColor bgColor,
	eUITextFont pctFont, tColor pctTextColor,bool rightAlignment) :
	UIElement(tft, location, "Compass", eElementType::NotInteractive),
	pctCharged(pctCharged),barColors(barColors),showPct(showPct),
	borderColor(borderColor),pctFont(pctFont),pctTextColor(pctTextColor),
	rightAlignment(rightAlignment), bgColor(bgColor)
{
}

void UIBattery::Update()
{
	BatteryIcon::Draw(tft, location, pctCharged, barColors, showPct, borderColor, bgColor, pctFont,
		pctTextColor, rightAlignment);
	Logger::Trace("Pct Charged: %d", pctCharged);
}