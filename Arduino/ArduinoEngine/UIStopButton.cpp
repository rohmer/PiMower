#include "UIStopButton.h"

UIStopButton::UIStopButton(DriverBase &tft, Rectangle location) :
	UIElement(tft, location, "Stop Button", eElementType::Button)
{
	Rectangle textRec = FontHelper::GetTextRect(tft, "STOP ALL", eUITextFont::AntiAliasFont31, Point(0, 0));
	textWidth = textRec.width;
	textHeight = textRec.height;
}

void UIStopButton::Update()
{
	Button::Draw(tft, false, location.x1, location.y1, location.width, location.height,
		Color::Black, Color::Gray, eUITextFont::None, "", false, 0, 255);
	// First draw the box
	UIPrimitives::FlatPanel(tft, location.center().x - textWidth/2 - 10, location.center().y - textHeight/6 - 20, 
		textWidth + 20, textHeight, 0, Color::Red);
	//tft.drawRect(location.center().x - textWidth/2 - 10, location.center().y - textHeight/2 - 10, textWidth + 20, textHeight + 20, Color::Red, 5);
	UIPrimitives::Text(tft, Color::White, 255, location.center().x, location.center().y-25, eUITextFont::AntiAliasFont31, false, "STOP ALL");
}