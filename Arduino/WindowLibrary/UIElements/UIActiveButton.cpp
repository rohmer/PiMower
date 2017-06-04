#include "UIActiveButton.h"

#ifdef useActiveButton

UIActiveButton::UIActiveButton(DriverBase &tft, Rectangle location, std::string buttonText, eUITextFont font,
	tColor textColor, uint8_t textScale, tColor buttonBGColor, uint8_t cornerRadius,
	bool is3D, bool raised, uint16_t updateInMillis, std::string elementName = "", uint8_t alpha) :
	UIElement(tft, location, elementName, eElementType::ActiveButton)
{
	this->buttonText = buttonText;
	this->font = font;
	this->textColor = textColor;
	this->buttonBGColor = buttonBGColor;
	this->cornerRadius;
	this->is3D = is3D;
	this->raised = raised;
	this->updateInterval = updateInMillis;

#ifdef RA8875
	this->textScale = textScale;
#endif
	this->alpha = alpha;
#ifdef DEBUG
	Logger::Trace("UIButton(TFT, (%d,%d,%d,%d), %s, %d, %d, %d, %d, %d) initialized",
		location.x1, location.y1, location.x2, location.y2, buttonText.c_str(),
		font, textColor, buttonBGColor, cornerRadius);
#endif
}

sTouchResponse UIActiveButton::ProcessTouch(Point pt)
{
	if (!this->enabled)
		return sTouchResponse(this->elementID, eTouchResponse::NoOp);
	if (this->location.contains(pt))
		return sTouchResponse(this->elementID, eTouchResponse::ControlTouched);
}

void UIActiveButton::SetButtonText(std::string text)
{
	if (text == this->buttonText)
		return;
	this->buttonText = text;
	this->is3D = is3D;
	this->updatePending = true;
}

/// <summary>
/// An active button will call this first, then draw whatever data on the 
/// button that it wants to display.  This will automatically be updated at 
/// update interval
/// </summary>
void UIActiveButton::Update()
{
	uint32_t time = millis();
	if (!updatePending | time>updateTime)
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
	updateTime = millis() + updateInterval;
	this->updatePending = false;
}  


#endif