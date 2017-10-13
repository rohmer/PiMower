/*
Name:		WindowLibrary.ino
Created:	4/24/2017 8:33:23 PM
Author:	rohme
Editor:	http://www.visualmicro.com
*/

#define TEST_FT_PRIMITIVES

#include <utility.h>
#include <unwind-cxx.h>
#include <system_configuration.h>
#include <StandardCplusplus.h>
#include "Options.h"
#include "Driver\DriverBase.h"

#ifdef RA8875
#include "Driver\RA8875Driver.h"
#endif
#ifdef FT8XX
#include "Driver\FT8XXDriver.h"
#endif

#include "UIElements\ControlDisplay\Button.h"
#include "UIElements\ControlDisplay\CheckBox.h"
#include "UIElements\ControlDisplay\DropDownList.h"
#include "UIElements\ControlDisplay\ProgressBar.h"
#include "UIElements\ControlDisplay\RadioButton.h"
#include "UIElements\ControlDisplay\Slider.h"
#include "UIElements\ControlDisplay\NumericEntryRA8875.h"
#include "UIElements\ControlDisplay\TextEntryRA8875.h"
#include "UIElements\ControlDisplay\NumericEntryFT8XX.h"
#include "UIElements\ControlDisplay\TextEntryFT8XX.h"

#include "UIElements\ControlDisplay\RingMeter.h"
#include "UIElements\ControlDisplay\Window.h"
#include "UIElements\UIButton.h"
#include "Utility\Logger.h"
#include "Utility\Color.h"
#include "Utility\CircularMinMaxBuffer.h"
#include "UIElements\UIPages\ScreenSaver.h"
#include "UIElements\UIPages\HomeScreen.h"
#include "UIElements\UIElementGraph.h"
#include "UIElements\ControlDisplay\Compass.h"

#include "WindowManager\WindowManager.h"
/*
bool updated = false;
uint8_t prog = 0;
uint32_t runTime = millis();
int reading = 0;
std::string val = "0";
int d = 0;
*/
WindowManager *wm = NULL;
/*
UIWindow *win = NULL;
ScreenSaver *ss = NULL;
*/
HomeScreen *hs = NULL;
/*
UIButton *settings = NULL;
*/
FT8XXDriver *tft;
std::string val = "0";
bool updated = false;
CircularMinMaxBuffer *buf;
UIElementGraph *eg = NULL;
Compass *compass = NULL;

// the setup function runs once when you press reset or power the board
void setup() {
	//wm = WindowManager::instance(10, 9, 11, 13, 12, eLCDSizes::lcd800x480);		
	buf = new CircularMinMaxBuffer(25);
	tft = new FT8XXDriver(800, 480);
}

void testPrimitives(DriverBase &tft)
{
	for (int i = 0; i < 360; i++)
	{
		tft.clearScreen();
		Compass::Draw(*wm->GetDriver(), Rectangle(50, 50, 250, 250), i, Color::Yellow, Color::Red, eUITextFont::AntiAliasFont29,
			true, eUITextFont::AntiAliasFont28, Color::CadetBlue, Color::DimGray);
		tft.swapDisplay();
		delay(100);
	}


}
/*
void testSpecialButtons()
{
FT8XXDriver tft(800, 480);
tft.clearScreen();
SettingsButton *settingsButton = new SettingsButton(tft, Rectangle(535, 325, 785, 465));
settingsButton->Update();
tft.swapDisplay();
}
*/

// the loop function runs over and over again until power down or reset
void loop()
{
	/*if (!wm)
	{
	wm = WindowManager::instance(10, 9, 11, 13, 12, eLCDSizes::lcd800x480);
	for (int i = 0; i < 25; i++)
	{
	float val = static_cast<float>(random(1, 1000) / static_cast<float>(100));
	buf->PushItem(val);
	}
	}
	*/
	testPrimitives(*tft);
	return;
	/*
	if (hs == NULL)
	hs = new HomeScreen(*wm->GetDriver());
	wm->RegisterElement(hs);
	*/

	/*if(eg==NULL)
	{
	eg = new UIElementGraph(*wm->GetDriver(), Rectangle(50, 150, 750, 350), *buf, "Test Graph", eUITextFont::AntiAliasFont28, Color::White,
	1, Color::DarkBlue, Color::Gray, UIElementGraph::eGraphType::BarGraph);
	wm->RegisterElement(eg);
	}
	wm->Update();
	*/
	GD.swap();
	return;

	if (!updated)
	{
		Serial.write("Before");
		FT8XXDriver tft(800, 480);
		testPrimitives(tft);
		updated = true;
	}
}


