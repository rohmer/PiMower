#include "UIToggle.h"

UIToggle::UIToggle(Point position, std::string text)
	: UIElement(position, false, true)
{
	this->text = text;
	setArea();
}

UIToggle::UIToggle(Point position,
	std::string text,
	uint8_t checkColor,
	uint8_t textColor,
	UIFont::eFontName font,
	bool state,
	eTextAlignment textAlign)
	: UIElement(position, false, true)
{
	this->text = text;
	this->checkColor = checkColor;
	this->textColor = textColor;
	this->font = font;
	this->toggleState = state;
	this->textAlign = textAlign;
	setArea();
}

void UIToggle::setArea()
{
	// The width of the control is TextHeight y and
	// TextWidth * (Text.size() + 2)
	// 1 is for the checkbox 1 is for the space
	int checkSquare = UIFont::getFontWidth(font);
	if (UIFont::getFontHeight(font) < checkSquare)
		checkSquare = UIFont::getFontHeight(font);
	touchTarget = Rectangle(position.x, position.y, position.x + UIFont::getFontWidth(font)*text.size() + (checkSquare * 2), position.y + UIFont::getFontHeight(font));
	if (textAlign == eTextAlignment::textRight)
	{
		checkArea = Rectangle(position.x, position.y, position.x + checkSquare, position.y + checkSquare);
		checkArea.update();
		textArea = Point(position.x + (checkSquare * 2), position.y + UIFont::getFontHeight(font));
	}
	else
	{
		checkArea = Rectangle(position.x + (UIFont::getFontWidth(font)*(text.size() + checkSquare)), position.y, position.x + (UIFont::getFontWidth(font)*(text.size() + 2*checkSquare)), position.y + checkSquare);
		checkArea.update();
		textArea = Point(position.x, position.y + UIFont::getFontHeight(font));
	}
}

void UIToggle::update(DigoleLCD *lcd, RobotLib *robotLib)
{
	lcd->setColor(textColor);
	lcd->printxy_abs(textArea.x, textArea.y, text);
	lcd->drawFrame(checkArea.x1, checkArea.y1, checkArea.width, checkArea.height);
	lcd->drawFrame(checkArea.x1 + 1, checkArea.y1 + 1, checkArea.width - 2, checkArea.height - 2);
	if (toggleState)
	{
		// Draw an X
		lcd->setColor(checkColor);
		lcd->drawLine(checkArea.x1, checkArea.y1, checkArea.x2, checkArea.y2);
		lcd->drawLine(checkArea.x1 + 1, checkArea.y1, checkArea.x2, checkArea.y2 - 1);
		lcd->drawLine(checkArea.x1, checkArea.y1 + 1, checkArea.x2 - 1, checkArea.y2);
		lcd->drawLine(checkArea.x1, checkArea.y2, checkArea.x2, checkArea.y1);
		lcd->drawLine(checkArea.x1 + 1, checkArea.y2, checkArea.x2, checkArea.y1 + 1);
		lcd->drawLine(checkArea.x1, checkArea.y2 - 1, checkArea.x2 - 1, checkArea.y1);
	}
}

void UIToggle::setState(bool state, ScreenManager *screenManager)
{
	this->toggleState = state;
	screenManager->setDirty(this);
}

bool UIToggle::getState()
{
	return (this->toggleState);
}