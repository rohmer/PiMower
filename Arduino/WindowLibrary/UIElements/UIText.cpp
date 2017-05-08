#include "UIText.h"

UIText::UIText(DriverBase &tft, Rectangle location, std::string text, 
	Theme &elementTheme, eThemeObjState state) :
	UIElement(tft, location, state)
{
	this->theme = elementTheme;
	this->text = text;	
	themeSettings = elementTheme.LoadTheme(eThemeObjType::clickable, state);
	textScale = themeSettings.textScale;
	textColor = themeSettings.textColor;
	textFont = themeSettings.textFont;
	setButtonLines();
	Logger::Trace("UIText((%d,%d,%d,%d),%s) created", location.x1, location.y1,
		location.x2, location.y2, text.c_str());
	updatePending = true;
}

UIText::UIText(DriverBase &tft, Rectangle location, std::string text, eThemeObjState state,
	eUITextFont textFont, uint8_t textScale, uint16_t textColor) :
	UIElement(tft,location,state)
{
	this->text = text;
	this->textScale = textScale;
	this->textColor = textColor;
	this->textFont = textFont;
	setButtonLines();
	Logger::Trace("UIText((%d,%d,%d,%d),%s,%d,%d,%d,%d) created", location.x1, location.y1,
		location.x2, location.y2, text.c_str(),state,textFont,textScale,textColor);
	updatePending = true;
}

void UIText::setButtonLines()
{
	textLines.clear();	
	std::string::size_type pos = 0;
	std::string::size_type prev = 0;
	while((pos=text.find('\n',prev))!=std::string::npos)
	{
		std::string token = text.substr(prev, pos - prev);
#ifdef DEBUG
		Logger::Trace("Adding: %s to line list", token.c_str());
#endif
		textLines.push_back(token);
	}
	
	textLines.push_back(text.substr(prev));
#ifdef DEBUG
	std::string s = text.substr(prev);
	Logger::Trace("Adding: %s to line list", s.c_str());
#endif

}

void UIText::Update()
{
	if (!updatePending)
		return;
	tft.setTextSize(this->textScale);	
#ifdef DEBUG
	Logger::Trace("Writing text: %s to (%d,%d)", text.c_str(), 
		location.x1, location.y1);
	Logger::Trace("Text Scale: %d", this->textScale);
	Logger::Trace("Text Color: %d", this->textColor);
#endif
	tft.textWrite(location.x1, location.y1, textFont, this - textColor, 0, text);
	Logger::Trace("Writing \"%s\" at (%d,%d)", text.c_str(), location.x1, location.y1);
	
	updatePending= false;
}

void UIText::SetText(std::string text)
{
	this->text = text;
	setButtonLines();
	location = FontHelper::GetTextRect(tft, text, themeSettings.textFont, Point(location.x1, location.y1));
}


sTouchResponse UIText::ProcessTouch(Point touchPoint)
{
	// Text cannot be interacted with, so this is an automatic NoOp
	return sTouchResponse(this->elementID, eTouchResponse::NoOp);
}

