#include <iostream>
#include "../RobotLib.h"
#include "../../RobotController/SensorLib/DigoleLCD.h"
#include "../UIFont.h"
#include "../UIButton.h"

using namespace std;

int main(int argc, char *argv[])
{
	RobotLib *robotLib = new RobotLib();
	DigoleLCD *lcd = new DigoleLCD(robotLib, 0x27);
	//lcd->setup(27);
	lcd->clearScreen();
	lcd->drawBox(10, 10, 200, 100);
	return 0;
}