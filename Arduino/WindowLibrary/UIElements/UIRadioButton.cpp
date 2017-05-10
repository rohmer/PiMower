#include "UIRadioButton.h"

UIRadioButton::UIRadioButton(DriverBase &tft, Rectangle location, std::string text, bool checked, eUITextFont textFont,
	uint16_t textColor, uint8_t textScale, uint16_t controlColor, uint16_t checkColor, bool is3D, bool textRight)
	: UIElement(tft,location)
{
	this->buttonText = text;
	this->isChecked = checked;
	this->textFont = textFont;
	this->textColor = textColor;
	this->textScale = textScale;
	this->controlColor = controlColor;
	this->checkColor = checkColor;
	this->is3D = is3D;
	this->textRight = textRight;
#ifdef DEBUG
	Logger::Trace("UIRadioButton(TFT,(%d,%d,%d,%d), %s, %s, %d, %d, %d, %d, %d, %s) initialized",
		location.x1, location.y1, location.x2, location.y2,
		text.c_str(), Logger::BoolToStr(checked).c_str(), (int)textFont, 
		textColor, textScale, controlColor, checkColor, 
		Logger::BoolToStr(is3D).c_str());
#endif
}

void UIRadioButton::Update()
{
	if (!updatePending)
	{
#ifdef DEBUG
		Logger::Trace("No update pending for RadioButton");
#endif
		return;
	}
	
#ifdef RA8875
	tft.setTextSize(textScale);
#endif

	location = RadioButton::Draw(tft, is3D, isChecked, location.x1, location.y1, textColor, controlColor,
		checkColor, textFont, buttonText, textRight);
	updatePending = false;
}

void UIRadioButton::SetText(std::string text)
{
	if (this->buttonText == text)
		return;
	this->buttonText = text;
	Invalidate();
}

void UIRadioButton::SetChecked(bool checked)
{
	if (this->isChecked == checked)
		return;
	this->isChecked;
	Invalidate();
}

sTouchResponse UIRadioButton::ProcessTouch(Point touchPoint)
{
	if (location.contains(touchPoint))
	{
		this->isChecked = !isChecked;
		Invalidate();
		return sTouchResponse(this->elementID, eTouchResponse::ControlTouched);
	}
	return sTouchResponse(this->elementID, eTouchResponse::NoOp);
}
