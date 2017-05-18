#include "TextEntryRA8875.h"

// Keyboard is 480x384
// Keys are 45x45, 3px space
#ifdef RA8875
Rectangle TextEntry::Draw(DriverBase &tft, eKeyboardState keyboardState, uint16_t x,
	uint16_t y, uint16_t controlColor, uint16_t controlBGColor, uint16_t textColor,
	eUITextFont font, std::string initialValue, uint8_t cornerRadius)
{
#ifdef DEBUG
	Logger::Trace("TextEntry::Draw(tft,%d,%d,%d,%d,%d,%d,%s,%d)",
		x, y, controlColor, controlBGColor, textColor, font, initialValue.c_str(),
		cornerRadius);
#endif
	if (x == 0)
	{
		if (tft.isLandscape())
			x = 160;
		else
			x = 0;
	}
	if (y == 0)
	{
		if (tft.isLandscape())
			y = 48;
		else
			y = 0;
	}

	std::string standard[4] = {
		"1234567890",
		"abcdefghij",
		"klmnopqrst",
		"uvwxyz!,.@",
	};

	// Draw Keyboard
	UIPrimitives::FlatPanel(tft, x, y, 480, 384, cornerRadius, controlColor, 255);	
	for (int ky = 0; ky < 4; ky++)
	{
		for (int kx = 0; kx < 10; kx++)
		{
			// First draw the key
			UIPrimitives::FlatPanel(tft, x + 3 + (48 * kx), y +384-6*48+(48 * ky), 45, 45, 0, controlBGColor, 0);
			std::stringstream s;
			if (keyboardState == eKeyboardState::normal)
				s << standard[ky][kx];
			uint8_t charWidth = FontHelper::GetTextRect(tft, s.str(), font, Point(0, 0)).width;
			UIPrimitives::Text(tft, textColor, 255, x + 25 + (48 * kx) - charWidth / 2,
				y + 384 - 6 * 48 + (48 * ky)+22, font, false, s.str());
		}
	}

	// All keyboards share the last 2 rows
	// 5th row 
	UIPrimitives::FlatPanel(tft, x + 3, y + 287, 94, 45, 0, controlBGColor);
	uint8_t charWidth = FontHelper::GetTextRect(tft, "Shift", font, Point(0, 0)).width;
	UIPrimitives::Text(tft, textColor, 255, x + 47 - charWidth / 2, y + 310, font, false, "Shift");
	UIPrimitives::FlatPanel(tft, x + 99, y + 287, 94, 45, 0, controlBGColor);
	charWidth = FontHelper::GetTextRect(tft, "Symbol", font, Point(0, 0)).width;
	UIPrimitives::Text(tft, textColor, 255, x + 143 - charWidth / 2, y + 307, font, false, "Symbol");
	UIPrimitives::FlatPanel(tft, x + 195, y + 287, 94, 45, 0, controlBGColor);
	charWidth = FontHelper::GetTextRect(tft, "Space", font, Point(0, 0)).width;
	UIPrimitives::Text(tft, textColor, 255, x + 239- charWidth / 2, y + 308, font, false, "Space");
	UIPrimitives::FlatPanel(tft, x + 291, y + 287, 94, 45, 0, controlBGColor);
	charWidth = FontHelper::GetTextRect(tft, "Delete", font, Point(0, 0)).width;
	UIPrimitives::Text(tft, textColor, 255, x + 337 - charWidth / 2, y + 310, font, false, "Delete");
	UIPrimitives::FlatPanel(tft, x + 388, y + 287, 94, 45, 0, controlBGColor);
	charWidth = FontHelper::GetTextRect(tft, "Clear", font, Point(0, 0)).width;
	UIPrimitives::Text(tft, textColor, 255, x + 430 - charWidth / 2, y + 311, font, false, "Clear");

	// 6th row
	UIPrimitives::FlatPanel(tft, x + 3, y+335, 237, 45, 0, controlBGColor);
	charWidth = FontHelper::GetTextRect(tft, "Cancel", font, Point(0, 0)).width;
	UIPrimitives::Text(tft, textColor, 255, x + 157 - charWidth, y+355, font, false, "Cancel");
	UIPrimitives::FlatPanel(tft, x + 243, y+335, 237, 45, 0, controlBGColor);
	charWidth = FontHelper::GetTextRect(tft, "Continue", font, Point(0, 0)).width;
	UIPrimitives::Text(tft, textColor, 255, x + 411 - charWidth, y+355, font, false, "Continue");

	UpdateInput(tft, x, y, controlBGColor, textColor, font, initialValue);
}

void TextEntry::UpdateInput(DriverBase &tft, uint16_t x, uint16_t y, uint16_t controlBGColor,
	uint16_t textColor, eUITextFont font, std::string inputValue)
{
	// First draw window
	UIPrimitives::FlatPanel(tft, x + 3, y + 13, 474, 73, 0, controlBGColor);

	// Ok, now figure out what we can display
	uint8_t strPtr = 0;
	while (FontHelper::GetTextRect(tft, inputValue.substr(strPtr, inputValue.size() - strPtr), font, Point(0, 0)).width > 468)
		strPtr++;
	uint16_t strWidth = FontHelper::GetTextRect(tft, inputValue.substr(strPtr, inputValue.size() - strPtr), font, Point(0, 0)).width;

	UIPrimitives::Text(tft, textColor, 255, x + 240 - strWidth / 2, y + 50, font, false,
		inputValue.substr(strPtr, inputValue.size() - strPtr));
}
#endif