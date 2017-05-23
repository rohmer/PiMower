#include "UICheckBox.h"

#ifdef RA8875
UICheckBox::UICheckBox(DriverBase &tft, Rectangle location, std::string boxText, bool checked,
	eUITextFont textFont, uint16_t textColor, uint8_t textScale, uint16_t boxColor,
	uint16_t boxShadowColor, uint8_t boxShadowSize, uint8_t boxBorderSize,
	uint16_t boxCheckColor, bool hasRoundCorners, uint8_t cornerRadius, std::string elementName = "") :
#endif
#ifdef FT8XX
	UICheckBox::UICheckBox(DriverBase &tft, Rectangle location, std::string boxText, bool checked,
		eUITextFont textFont, uint32_t textColor, uint8_t textScale, uint32_t boxColor,
		uint32_t boxShadowColor, uint8_t boxShadowSize, uint8_t boxBorderSize,
		uint32_t boxCheckColor, bool hasRoundCorners, uint8_t cornerRadius, std::string elementName = "") :
#endif
	UIElement(tft, location, elementName, eElementType::CheckBox)
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
		UIElement::Update();
		return;
	}

#ifdef RA8875
	tft.setTextSize(textScale);
#endif

	CheckBox::Draw(tft, true, isChecked, location.x1, location.y1, 
		textColor, boxColor, boxCheckColor, 
		textFont, buttonText, true, true, cornerRadius);
	updatePending = false;
}

UICheckBox::~UICheckBox()
{

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
