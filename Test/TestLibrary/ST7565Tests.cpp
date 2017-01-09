#include "ST7565Tests.h"
#include "../../RobotController/SensorLib/ST7565.h"

TEST_GROUP(ST7565)
{	
}
;

TEST(ST7565, InitTest)
{
	RobotLib *rl = new RobotLib();
	ST7565 *lcd = reinterpret_cast<ST7565 *>(rl->getDeviceManager()->getByName("ST7565"));
	if (!lcd)
		FAIL("Failed to initialize LCD via device manager");
	delete(rl);	
}

TEST(ST7565, WriteText)
{
	RobotLib *rl = new RobotLib();
	ST7565 *lcd = reinterpret_cast<ST7565 *>(rl->getDeviceManager()->getByName("ST7565"));
	if (!lcd)
		FAIL("Failed to initialize LCD via device manager");
	lcd->clearDisplay();
	lcd->setBrightness(15);
	lcd->drawstring(0, 0, static_cast<char *>("1234567890123456"));
	lcd->drawstring(0, 1, static_cast<char *>("1234567890123456"));
	lcd->drawstring(0, 2, static_cast<char *>("1234567890123456"));
	usleep(10);
}