#include "UIGraphic.h"

UIGraphic::UIGraphic(Point position,
	uint width,
	uint height,
	const unsigned char graphic[],
	eGraphicColors colorDepth)
	: UIElement(position, false, false)
{
	int arSize = sizeof(graphic);
	memcpy(this->graphic, graphic, sizeof(arSize));
	this->colorDepth = colorDepth;
	this->width = width;
	this->height = height;
	setArea();
}

void UIGraphic::update(DigoleLCD *lcd, RobotLib *robotLib)
{
	switch (colorDepth)
	{
	case eGraphicColors::Color2:
		lcd->drawBitmap(position.x, position.y, width, height, graphic, DigoleLCD::WHITE);
		break;
	case eGraphicColors::Color256:
		lcd->drawBitmap256(position.x, position.y, width, height, graphic);
		break;
	case eGraphicColors::Color65536:
		lcd->drawBitmap256K(position.x, position.y, width, height, graphic);
		break;
	}
}

void UIGraphic::setArea()
{
	elementArea = Rectangle(position.x, position.y, position.x + width, position.y + height);
}