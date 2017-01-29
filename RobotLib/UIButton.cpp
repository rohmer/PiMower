#include "UIButton.h"

UIButton::UIButton(Point position, std::string text)
	: UIElement(position, false, true)
{
	labelFont = UIFont::defaultFont;
	labelText = text;
	textColor = DigoleLCD::WHITE;
	buttonColor = DigoleLCD::BLACK;
	buttonFrameColor = DigoleLCD::WHITE;	
}

UIButton::UIButton(Point position, std::string text, UIFont::eFontName font, uint8_t textColor, uint8_t buttonColor, uint8_t buttonFrameColor, Rectangle buttonSize)
	: UIElement(position, false, true)
{
	labelFont = font;
	labelText = text;
	textColor = textColor;
	this->buttonColor = buttonColor;
	this->buttonFrameColor = buttonFrameColor;
	elementArea = buttonSize;
}

void UIButton::setArea()
{
	int width = (labelText.length()*UIFont::getFontWidth(labelFont)+6)/2;
	int height = UIFont::getFontHeight(labelFont)+6;
	elementArea = Rectangle(position.x, position.y, position.x + width, position.y + height);	
	elementArea.update();	
	areaSet = true;
}

void UIButton::update(DigoleLCD *lcd, RobotLib *robotLib) 
{		
	if (!areaSet)
		setArea();
	lcd->setFont(labelFont);
	// First draw frame
	lcd->setColor(buttonFrameColor);
	lcd->drawFrame(elementArea.x1, elementArea.y1, elementArea.width, elementArea.height);
	lcd->setColor(textColor);
	int textY = (elementArea.height / 2) + elementArea.y1+6;
	int textX = elementArea.x1 + 3;
	lcd->printxy_abs(textX, textY, labelText);
}

int UIButton::processTouch(Point pt)
{
	if (elementArea.contains(pt))
		return 1;
	return -1;
}