#include "UIRadioButton.h"
#include "../../Options.h"
#ifdef RA8875

UIRadioButton::UIRadioButton(Adafruit_RA8875 &tft, Rectangle location, std::string text,
	bool checked, Theme &elementTheme, eThemeObjState state) :
	UIElement(tft, location, state)
{
	this->buttonText = text;
	this->isChecked = checked;	
	sThemeSettings settings = elementTheme.LoadTheme(eThemeObjType::clickable, state);
	this->textFont = settings.textFont;
	textColor = settings.textColor;
	controlColor = settings.borderColor;
	checkColor = settings.iconColor;
	textScale = settings.textScale;
	// WE will reset x2 to denote that it needs to be generated
	// by update.
	this->location.x2 = -1;
}

UIRadioButton::UIRadioButton(Adafruit_RA8875 &tft, Rectangle location, std::string text, bool checked,
	eUITextFont textFont, uint16_t textColor, uint8_t textScale,
	uint16_t controlColor, uint16_t checkColor) :
	UIElement(tft, location, eThemeObjState::defaultState)
{
	this->buttonText = text;
	this->isChecked = checked;
	this->textFont = textFont;
	this->controlColor = controlColor;
	this->checkColor = checkColor;
	this->textColor = textColor;
	this->textScale = textScale;
	// WE will reset x2 to denote that it needs to be generated
	// by update.
	this->location.x2 = -1;
}

UIRadioButton::~UIRadioButton()
{
	if (checkRect != NULL)
		delete(checkRect);
}

void UIRadioButton::SetText(std::string text)
{
	if (buttonText == text)
		return;
	this->buttonText = text;
	location.x2 = -1;
	Invalidate();
}

void UIRadioButton::SetChecked(bool checked)
{
	if (checked == isChecked)
		return;
	isChecked = false;
	Invalidate();
}

void UIRadioButton::Update()
{
	if (!updatePending)
	{
#ifdef DEBUG
		Logger::Trace("No update pending");
#endif
		return;
	}

	tft.setTextSize(textScale);
	if (location.x2 == -1)
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
		x2 = textRect.x1+textRect.x2 / buttonText.size()+location.x1;
		y2 = textRect.y2+location.y2;
		if (checkRect == NULL)
		{
			checkRect = new Rectangle(x1, y1, x2, y2);
			checkRect->update();
		}
		else
		{
			checkRect->x1 = x1;
			checkRect->y1 = y1;
			checkRect->x2 = x2;
			checkRect->y2 = y2;
			checkRect->update();
		}

		// So the total width is: checkRect.x2*1.5+textRect.x2
		location.x2 = location.x1 + (checkRect->x2*1.5) + textRect.x2;
		// Height is textRect.y2 + 2
		location.y2 = textRect.y2 + 2;
		location.update();
	}
#ifdef DEBUG 
	Logger::Trace("Check Rect (%d,%d,%d,%d), w=%d, h=%d", checkRect->x1, checkRect->y1, 
		checkRect->x2, checkRect->y2, checkRect->width,checkRect->height);
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
		tft.drawCircle(checkRect->center.x, location.center.y+1, checkRect->width - i, controlColor);
	
	// Is it checked?
	if (isChecked)
	{
		tft.fillCircle(checkRect->center.x, location.center.y+1, checkRect->width-(checkLineWidth+1), checkColor);
	}

	// Now draw text
#ifdef DEBUG 
	Logger::Trace("Setting TextCursor(%d,%d)", location.x1 + checkRect->width * 1.5, checkRect->y1);
#endif
	tft.setCursor(location.x1 + checkRect->width * 2, checkRect->center.y);
	tft.setTextColor(textColor);
	tft.print(buttonText.c_str());

	updatePending = false;
}

sTouchResponse UIRadioButton::ProcessTouch(Point pt)
{
	if (location.contains(pt))
	{
		return sTouchResponse(this->elementID, eTouchResponse::ControlTouched);
	}

	return sTouchResponse(this->elementID, eTouchResponse::NoOp);
}

#endif