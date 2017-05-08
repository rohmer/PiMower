#include "UICheckBox.h"

UICheckBox::UICheckBox(DriverBase &tft, Rectangle location, std::string boxText, bool checked,
	Theme &elementTheme, eThemeObjState state) :
	UIElement(tft, location, state)
{
	location.x2 = -1;
	this->isChecked = checked;
	this->buttonText = buttonText;
	theme = elementTheme.LoadTheme(eThemeObjType::clickable, eThemeObjState::defaultState);
	this->textFont = theme.textFont;
	this->textColor = theme.textColor;
	this->textScale = theme.textScale;
	this->boxColor = theme.borderColor;
	this->boxShadowColor = theme.shadowColor;
	this->shadowSize = theme.shadowThickness;
	this->boxBorderSize = theme.borderSize;
	if (theme.cornerType == eCornerType::Rounded)
		hasRoundCorners = true;
	else
		hasRoundCorners = false;
	this->cornerRadius = theme.cornerRadius;
	this->boxCheckColor = theme.bgColor;
#ifdef DEBUG
	Logger::Trace("UICheckBox(TFT,(%d,%d,%d,%d),%s,%s,THEME,%d) initalized", location.x1, location.y1,
		location.x2, location.y2, buttonText.c_str(), Logger::BoolToStr(checked).c_str(), (int)state);
#endif

}

UICheckBox::UICheckBox(DriverBase &tft, Rectangle location, std::string boxText, bool checked,
	eUITextFont textFont, uint16_t textColor, uint8_t textScale, uint16_t boxColor,
	uint16_t boxShadowColor, uint8_t boxShadowSize, uint8_t boxBorderSize,
	uint16_t boxCheckColor, bool hasRoundCorners, uint8_t cornerRadius) :
	UIElement(tft, location, eThemeObjState::defaultState)
{	
	this->isChecked = checked;
	this->buttonText = boxText;
	this->textFont = textFont;
	this->textColor = textColor;
	this->textScale = textScale;
	this->boxColor = boxColor;
	this->boxShadowColor = boxShadowColor;
	this->shadowSize = boxShadowSize;
	this->boxBorderSize = boxBorderSize;
	this->boxCheckColor = boxCheckColor;
	this->hasRoundCorners = hasRoundCorners;
	this->cornerRadius = cornerRadius;

#ifdef DEBUG
	Logger::Trace("UICheckBox(TFT,(%d,%d,%d,%d),%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d)",location.x1,location.y1,
		location.x2,location.y2,buttonText.c_str(), Logger::BoolToStr(checked).c_str(),textFont, textColor, 
		textScale, boxColor, boxShadowColor, shadowSize, boxBorderSize, boxCheckColor, 
		Logger::BoolToStr(hasRoundCorners).c_str(), cornerRadius);
#endif
}

void UICheckBox::Update()
{
	if (!updatePending)
	{
#ifdef DEBUG
		Logger::Trace("No update pending");
#endif
		return;
	}

	tft.setTextSize(textScale);
	if (checkRect==NULL)
	{
		// Figure out the size of the control
		Rectangle textRect = FontHelper::GetTextRect(tft, buttonText, textFont, Point(0, 0));

#ifdef DEBUG
		Logger::Trace("Text Rect: (%d,%d,%d,%d), buttonText length: %d", textRect.x1,
			textRect.y1, textRect.x2, textRect.y2, buttonText.size());
#endif
		int x1, y1, x2, y2;
		x1 = location.x1;
		y1 = location.y1;
		x2 = textRect.x1 + (textRect.x2/buttonText.size())  + location.x1;		
		y2 = textRect.y2 + location.y1;
		Logger::Trace("(textRect):x1:%d, y1:%d, x2:%d, y2:%d, (location)x1:%d, y1:%d, x2:%d, y2:%d",
			x1, y1, x2, y2, location.x1, location.y1, location.x2, location.y2);
		checkRect = new Rectangle(x1, y1, x2, y2);
		checkRect->update();
		
		// So the total width is: checkRect.x2*1.5+textRect.x2
		location.x2 = location.x1 + (checkRect->x2*1.5) + textRect.x2;
		// Height is textRect.y2 + 2
		location.y2 = textRect.y2 + 2;
		location.update();
	}
#ifdef DEBUG 
	Logger::Trace("Check Rect (%d,%d,%d,%d), w=%d, h=%d", checkRect->x1, checkRect->y1,
		checkRect->x2, checkRect->y2, checkRect->width, checkRect->height);
#endif
	// First lets draw the control
	uint8_t checkLineWidth = 3;
	if (checkRect->width < 10)
	{
		if (checkRect->width >= 8)
			checkLineWidth = 2;
		else
			checkLineWidth = 1;
	}	
	for (int i = 0; i < checkLineWidth; i++)
		tft.drawRect(checkRect->x1+i, checkRect->y1+i, checkRect->width-i, checkRect->height-i, boxColor);

	// Is it checked?
	if (isChecked)
	{
		tft.drawLine(checkRect->x1, checkRect->y1, checkRect->x2, checkRect->y2, boxCheckColor);
		tft.drawLine(checkRect->x1+1, checkRect->y1, checkRect->x2, checkRect->y2-1, boxCheckColor);
		tft.drawLine(checkRect->x1 + 1, checkRect->y1+1, checkRect->x2-1, checkRect->y2, boxCheckColor);

		tft.drawLine(checkRect->x2, checkRect->y1, checkRect->x1, checkRect->y2, boxCheckColor);
		tft.drawLine(checkRect->x2-1, checkRect->y1, checkRect->x1, checkRect->y2-1, boxCheckColor);
		tft.drawLine(checkRect->x2, checkRect->y1+1, checkRect->x1+1, checkRect->y2, boxCheckColor);
	}

	// Now draw text
#ifdef DEBUG 
	Logger::Trace("Setting TextCursor(%d,%d)", location.x1 + checkRect->width * 1.5, checkRect->y1);
#endif
	tft.textWrite(location.x1 + checkRect->width * 2, checkRect->center.y,
		textFont, textColor, 0, buttonText);
	
	updatePending = false;
}

UICheckBox::~UICheckBox()
{
	if (checkRect != NULL)
	{
		delete(checkRect);
	}
}

sTouchResponse UICheckBox::ProcessTouch(Point touchPoint)
{
	if (!location.contains(touchPoint))
		return sTouchResponse(this->elementID, eTouchResponse::NoOp);
	if(!this->enabled)
		return sTouchResponse(this->elementID, eTouchResponse::NoOp);
	// Its in our control, so toggle checked
	if (isChecked)
		isChecked = false;
	else
		isChecked = true;
	Invalidate();
	return sTouchResponse(this->elementID, eTouchResponse::ControlTouched);
}

