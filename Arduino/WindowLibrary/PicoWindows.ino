/*
 Name:		WindowLibrary.ino
 Created:	4/24/2017 8:33:23 PM
 Author:	rohme
 Editor:	http://www.visualmicro.com
*/
#include <utility.h>
#include <unwind-cxx.h>
#include <system_configuration.h>
#include <StandardCplusplus.h>
#include "Options.h"
#include "Driver\DriverBase.h"
#include "Driver\RA8875Driver.h"
#include "UIElements\ControlDisplay\Button.h"
#include "UIElements\ControlDisplay\CheckBox.h"
#include "UIElements\ControlDisplay\DropDownList.h"
#include "UIElements\ControlDisplay\ProgressBar.h"
#include "UIElements\ControlDisplay\RadioButton.h"
#include "UIElements\ControlDisplay\Slider.h"
#include "UIElements\ControlDisplay\NumericEntryRA8875.h"
#include "UIElements\ControlDisplay\TextEntryRA8875.h"
#include "UIElements\ControlDisplay\RingMeter.h"
#include "UIElements\ControlDisplay\Window.h"
#include "UIElements\UIButton.h"
#include "Utility\Logger.h"
#include "Utility\Color.h"

bool updated = false;
uint8_t prog = 0;
uint32_t runTime = millis();
int reading = 0;

int d = 0;

RA8875Driver lcd;
// the setup function runs once when you press reset or power the board
void setup() {	
}

void TextEntry()
{
	TextEntry::Draw(lcd, TextEntry::eKeyboardState::normal, 0, 0, Color::Gray204, Color::Gray128, Color::White, eUITextFont::AileronRegular12, "Some Text To Edit");
}

void ControlPage1()
{
	Button::Draw(lcd, true, 50, 50, 200, 100, Color::White, Color::Red
		, eUITextFont::AileronRegular12, "Button", true);
	Button::Draw(lcd, false, 300, 50, 200, 100, Color::Red, Color::Yellow
		, eUITextFont::AileronRegular12, "Button Two", true);
	CheckBox::Draw(lcd, false, false, 50, 200, Color::Black, Color::White
		, Color::Red, eUITextFont::AileronRegular12, "Not Checked");
	CheckBox::Draw(lcd, false, true, 275, 200, Color::Black, Color::White
		, Color::Red, eUITextFont::AileronRegular12, "Checked");
	updated = true;
	RadioButton::Draw(lcd, false, false, 50, 175, Color::White, Color::White, Color::Black,
		eUITextFont::AileronRegular12, "Unchecked Radio");
	RadioButton::Draw(lcd, false, true, 275, 175, Color::White, Color::White, Color::Black,
		eUITextFont::AileronRegular12, "Checked Radio");
	std::vector<std::string> dropDownItems;
	dropDownItems.push_back("Item #1");
	dropDownItems.push_back("Item #2");
	dropDownItems.push_back("Item #3");
	dropDownItems.push_back("Item #4");
	dropDownItems.push_back("Item #5");
	DropDownList::Draw(lcd, 50, 235, 125, 20, Color::Black, Color::White, Color::White, 255, 4, eUITextFont::AileronRegular12,
		dropDownItems, 0, true);

	DropDownList::DrawExpanded(lcd, 275, 235, 125, 20, Color::Black, Color::White, Color::White, 255, 4, eUITextFont::AileronRegular12,
		dropDownItems, 0, true);
	ProgressBar::Draw(lcd, 50, 400, 300, 30, 75, RA8875_WHITE, Color::Red,
		Color::Green, eUITextFont::AileronRegular12, true, 4, 255);

	Slider::Draw(lcd, 50, 285, 125, 30, Color::Black, Color::White, Color::Orange, eUITextFont::AileronRegular12,
		50, 0, 100);
}

void WindowTest()
{
	Window::Draw(lcd, 0, 0, 400, 240, Color::White, Color::Yellow, Color::Green, Color::White, Color::Black, "Test Window", eUITextFont::AileronRegular12, true, true, true, true, 4, 255);	
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	if (!updated)
	{
		lcd.Init(800, 480);
		WindowTest();
	}
	updated = true;
}

/*

// Library only supports hardware SPI at this time
// Connect SCLK to UNO Digital #13 (Hardware SPI clock)
// Connect MISO to UNO Digital #12 (Hardware SPI MISO)
// Connect MOSI to UNO Digital #11 (Hardware SPI MOSI)
#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9

Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);
uint16_t tx, ty;

void setup()
{
	Serial.begin(9600);
	Serial.println("RA8875 start");

	if (!tft.begin(RA8875_800x480)) {
		Serial.println("RA8875 Not Found!");
		while (1);
	}

	Serial.println("Found RA8875");

	tft.displayOn(true);
	tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
	tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
	tft.PWM1out(255);

	// With hardware accelleration this is instant
	tft.fillScreen(RA8875_WHITE);

	// Play with PWM
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

	// Try some GFX acceleration!
	tft.drawCircle(100, 100, 50, RA8875_BLACK);
	tft.fillCircle(100, 100, 49, RA8875_GREEN);

	tft.fillRect(11, 11, 398, 198, RA8875_BLUE);
	tft.drawRect(10, 10, 400, 200, RA8875_GREEN);
	tft.fillRoundRect(200, 10, 200, 100, 10, RA8875_RED);
	tft.drawPixel(10, 10, RA8875_BLACK);
	tft.drawPixel(11, 11, RA8875_BLACK);
	tft.drawLine(10, 10, 200, 100, RA8875_RED);
	tft.drawTriangle(200, 15, 250, 100, 150, 125, RA8875_BLACK);
	tft.fillTriangle(200, 16, 249, 99, 151, 124, RA8875_YELLOW);
	tft.drawEllipse(300, 100, 100, 40, RA8875_BLACK);
	tft.fillEllipse(300, 100, 98, 38, RA8875_GREEN);
	// Argument 5 (curvePart) is a 2-bit value to control each corner (select 0, 1, 2, or 3)
	tft.drawCurve(50, 100, 80, 40, 2, RA8875_BLACK);
	tft.fillCurve(50, 100, 78, 38, 2, RA8875_WHITE);



	tft.touchEnable(true);

	Serial.print("Status: "); Serial.println(tft.readStatus(), HEX);
	Serial.println("Waiting for touch events ...");
}

void loop()
{
	float xScale = 1024.0F / tft.width();
	float yScale = 1024.0F / tft.height();

	if (!digitalRead(RA8875_INT))
	{
		if (tft.touched())
		{
			Serial.print("Touch: ");
			tft.touchRead(&tx, &ty);
			Serial.print(tx); Serial.print(", "); Serial.println(ty);
			tft.fillCircle((uint16_t)(tx / xScale), (uint16_t)(ty / yScale), 4, RA8875_WHITE);
		}
	}
}
*/