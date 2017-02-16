#pragma once
#include "UIElement.h"
#include <vector>

// Used to define an area that may or may not have another element
// as touchable
// Use case: A sleep screen to make the whole screen touchable
class UITouchArea : UIElement 
{
public:
	UITouchArea(Point position, 
		uint width, 
		uint height);
	void update(DigoleLCD *lcd, RobotLib *robotLib) override;
	int processTouch(Point pt) override;

protected:
	void setArea();	

private:
	uint width, height;
};