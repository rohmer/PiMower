#include "UICheckbox.h"

UICheckbox::UICheckbox(std::string text, Point location)
	: UIElement(location, true)
	, textRightAlign(true)
	, font(UIFont::u8g_font_unifont)
	, value(false)
	, textColor(1)
	, checkColor(35)
{
	elementArea = calcSize();
	setUpdateCycle(500);
}

UICheckbox::UICheckbox(std::string text, Point location, UIFont::eFontName font)
	: UIElement(location, true)
	, textRightAlign(true)
	, font(font)
	, value(false)
	, textColor(1)
	, checkColor(35)
{
	elementArea = calcSize();
	setUpdateCycle(500);
}

UICheckbox::UICheckbox(std::string text, Point location, UIFont::eFontName font, bool textRightAlign)
	: UIElement(location, true)
	, textRightAlign(textRightAlign)
	, font(font)
	, value(false)
	, textColor(1)
	, checkColor(35)
{
	elementArea = calcSize();
	setUpdateCycle(500);
}

UICheckbox::UICheckbox(std::string text, Point location, UIFont::eFontName font, bool textRightAlign, bool isChecked)
	: UIElement(location, true)
	, textRightAlign(textRightAlign)
	, font(font)
	, value(isChecked)
	, textColor(1)
	, checkColor(35)
{
	elementArea = calcSize();
	setUpdateCycle(500);
}

void UICheckbox::setTextColor(uint8_t textColor)
{
	this->textColor = textColor;
}

void UICheckbox::setCheckColor(uint8_t checkColor)
{
	this->checkColor = checkColor;
}

void UICheckbox::update(DigoleLCD *lcdDriver)
{
	if (updateNeeded())
	{
		// position defines where the checkbox should be
		int fontHeight = UIFont::getFontHeight(font);
		int fontWidth = UIFont::getFontWidth(font);
		Rectangle boxRect;
		if (fontHeight > fontWidth)
		{
			
			boxRect.x1 = location.x;
			boxRect.y1 = location.y + ((fontHeight - fontWidth) / 2);
			boxRect.x2 = location.x+fontWidth;
			boxRect.y2 = location.y + fontWidth;				
		}
		else
		{
			if (fontHeight < fontWidth)
			{
				boxRect.x1 = location.x + ((fontWidth - fontHeight) / 2);
				boxRect.y1 = location.y;
				boxRect.x2 = location.x + fontHeight;
				boxRect.y2 = location.y + fontHeight;
			}
			else
			{
				// width==height, we already have a box
				boxRect.x1 = location.x;
				boxRect.y1 = location.y;
				boxRect.x2 = location.x + fontWidth;
				boxRect.y2 = location.y + fontHeight;
			}
		}
		lcdDriver->setColor(textColor);
		lcdDriver->drawBox(boxRect.x1, boxRect.y1, boxRect.x2 - boxRect.x1, boxRect.y2 - boxRect.y1);
		if (textRightAlign)
		{
			lcdDriver->printxy_abs(boxRect.x2 + (fontWidth / 2), boxRect.y1, text);
		}
		else
		{
			lcdDriver->printxy_abs(boxRect.x1 - ((text.size() + 0.5)*fontWidth), boxRect.y1, text);
		}
		// Now draw the check (Which actually is an X)
		if (value)
		{	
			lcdDriver->setColor(checkColor);
			lcdDriver->drawLine(boxRect.x1, boxRect.y1, boxRect.x2, boxRect.y2);
			lcdDriver->drawLine(boxRect.x2, boxRect.y1, boxRect.x1, boxRect.y2);
		}
		
	}	
}

Rectangle UICheckbox::calcSize()
{
	// Size is the size of the length of the label + the size of the checkbox (width of a char) + 1/2
	// for the space between the checkbox and the label
	return Rectangle(location.x, location.y, UIFont::getFontWidth(font)*(text.size()+1.5), UIFont::getFontHeight(font));
}

void UICheckbox::setValue(bool checked)
{
	this->value = checked;
}

bool UICheckbox::isChecked()
{
	return this->value;
}