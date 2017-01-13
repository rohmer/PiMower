#include "UIButton.h"

UIButton::UIButton(Rectangle location, std::string buttonText)
	: UIElement(Point(location.x1, location.y1))
	, buttonColor(35)
	, textColor(252)
	, buttonText(buttonText)
	, font(UIFont::u8g_font_unifont)	
	, triggered(false)
	, useButtonFrame(true)
	, buttonFrameColor(1)
{
	elementArea = location;
	setUpdateCycle(-1);
	forceUpdate();
}

UIButton::UIButton(Rectangle location, std::string buttonText, UIFont::eFontName  font, uint8_t buttonColor, uint8_t textColor, bool useButtonFrame, uint8_t buttonFrameColor)
	: UIElement(Point(location.x1, location.y1))
	, buttonColor(buttonColor)
	, textColor(textColor)
	, buttonText(buttonText)
	, font(font)	
	, triggered(false)
	, useButtonFrame(useButtonFrame)
	, buttonFrameColor(buttonFrameColor)
{
	elementArea = location;
	setUpdateCycle(-1);
	forceUpdate();
}

Rectangle UIButton::calcSize()
{
	return elementArea;
}

void UIButton::update(DigoleLCD *lcdDriver)
{
	if (!this->updateNeeded())
		return;
	Rectangle drawRect(elementArea.x1, elementArea.y1, elementArea.x2, elementArea.y2);
	if (useButtonFrame)
	{
		lcdDriver->setColor(buttonFrameColor);
		lcdDriver->drawBox(drawRect.x1, drawRect.y1, drawRect.width, drawRect.height);
		drawRect.x1++;
		drawRect.y1++;
		drawRect.x2--;
		drawRect.y2--;
		drawRect.update();
	}
	
	lcdDriver->setColor(buttonColor);
	lcdDriver->drawBoxFill(drawRect.x1, drawRect.y1, drawRect.width, drawRect.height);
	if (buttonText.size() > 0)
	{		
	// Now center the text in the button
	// TODO: Assuming the the position for text is top left corner, maybe wrong
		int centerX, centerY;
		int fontHeight = UIFont::getFontHeight(font);
		int fontWidth = UIFont::getFontWidth(font);
		if (drawRect.x1 < drawRect.x2)
			centerX = (drawRect.x2 - drawRect.x1) / 2;
		else
			centerX = (drawRect.x1 - drawRect.x2) / 2;
		if (drawRect.x1 < drawRect.x2)
			centerY = (drawRect.y2 - drawRect.y1) / 2 - (fontHeight / 2);
		else
			centerY = (drawRect.y1 - drawRect.y2) / 2 - (fontHeight / 2);
		lcdDriver->setColor(textColor);

		lcdDriver->printxy_abs(centerX - ((fontWidth*buttonText.size()) / 2), centerY, buttonText);
	}	
}

bool UIButton::pointTouches(Point pt)
{
	if (!clickable)
		return false;
	if (elementArea.contains(pt))
	{		
		touchEvents.push_back(true);
		return true;
	}
	return false;
}