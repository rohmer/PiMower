#pragma once
#include "UIElement.h"
#include <vector>

class UIGraphic :UIElement
{	
public:
	enum eGraphicColors
	{
		Color2,
		Color256,
		Color65536
	};
	UIGraphic(Point position, 
		uint width,
		uint height,
		const unsigned char graphic[], 
		eGraphicColors colorDepth);
	void update(DigoleLCD *lcd, RobotLib *robotLib) override;
	int processTouch(Point pt) override
	{
		return -1;
	}
protected:
	void setArea() override;
	
private:	
	eGraphicColors colorDepth;
	unsigned char *graphic;
	uint width, height;
};