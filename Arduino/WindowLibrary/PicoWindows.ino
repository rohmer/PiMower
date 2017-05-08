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
#include "External\Adafruit_RA8875\Adafruit_RA8875.h"
#include "UIElements\UIElements.h"

void createTheme()
{
}

// the setup function runs once when you press reset or power the board
void setup() {
	/*if (!lcd.begin(RA8875_800x480))
	{
		Serial.println("RA8875 not found");
		while (1);
	}

	Serial.println("Found RA8875");
	lcd.displayOn(true);	
	lcd.GPIOX(true);
	lcd.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
	lcd.PWM1out(128);
	
	lcd.graphicsMode();
	lcd.fillScreen(RA8875_BLACK);
	
	//uiWindow = new UIWindow(lcd, Rectangle(50, 50, 350, 350), eUITextFont::AileronLight12, "Test Window!", true, true, true, false, true);
	//rButton1 = new UIRadioButton(lcd, Rectangle(10, 10, 0, 0), "Checked Button", true, eUITextFont::AileronBlack12, Color::White, 2, Color::White, Color::Yellow);
	//rButton2 = new UIRadioButton(lcd, Rectangle(10, 50, 0, 0), "Button", false, eUITextFont::AileronBlack12, Color::White, 1, Color::White, Color::LightGreen);
	//button = new UIButton(lcd, Rectangle(50, 50, 300, 150), "Test Button!", eUITextFont::AileronBlack12,RA8875_WHITE, 2,Color::DarkGoldenrod, RA8875_WHITE, 4, Color::Goldenrod, Color::Aqua, Color::Gray, 4, Color::Gray, 4, false, true, 6);
	//cb1 = new UICheckBox(lcd, Rectangle(400, 100, 0, 0), "Checked Box!", true, eUITextFont::AileronBoldItalic12, RA8875_WHITE, 3, RA8875_WHITE, Color::DarkGray, 4, 3, RA8875_RED, true, 4);
	//editor = new UIAlphaNumericEditor(lcd, "", eUITextFont::AileronRegular12, RA8875_BLACK, Color::DarkGray, RA8875_WHITE, 2, Color::Black, 4,3);
	//image = new UIImage(lcd, Rectangle(100, 100, 63, 34), Battery15pct);
	batteryIcon = new BatteryIcon(lcd, Rectangle(10, 10, 790, 470), 100, true);
	*/
}

// the loop function runs over and over again until power down or reset
void loop() {
	/*uiWindow->Update();
	//rButton1->Update();
	//rButton2->Update();
	//button->Update();
	//editor->Update();
	//cb1->Update();
	//image->Update();
	batteryIcon->Update();
	*/
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