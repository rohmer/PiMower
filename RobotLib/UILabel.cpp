#include "UILabel.h"

UILabel::UILabel(Point position, std::string text)
	: UIElement(position, false, false)
{
	labelFont = UIFont::defaultFont;
	labelText = text;
	textColor = DigoleLCD::WHITE;
	textBGColor = DigoleLCD::BLACK;
	setArea();
}

UILabel::UILabel(Point position, std::string text, UIFont::eFontName font, uint8_t textColor, uint8_t textBackgroundColor)
	: UIElement(position, false, false)
{
	labelFont = font;
	labelText = text;
	textColor = textColor;
	textBGColor = textBackgroundColor;
	setArea();
}

void UILabel::setArea()
{
	int width = labelText.length()*UIFont::getFontWidth(labelFont);
	int height = labelText.length()*UIFont::getFontHeight(labelFont);
	elementArea = Rectangle(position.x, position.y, position.x + width, position.y + width);
}

void UILabel::update(DigoleLCD *lcd, RobotLib *robotLib)
{
	std::stringstream ss;
	ss << "Text Color: " << (int)textColor;
	robotLib->Log(ss.str());
	ss.clear();
	ss << "BG Color: " << (int)textBGColor;
	robotLib->Log(ss.str());
	ss.clear();
	ss << "Position: (" << position.x << ", " << position.y << ")";
	robotLib->Log(ss.str());
	robotLib->Log(labelText);
	lcd->setColor(textColor);
	lcd->setBackgroundColor(textBGColor);
	lcd->printxy_abs(position.x, position.y, labelText);
}