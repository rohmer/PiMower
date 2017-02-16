#pragma once
#include "UIElement.h"
#include "UILabel.h"
#include "UIGraphic.h"
#include <ctime>
#include <iostream>
#include "../RobotController/SensorLib/BQ34Z100G1.h"

class IdlePage : public UIElement
{
public:	
	IdlePage();
	void update(DigoleLCD *lcd, RobotLib *robotLib) override;
	int processTouch(Point pt) override;
	
private:
	time_t nextUpdate;
	BQ34Z100G1 *batMon = NULL;
};
