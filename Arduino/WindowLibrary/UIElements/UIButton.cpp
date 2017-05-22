#include "UIButton.h"

#ifdef useButton

#ifdef RA8875

UIButton::UIButton(DriverBase &tft, Rectangle location, std::string buttonText, eUITextFont font,
	uint16_t textColor, uint8_t textScale, uint16_t buttonBGColor, uint8_t cornerRadius,
	bool is3D, bool raised) :
	UIElement(tft, location)
#endif
#ifdef FT8XX
UIButton::UIButton(DriverBase &tft, Rectangle location, std::string buttonText, eUITextFont font,
	uint32_t textColor, uint32_t buttonBGColor, uint8_t cornerRadius, bool is3D, bool raised,
	uint8_t alpha) :
	UIElement(tft, location)
#endif
{
	this->buttonText = buttonText;
	this->font = font;
	this->textColor = textColor;
	this->buttonBGColor = buttonBGColor;
	this->cornerRadius;
	this->is3D = is3D;
	this->raised = raised;
#ifdef RA8875
	this->textScale = textScale;
#endif
#ifdef FT8XX
	this->alpha = alpha;
#endif

#ifdef DEBUG
	Logger::Trace("UIButton(TFT, (%d,%d,%d,%d), %s, %d, %d, %d, %d, %d) initialized",
		location.x1, location.y1, location.x2, location.y2, buttonText.c_str(),
		font, textColor, buttonBGColor, cornerRadius);
#endif
}

sTouchResponse UIButton::ProcessTouch(Point pt)
{
	if (!this->enabled)
		return sTouchResponse(this->elementID, eTouchResponse::NoOp);
	if (this->location.contains(pt))
		return sTouchResponse(this->elementID, eTouchResponse::ControlTouched);
}

void UIButton::SetButtonText(std::string text)
{
	if (text == this->buttonText)
		return;
	this->buttonText = text;
	this->is3D = is3D;
	this->updatePending = true;	
}

void UIButton::Update()
{
	if (!updatePending)
	{
#ifdef DEBUG
		Logger::Trace("No update for UIButton pending");
#endif
		return;
	}

	// First draw the box
	if (is3D)
	{
		Button::Draw(tft, !raised, location.x1, location.y1, location.width, location.height,
			textColor, buttonBGColor, font, buttonText, true, cornerRadius, alpha);
	}
	else
	{
		Button::Draw(tft, !raised, location.x1, location.y1, location.width, location.height,
			textColor, buttonBGColor, font, buttonText, false, cornerRadius, alpha);
	}
	this->updatePending = false;
}
#endif
