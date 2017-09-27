#include "NumericEntryFT8XX.h"
#ifdef FT8XX
// NumericEntry::Draw
// If x==0 then X will be set to center the control
// If y==0 then Y will be set to center the control
// The control is 250x300
Rectangle NumericEntry::Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t controlColor,
	uint16_t controlBGColor, uint16_t textColor, eUITextFont font, std::string initialValue,
	bool is3D, uint8_t cornerRadius, uint8_t alpha, bool singleDecimal)
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
			y = 78;
		else
			y = 238;
	}

	if (is3D)
		UIPrimitives::SunkenPanel(tft, x, y, 253, 323, cornerRadius, controlColor, alpha);
	else
		UIPrimitives::FlatPanel(tft, x, y, 253, 323, cornerRadius, controlColor, alpha);

	UpdateInput(tft,x,y,controlBGColor,textColor,font,initialValue,is3D);

	// Now time to draw the keys
	DrawKeys(tft, x, y, controlColor, textColor, font, is3D, true, singleDecimal);
	return (Rectangle(x, y, x + 250, y + 462));
}

void NumericEntry::DrawKeys(DriverBase &tft, uint16_t x, uint16_t y, uint16_t controlColor,
	uint16_t textColor, eUITextFont font, bool is3D = true, bool periodActive = true,
	bool singleDecimal = true)
{
	// The keys are in this arrangement
	// 123
	// 456
	// 789
	// .0B
	// C/E
	//
	// Where B=Backspace, C=Cancel, E=Enter
	for (int i = 0; i <= 13; i++)
	{
		std::string keyText;
		uint16_t xKey, yKey;
		switch (i)
		{
		case (1):
			xKey = x + 5;
			yKey = y + 58;
			keyText = "1";
			break;
		case(2):
			xKey = x + 88;
			yKey = y + 58;
			keyText = "2";
			break;
		case(3):
			xKey = x + 171;
			yKey = y + 58;
			keyText = "3";
			break;
		case(4):
			xKey = x + 5;
			yKey = y + 111;
			keyText = "4";
			break;
		case(5):
			xKey = x + 88;
			yKey = y + 111;
			keyText = "5";
			break;
		case(6):
			xKey = x + 171;
			yKey = y + 111;
			keyText = "6";
			break;
		case(7):
			xKey = x + 5;
			yKey = y + 164;
			keyText = "7";
			break;
		case(8):
			xKey = x + 88;
			yKey = y + 164;
			keyText = "8";
			break;
		case(9):
			xKey = x + 171;
			yKey = y + 164;
			keyText = "9";
			break;
		case(0):
			xKey = x + 88;
			yKey = y + 217;
			keyText = "0";
			break;
		case(10):
			xKey = x + 5;
			yKey = y + 217;
			keyText = ".";
			break;
		case(11):
			xKey = x + 171;
			yKey = y + 217;
			keyText = "DEL";
			break;

		case(12):
			xKey = x + 5;
			yKey = y + 270;
			keyText = "CANCEL";
			break;
		case(13):
			xKey = x + 130;
			yKey = y + 270;
			keyText = "ENTER";
			break;
		}
		Rectangle keyRect;
		if (i < 12)
		{
			if (is3D)
				keyRect = UIPrimitives::RaisedPanel(tft, xKey, yKey, 78, 50, 0, controlColor, 255);
			else
				keyRect = UIPrimitives::FlatPanel(tft, xKey, yKey, 78, 50, 0, controlColor, 255);
		}
		else
		{
			if (is3D)
				keyRect = UIPrimitives::RaisedPanel(tft, xKey, yKey, 120, 50, 0, controlColor, 255);
			else
				keyRect = UIPrimitives::FlatPanel(tft, xKey, yKey, 120, 50, 0, controlColor, 255);
		}

		Rectangle fontRect = FontHelper::GetTextRect(tft, keyText, font, Point(0, 0));
		if (i < 11)
			UIPrimitives::Text(tft, textColor, 255, keyRect.center().x, keyRect.center().y-fontRect.height/2, font, is3D, keyText);
		else
		{
			fontRect = FontHelper::GetTextRect(tft, keyText, font-1, Point(0, 0));
			UIPrimitives::Text(tft, textColor, 255, keyRect.center().x, keyRect.center().y-fontRect.height/2, font - 1, is3D, keyText);

		}
	}


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
		{
			y = 9;
		}
		else
		{
			y = 169;
		}
	}


	// Input widget is 5 down from the top and left, and the width - 10 
	if (is3D)
		UIPrimitives::SunkenPanel(tft, x + 5, y + 5, 240, 50, 0, controlBGColor, 255);
	else
		UIPrimitives::FlatPanel(tft, x + 5, y + 5, 240, 50, 0, controlBGColor, 255);

	Rectangle rect = FontHelper::GetTextRect(tft, inputValue, font, Point(0, 0));
	// Now draw the text, right justified
	uint16_t textWidth = rect.width;
	uint16_t textHeight = rect.height;
	if (rect.width > 235)
	{
		// We cant show all the items, so we show the most we can
		int ptr = 1;
		while (FontHelper::GetTextRect(tft, inputValue.substr(inputValue.size() - ptr), font, Point(0, 0)).width < 235)
		{
			ptr++;
		}
		ptr=ptr-1;
		inputValue = inputValue.substr(ptr);
		textWidth = FontHelper::GetTextRect(tft, inputValue, font, Point(0, 0)).width;
	}
	UIPrimitives::Text(tft, textColor, 255, x + 5+textWidth/2, y + textHeight/2-5, font, is3D, inputValue);
}

/// <summary>
/// Processes the touch point
/// </summary>
/// <param name="pt">The pt.</param>
/// <returns>value each time, complete=true if it is complete</returns>
std::string NumericEntry::ProcessTouch(DriverBase &tft, std::string value, uint16_t x, uint16_t y, Point pt, bool &complete,
	bool singleDecimal)
{
	bool decimalActive = true;
	if (singleDecimal && value.find(".") != std::string::npos)
		decimalActive = false;

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
			y = 78;
		else
			y = 238;
	}
	if (!Rectangle(x, y, 253, 323).contains(pt))
		return value;									// Touch not in control
	pt.y -= y;
	pt.x -= x;
	uint8_t xKey = 0, yKey = 0;
	if (pt.y >= 58 && pt.y <= 110)
		yKey = 1;
	if (pt.y >= 111 && pt.y <= 163)
		yKey = 2;
	if (pt.y >= 164 && pt.y <= 216)
		yKey = 3;
	if (pt.y >= 217 && pt.y <= 269)
		yKey = 4;
	if (pt.y > 270)
		yKey = 5;
	if (yKey >= 1 && yKey <= 4)
	{
		if (pt.x >= 0 && pt.x <= 87)
			xKey = 1;
		if (pt.x >= 88 && pt.x <= 170)
			xKey = 2;
		if (pt.x >= 171)
			xKey = 3;
	}
	else
	{
		if (pt.x >= 0 && pt.x <= 129)
			xKey = 1;
		else xKey = 2;
	}
	if (xKey == 0 || yKey == 0)
		return value;
	if (yKey == 1 && xKey == 1)
		value.insert(value.size(), "1");
	if (yKey == 1 && xKey == 2)
		value.insert(value.size(), "2");
	if (yKey == 1 && xKey == 3)
		value.insert(value.size(), "3");
	if (yKey == 2 && xKey == 1)
		value.insert(value.size(), "4");
	if (yKey == 2 && xKey == 2)
		value.insert(value.size(), "5");
	if (yKey == 2 && xKey == 3)
		value.insert(value.size(), "6");
	if (yKey == 3 && xKey == 1)
		value.insert(value.size(), "7");
	if (yKey == 3 && xKey == 2)
		value.insert(value.size(), "8");
	if (yKey == 3 && xKey == 3)
		value.insert(value.size(), "9");
	if (yKey == 4 && xKey == 1 && decimalActive)
		value.insert(value.size(), ".");
	if (yKey == 4 && xKey == 2)
		value.insert(value.size(), "0");
	if (yKey == 4 && xKey == 2)
		if(value.size()>0)
			value.erase(value.size());
	if (yKey == 5 && xKey == 1)
	{
		complete = true;
		return "";
	}
	if (yKey == 5 && xKey == 2)
	{
		complete = true;
		return value;
	}
}


#endif