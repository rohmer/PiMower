#include "SettingsButton.h"

#ifdef useIconButton
SettingsButton::SettingsButton(DriverBase &tft, Rectangle location) :
	UIElement(tft,location,"SettingsButton",eElementType::ActiveButton)
{
	updateTime = 0;
	LOAD_ASSETS();
}

void SettingsButton::Update()
{
	IconButton::Draw(tft, false, location.x1, location.y1, location.width, location.height, SETTINGS_HANDLE, Rectangle(0, 0, 48, 48), Color::White,
		Color::DarkGray, eUITextFont::AntiAliasFont30, "Settings", true, 3, 255);
	updatePending = false;
}

sTouchResponse SettingsButton::ProcessTouch(Point pt)
{
	if (location.contains(pt))
		return sTouchResponse(this->elementID, eTouchResponse::ControlTouched);
	return sTouchResponse(this->elementID, eTouchResponse::NoOp);
}

SettingsButton::~SettingsButton()
{
}
#endif