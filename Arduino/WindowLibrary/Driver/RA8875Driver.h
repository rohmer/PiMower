#pragma once
#include "DriverBase.h"
#include "../Utility/Logger.h"
#include "../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "../Utility/FontHelper.h"

#define swapvals(a, b) { int16_t t=a; a=b; b=t; }
#define RA8875_DLHSR0         		  0x91//Draw Line/Square Horizontal Start Address Register0
#define RA8875_DLVSR0         		  0x93//Draw Line/Square Vertical Start Address Register0
#define RA8875_DLHER0         		  0x95//Draw Line/Square Horizontal End Address Register0
#define RA8875_DLVER0         		  0x97//Draw Line/Square Vertical End Address Register0
#define RA8875_DTPH0         		  0xA9//Draw Triangle Point 2 Horizontal Address Register0
#define RA8875_DTPV0         		  0xAB//Draw Triangle Point 2 Vertical Address Register0

class RA8875Driver : public DriverBase
{
public:
	RA8875Driver();
	RA8875Driver(uint16_t width, uint16_t height, 
		uint8_t cs = 10, uint8_t rst = 9);

	void Init(uint16_t width, uint16_t height,
		uint8_t cs = 10, uint8_t rst = 9) override;

	eDriverType getDriverType()
	{
		return this->driverType;
	}

	void drawPixel(int16_t x, int16_t y, uint32_t color) override;
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color) override;
	void setRotation(eDisplayRotation rotation) override;
	void invertDisplay() override;
	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color) override;
	void fillScreen(uint32_t color) override;
	void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color) override;
	void drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color) override;
	void fillCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color) override;
	void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint32_t color) override;
	void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint32_t color) override;
	void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
		int16_t radius, uint32_t color) override;
	void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
		int16_t radius, uint32_t color) override;
	void drawChar(int16_t x, int16_t y, unsigned char c, uint32_t color,
		uint16_t bg, uint8_t size) override;
	void setCursor(int16_t x, int16_t y) override;
	void setTextColor(uint32_t c) override;
	void setTextColor(uint32_t c, uint32_t bg) override;
	
	void setTextSize(uint8_t s) override;
	void getTextBounds(std::string str, int16_t x, int16_t y,
		int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) override;
	void drawEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis,
		int16_t shortAxis, uint32_t color) override;
	void fillEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis,
		int16_t shortAxis, uint32_t color) override;
	void drawCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis,
		int16_t shortAxis, uint8_t curvePart, uint32_t color) override;
	void fillCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis,
		int16_t shortAxis, uint8_t curvePart, uint32_t color) override;

	// Power type functions
	void softReset() override;
	void displayPower(bool powerMode) override;
	void displaySleep(bool sleepModeOn) override;

	// Text functions
	void textMode()  override;
	void setTextCursor(uint16_t x, uint16_t y)  override;
	void textTransparent(uint32_t foreColor)  override;
	void textWrite(std::string text)  override;
	void textWriteLn(std::string text)  override;

	// Graphics functions
	void graphicsMode() override;
	void setXY(uint16_t x, uint16_t y) override;
	void pushPixels(uint32_t num, uint32_t color) override;

	// Backlight
	void backlightOn(bool value) override;
	void backlightPower(uint8_t value) override;

	// Touch screen
	void touchEnable(bool value) override;
	bool touched() override;
	bool touchRead(uint16_t *x, uint16_t *y)override;

	// Low level functions
	void writeReg(uint8_t reg, uint8_t val) override;
	uint8_t readReg(uint8_t reg) override;
	void    writeData(uint8_t d) override;
	uint8_t readData() override;
	void    writeCommand(uint8_t d) override;
	uint8_t readStatus() override;
	bool waitPoll(uint8_t r, uint8_t f) override;

	void textWrite(uint16_t x, uint16_t y, eUITextFont font, uint32_t textColor,
		uint16_t justification, std::string text) override;

	void drawQuad(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t color);
	void fillQuad(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t color, bool triangled = true);
	void _triangle_helper(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color, bool filled);
	void _line_addressing(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
	void _writeRegister(const uint8_t reg, uint8_t val);
	~RA8875Driver();

private:
	Adafruit_RA8875 *tft = NULL;
	bool initalized = false;
	
	bool checkInit();
};
