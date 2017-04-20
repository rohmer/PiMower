#include "UIRadioGroup.h"

UIRadioGroup::UIRadioGroup(Point position)
	: UIElement(position, false, true)
{
}

UIRadioGroup::UIRadioGroup(Point position,
	uint8_t radioColor,
	uint8_t textColor,
	UIFont::eFontName font,
	GroupAlignment alignment,
	eTextAlignment textAlignment)
	: UIElement(position, false, true)
{
	this->radioColor = radioColor;
	this->textColor = textColor;
	this->font = font;
	this->alignment = alignment;
	this->textAlignment = textAlignment;
}

void UIRadioGroup::setArea()
{
	int checkSize = UIFont::getFontHeight(font);
	if (UIFont::getFontWidth(font) < checkSize)
	{
		checkSize = UIFont::getFontWidth(font);
	}
	if (alignment == GroupAlignment::Horizontal)
	{
		int totalSize = 0;
		for (int a = 0; a < values.size(); a++)
		{
			if (textAlignment == eTextAlignment::textRight)
			{
				int startX = position.x + totalSize;
				int controlPtr = 0;
				values[a].checkPoint = Point(startX, position.y);
				controlPtr += checkSize * 2;
				values[a].textStart = Point(startX + controlPtr, position.y + UIFont::getFontHeight(font));
				controlPtr += values[a].label.size()*(UIFont::getFontWidth(font) * .75);
				values[a].touchPoint = Rectangle(startX, position.y, position.x + controlPtr, position.y + UIFont::getFontHeight(font));
				totalSize += controlPtr;
			}
			else
			{
				int startX = position.x + totalSize;
				values[a].textStart = Point(position.x + totalSize, position.y);
				totalSize += values[a].label.size()*UIFont::getFontWidth(font);
				totalSize += checkSize;
				values[a].checkPoint = Point(position.x + totalSize, position.y);
				totalSize += UIFont::getFontWidth(font);
				values[a].touchPoint = Rectangle(startX, position.y, position.x + totalSize, position.y + UIFont::getFontHeight(font));
			}
		}
	}
	else
	{
		// Vertical Alignment
		for (int a = 0; a < values.size(); a++)
		{
			if (textAlignment == eTextAlignment::textRight)
			{
				values[a].checkPoint = Point(position.x, position.y + (a*UIFont::getFontHeight(font) * 1.5));
				values[a].textStart = Point(position.x + checkSize * 2, position.y + ((a + 1)*UIFont::getFontHeight(font) * 1.5) - 2);
			}
			else
			{
				values[a].textStart = Point(position.x, position.y + (a*UIFont::getFontHeight(font) * 1.5) - 2);
				values[a].checkPoint = Point(position.x + checkSize + values[a].label.size()*UIFont::getFontWidth(font), position.y + ((a + 1)*UIFont::getFontHeight(font) * 1.5));
			}
		}
	}

	// Make sure one is selected
	bool itemSelected = false;
	for (int a = 0; a < values.size(); a++)
	{
		if (values[a].value)
			itemSelected = true;
	}
	if (!itemSelected)
		values[0].value = true;
}

void UIRadioGroup::update(DigoleLCD *lcd, RobotLib *robotLib)
{
	int checkSize = UIFont::getFontHeight(font);
	if (UIFont::getFontWidth(font) < checkSize)
	{
		checkSize = UIFont::getFontWidth(font) / 2;
	}

	for (int a = 0; a < values.size(); a++)
	{
		lcd->setColor(textColor);
		// Draw box
		lcd->drawBox(values[a].checkPoint.x, values[a].checkPoint.y, checkSize, checkSize);
		lcd->printxy_abs(values[a].textStart.x, values[a].textStart.y, values[a].label);
		if (values[a].isSelected)
		{
			lcd->setColor(radioColor);
			lcd->setColor(radioColor);
			lcd->drawBoxFill(values[a].checkPoint.x + 1, values[a].checkPoint.y + 1, checkSize - 2, checkSize - 2);
		}
	}
}

bool UIRadioGroup::addRadioItem(std::string label, int value, bool isSelected)
{
	if (isSelected)
	{
		for (int a = 0; a < values.size(); a++)
		{
			values[a].isSelected = false;
		}
	}
	sRadioValue radioValue;
	radioValue.label = label;
	radioValue.value = value;
	radioValue.isSelected = isSelected;

	values.push_back(radioValue);
	setArea();
	return true;
}