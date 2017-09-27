#include "NumericEntryRA8875.h"

#ifdef RA8875
// NumericEntry::Draw
// If x==0 then X will be set to center the control
// If y==0 then Y will be set to center the control
// The control is 250x300
Rectangle NumericEntry::Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t controlColor,
	uint16_t controlBGColor, uint16_t textColor, eUITextFont font, std::string initialValue,
	bool is3D = true, uint8_t cornerRadius = 4)
{
#ifdef DEBUG
	Logger::Trace("NumericEntry::Draw(tft,%d,%d,%d,%d,%d,%d,%s,%s,%d)",
		x, y, controlColor, controlBGColor, textColor, font, initialValue.c_str(),
		Logger::BoolToStr(is3D).c_str(), cornerRadius);
#endif
	if (x == 0)
	{
		if (tft.isLandscape())
			x = 275;		// (Width/2 == 400) -(ControlWidth/2 == 125) = 275
		else
			x = 115;		// (Width/2 == 240) -(ControlWidth/2 == 125) = 115
	}
	if (y == 0)
	{
		if (tft.isLandscape())
			y = 9;
		else
			y = 169;
	}

	// First draw control BG
	if (is3D)
		UIPrimitives::RaisedPanel(tft, x, y, 250, 462, cornerRadius, controlColor, 255);
	else
		UIPrimitives::FlatPanel(tft, x, y, 250, 462, cornerRadius, controlColor, 255);

	UpdateInput(tft, x, y, controlBGColor, textColor, font, initialValue, is3D);

	for (int i = 0; i <= 9; i++)
	{
		uint16_t keyX, keyY;
		switch (i)
		{
		case(7):
			keyX = x + 6;
			keyY = y + 60;
			break;
		case(8):
			keyX = x + 12 + 75;
			keyY = y + 60;
			break;
		case(9):
			keyX = x + 18 + 150;
			keyY = y + 60;
			break;
		case(4):
			keyX = x + 6;
			keyY = y + 60 + 75 + 6;
			break;
		case(5):
			keyX = x + 12 + 75;
			keyY = y + 60+75+ 6;
			break;
		case(6):
			keyX = x + 18 + 150;
			keyY = y + 60 + 75+ 6;
			break;
			keyY = y + 56 + 92 + 6;
		case(1):
			keyX = x + 6;
			keyY = y + 60+ 150+ 12;
			break;
		case(2):
			keyX = x + 12 + 75;
			keyY = y + 60+ 150+ 12;
			break;
		case(3):
			keyX = x + 18 + 150;
			keyY = y + 60+ 150+ 12;
			break;
		case(0):
			keyX = x + 12 + 75;
			keyY = y + 60 + 225 + 18;
		}
		std::stringstream s;
		s << i;
		UIPrimitives::FlatPanel(tft, keyX, keyY, 75, 75, 0, controlBGColor);
		uint16_t keyTWidth = FontHelper::GetTextRect(tft, s.str(), font, Point(0, 0)).width;
		UIPrimitives::Text(tft, textColor, 255, keyX + 37-keyTWidth/2, keyY + 37, font, is3D, s.str());
	}

	uint16_t keyTWidth = FontHelper::GetTextRect(tft, ".", font, Point(0, 0)).width;
	// Draw Special Keys
	UIPrimitives::FlatPanel(tft, x + 6, y + 60 + 225 + 18, 75, 75, 0, controlBGColor);
	UIPrimitives::Text(tft, textColor, 255, x + 6 + 37 - keyTWidth / 2, y + 60 + 225 + 18 + 37, font, is3D, ".");

	keyTWidth = FontHelper::GetTextRect(tft, "BKSP", font, Point(0, 0)).width;
	UIPrimitives::FlatPanel(tft, x + 18 + 150, y + 60 + 225 + 18, 75, 75, 0, controlBGColor);
	UIPrimitives::Text(tft, textColor, 255, x + 18 + 150 + 35 - keyTWidth / 2, y + 60 + 225 + 18 + 37, font, is3D, "BKSP");
	
	keyTWidth = FontHelper::GetTextRect(tft, "Close", font, Point(0, 0)).width;
	UIPrimitives::FlatPanel(tft, x + 6, y + 60 + 300 + 24, 240, 75, 0, controlBGColor);
	UIPrimitives::Text(tft, textColor, 255, x + 6 + 120 - keyTWidth / 2, y + 60 + 300 + 24 + 37, font, is3D, "Close");

	return (Rectangle(x, y, x + 250, y + 462));
}

void NumericEntry::UpdateInput(DriverBase &tft, uint16_t x, uint16_t y, uint16_t controlBGColor,
	uint16_t textColor, eUITextFont font, std::string inputValue, bool is3D)
{
	if (x == 0)
	{
		if (tft.isLandscape())
			x = 275;		// (Width/2 == 400) -(ControlWidth/2 == 125) = 275
		else
			x = 115;		// (Width/2 == 240) -(ControlWidth/2 == 125) = 115
	}
	if (y == 0)
	{
		if (tft.isLandscape())
			y = 9;
		else
			y = 169;
	}


	// Input widget is 5 down from the top and left, and the width - 10 
	if (is3D)
		UIPrimitives::SunkenPanel(tft, x + 5, y + 5, 240, 50, 0, controlBGColor, 0);
	else
		UIPrimitives::FlatPanel(tft, x + 5, y + 5, 240, 50, 0, controlBGColor, 0);

	// Now draw the text, right justified
	uint16_t textWidth = FontHelper::GetTextRect(tft, inputValue, font, Point(0, 0)).width;
	UIPrimitives::Text(tft, textColor, 255, x + 250 - 40 - textWidth, y + 35, font, is3D, inputValue);	
}

std::map<std::string, Rectangle> NumericEntry::GetKeyRects(uint16_t x, uint16_t y)
{
	std::map<std::string, Rectangle> ret;
	for (int i = 0; i <= 9; i++)
	{
		uint16_t keyX, keyY;
		switch (i)
		{
		case(7):
			keyX = x + 6;
			keyY = y + 60;
			break;
		case(8):
			keyX = x + 12 + 75;
			keyY = y + 60;
			break;
		case(9):
			keyX = x + 18 + 150;
			keyY = y + 60;
			break;
		case(4):
			keyX = x + 6;
			keyY = y + 60 + 75 + 6;
			break;
		case(5):
			keyX = x + 12 + 75;
			keyY = y + 60 + 75 + 6;
			break;
		case(6):
			keyX = x + 18 + 150;
			keyY = y + 60 + 75 + 6;
			break;
			keyY = y + 56 + 92 + 6;
		case(1):
			keyX = x + 6;
			keyY = y + 60 + 150 + 12;
			break;
		case(2):
			keyX = x + 12 + 75;
			keyY = y + 60 + 150 + 12;
			break;
		case(3):
			keyX = x + 18 + 150;
			keyY = y + 60 + 150 + 12;
			break;
		case(0):
			keyX = x + 12 + 75;
			keyY = y + 60 + 225 + 18;
		}
		std::stringstream s;
		s << i;
		ret.insert(std::make_pair<std::string, Rectangle>(s.str(), Rectangle(keyX, keyY, 75, 75)));
	}
	ret.insert(std::make_pair<std::string, Rectangle>(".", Rectangle(x + 6, y + 60 + 225 + 18, 75, 75)));
	ret.insert(std::make_pair<std::string, Rectangle>("BKSP", Rectangle(x + 18 + 150, y + 60 + 225 + 18, 75, 75)));
	ret.insert(std::make_pair<std::string, Rectangle>("CLOSE", Rectangle(x + 6, y + 60 + 300 + 24, 240, 75)));
	return (ret);
}
#endif