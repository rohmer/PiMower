#include <iostream>
#include "../RobotLib.h"
#include "../../RobotController/SensorLib/DigoleLCD.h"
#include "../UIFont.h"
#include "../ScreenManager.h"
#include "../UILabel.h"
#include "../UIButton.h"
#include "../UIMenu.h"
#include "../UIToggle.h"
#include "../UIRadioGroup.h"
#include "../UIInput.h"
#include "img256.h"
#include "../PageManager.h"
#include "../../RobotController/SensorLib/RA8875/Adafruit_RA8875.h"
using namespace std;

int main(int argc, char *argv[])
{

	RobotLib *robotLib = new RobotLib();
	Adafruit_RA8875 tft(10, 11);
	tft.begin(RA8875sizes::RA8875_800x480);
	for (uint8_t i = 255; i != 0; i -= 5) 
	{
		tft.PWM1out(i); 
		delay(10);
	}  

	for (uint8_t i = 0; i != 255; i += 5) 
	{
		tft.PWM1out(i); 
		delay(10);
	}
	tft.PWM1out(255); 
	tft.fillScreen(RA8875_RED);

	delay(500);

	tft.fillScreen(RA8875_YELLOW);

	delay(500);

	tft.fillScreen(RA8875_GREEN);

	delay(500);

	tft.fillScreen(RA8875_CYAN);

	delay(500);

	tft.fillScreen(RA8875_MAGENTA);

	delay(500);

	tft.fillScreen(RA8875_BLACK);
 	return 0;
}