#include "UIRadioGroup.h"

UIRadioGroup::UIRadioGroup(Point location) 
	: UIElement(location, true)
	, textRightAlign(true)
	, font(UIFont::u8g_font_unifont)
	, value(-1)
	, textColor(1)
	, checkColor(35)
{
	// We have no items yet, so default to nothing
	elementArea = Rectangle(0, 0, 0, 0);	
}

UIRadioGroup::UIRadioGroup(Point location, bool rightTextAlign)
	: UIElement(location, true)
	, textRightAlign(rightTextAlign)
	, font(UIFont::u8g_font_unifont)
	, value(-1)
	, textColor(1)
	, checkColor(35)
{
	elementArea = Rectangle(0, 0, 0, 0);
}

void UIRadioGroup::addButton(std::string text, int value, bool isChecked)
{
	// By default we have a button checked
	if (buttons.size() == 0)
	{		
		isChecked = true;
	}	
	// If this is checked, no others can be
	// Also set the maxTextWidth so we can later calculate bounding box
	maxTextWidth = text.size();
	for (int a = 0; a < buttons.size(); a++)
	{
		if(isChecked)
			buttons[a].isChecked = false;			
		if (buttons[a].text.size() > maxTextWidth)		
			maxTextWidth = buttons[a].text.size();
	}
	// Finally set the value of the radioGroup;
	if (isChecked)
	{
		this->value = value;
	}
	buttons.push_back(radioButton(value, isChecked, text));
	forceUpdate();	
}

bool UIRadioGroup::pointTouches(Point pt)
{
	// Check to see if the point is within this radio group
	if (!elementArea.contains(pt))
		return false;
	
	// Now we need to check to see if a radio button was clicked
	for (int a = 0; a < buttons.size(); a++)
	{
		if (buttons[a].boundingBox.contains(pt))
		{
			// Is is already checked?
			if (buttons[a].isChecked)
			{
				// We are done
				return true;
			}
			// Clear all buttons
			for (int b = 0; b < buttons.size(); b++)
			{
				buttons[b].isChecked = false;
			}
			// Its not checked, so check it
			buttons[a].isChecked = true;
			// Set the value of the control
			this->value = buttons[a].value;
			// Force an update
			forceUpdate();
			// return
			return true;
		}
	}
	return false;
}

void UIRadioGroup::update(DigoleLCD *lcdDriver)
{
	if (buttons.size() == 0)
	{
		// Nothing to draw
		return;
	}
	// First we need to figure out how big the whole bounding box for this control is 
	// this allows us to short circuit figuring out what was touched in pointTouches if its 
	// outside the control
	elementArea = calcSize();
	
	for (int a = 0; a < buttons.size(); a++)
	{
		int y = location.y + ((UIFont::getFontHeight(font) + 2)*a);
		// First draw the radio button
		Rectangle boxRect;
		int fontHeight = UIFont::getFontHeight(font);
		int fontWidth = UIFont::getFontWidth(font);
		if (fontHeight > fontWidth)
		{
			
			boxRect.x1 = location.x;
			boxRect.y1 = location.y + ((fontHeight - fontWidth) / 2);
			boxRect.x2 = location.x + fontWidth;
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
		int radius = boxRect.x2 - boxRect.x1;
		lcdDriver->drawCircle(location.x, y, radius, false);
		if (textRightAlign)
		{
			lcdDriver->printxy_abs(location.x + fontWidth, y, buttons[a].text);
			buttons[a].boundingBox = Rectangle(location.x - 1, y - 1, location.x + ((maxTextWidth + 1.5)*fontWidth), y + fontHeight + 1);
		}
		else
		{
			lcdDriver->printxy_abs(location.x - buttons[a].text.size() - 1, y, buttons[a].text);
			buttons[a].boundingBox = Rectangle(location.x - buttons[a].text.size() - 1, y - 1, location.x + radius + 1, y + fontHeight + 1);
		}
		
		// Draw the checkmark (Filled circle in radio button) if it is checked
		if (buttons[a].isChecked)
		{
			lcdDriver->setColor(checkColor);
			radius -= 2;
			lcdDriver->drawCircle(location.x, y, radius, true);
		}
	}	
}

Rectangle UIRadioGroup::calcSize()
{
	// So, our size is:
	//		x = (maxTextWidth + 1.5) * font width
	//		y = buttonCount * (fontHeight + 2)
	elementArea = Rectangle(location.x, location.y, (maxTextWidth + 1.5)*UIFont::getFontWidth(font), buttons.size()*(UIFont::getFontHeight(font) + 2));	
}

int UIRadioGroup::getValue()
{
	return this->value;
}