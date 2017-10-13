#include "UICompass.h"

UICompass::UICompass(DriverBase &tft, Rectangle location, float direction, tColor controlColor,
	tColor pointerColor, eUITextFont controlFont, bool showNSEW, tColor textColor) :
	UIElement(tft, location, "Compass", eElementType::NotInteractive),
	direction(direction), controlColor(controlColor), pointerColor(pointerColor),
	controlFont(controlFont), showNSEW(showNSEW), textColor(textColor)
{
}

void UICompass::Update()
{
	Compass::Draw(tft, location, direction, controlColor, pointerColor, controlFont, false, eUITextFont::None, Color::Black, Color::Black, true, Color::DarkBlue);
}