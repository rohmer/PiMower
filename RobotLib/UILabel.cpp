#include "UILabel.h"

UILabel::UILabel(std::string text, Point location)
	: UIElement(Point(location.x, location.y), false)
	, font(UIFont::u8g_font_unifont)
	, text(text)
	, textColor(1)
{
	// We dont need to calculate the box, since this isnt clicakble
	setUpdateCycle(-1);	
}

UILabel::UILabel(std::string text, Point location, UIFont::eFontName font, bool clickable) 
	: UIElement(Point(location.x, location.y), clickable)
	, font(font)
	, text(text)
	, textColor(1)
{
	// Calculate the size if this is clickable
	if (clickable)
	{
		elementArea = Rectangle(location.x, location.y, UIFont::getFontWidth(font)*text.size(), UIFont::getFontHeight(font));
	}
	setUpdateCycle(-1);
}
	
UILabel::UILabel(std::string text, Point location, UIFont::eFontName font, bool clickable, uint8_t textColor) 
	: UIElement(Point(location.x, location.y), clickable)
	, font(font)
	, text(text)
	, textColor(textColor)
{
	// Calculate the size if this is clickable
	if (clickable)
	{
		elementArea = calcSize();
	}
	setUpdateCycle(-1);
}

void UILabel::update(DigoleLCD *lcdDriver) 
{	
	if (updateNeeded())
	{
		lcdDriver->setColor(textColor);
		lcdDriver->printxyf_abs(location.x, location.y, UIFont::getFontNum(font), text);
	}
}

Rectangle UILabel::calcSize()
{
	return Rectangle(location.x, location.y, UIFont::getFontWidth(font)*text.size(), UIFont::getFontHeight(font));
}