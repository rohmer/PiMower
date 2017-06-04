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
#include "Driver\RA8875Driver.h"
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
#include "UIElements\UIPages\ScreenSaver.h"
#include "UIElements\UIPages\HomeScreen.h"

#include "WindowManager\WindowManager.h"

bool updated = false;
uint8_t prog = 0;
uint32_t runTime = millis();
int reading = 0;
std::string val = "0";
int d = 0;
WindowManager *wm=NULL;
UIWindow *win = NULL;
ScreenSaver *ss = NULL;
HomeScreen *hs = NULL;
UIButton *settings = NULL;
FT8XXDriver tft(800, 480);

// the setup function runs once when you press reset or power the board
void setup() {	
	wm = WindowManager::instance(10, 9, 11, 13, 12, eLCDSizes::lcd800x480);		
}

void testPrimitives(DriverBase &tft)
{	
	tft.clearScreen();
	UIPrimitives::CircleFlat(tft, Color::Red, 255, 20, 20, 15);
	UIPrimitives::CircleRaised(tft, Color::Yellow, 255, 40, 20, 15);
	UIPrimitives::CircleSunken(tft, Color::Blue, 255, 60, 20, 15);
	UIPrimitives::FlatPanel(tft, 100, 20, 20, 20, 0, Color::Aqua);
	UIPrimitives::RaisedPanel(tft, 130, 20, 20, 20, 0, Color::White);
	UIPrimitives::SunkenPanel(tft, 160, 20, 20, 20, 0, Color::Yellow);
	UIPrimitives::Text(tft, Color::White, 255, 20, 40, eUITextFont::AntiAliasFont30, true, "Test Text");
	UIButton *uiButton=new UIButton(tft,Rectangle(50, 100, 270, 150), "Settings", eUITextFont::AntiAliasFont29,
		Color::LightGray, 1, Color::DarkGray, 0, true, true, "SettingsButton", 255, eVertAlign::Top);
	uiButton->Update();
	NumericEntry::Draw(tft, 0, 0, Color::Gray, Color::Black, Color::White, eUITextFont::AntiAliasFont30, val, true, 3);
	tft.swapDisplay();
	updated = true;
}

void testSpecialButtons()
{
	FT8XXDriver tft(800, 480);
	tft.clearScreen();
	SettingsButton *settingsButton = new SettingsButton(tft, Rectangle(535, 325, 785, 465));
	settingsButton->Update();
	tft.swapDisplay();
}
// the loop function runs over and over again until power down or reset
void loop() 
{	
	if(!updated)
		testPrimitives(tft);
	uint16_t x;
	uint16_t y;
	bool complete;
	tft.touchRead(&x, &y);
	if(x>=0 && y>=0 && x<=800 && y<=800)
		val=NumericEntry::ProcessTouch(tft, val, 0, 0, Point(x,y), complete, true);
	NumericEntry::Draw(tft, 0, 0, Color::Gray, Color::Black, Color::White, eUITextFont::AntiAliasFont30, val, true, 3);
	tft.swapDisplay();

	return;
	if(!wm)
		wm = WindowManager::instance(10, 9, 11, 13, 12, eLCDSizes::lcd800x480);
    if (!hs)
	{
		hs= new HomeScreen(*wm->GetDriver());
		wm->RegisterElement(hs);
	}


	wm->Update();	
	updated = true;
}



