#pragma once
#include "../Options.h"

#ifdef FT8XX
#include "DriverBase.h"
#include "../Utility/Logger.h"
#include "../External/GD3/GD3.h"

class FT8XXDriver : public DriverBase
{
	FT8XXDriver();
	FT8XXDriver(uint16_t width, uint16_t height, uint8_t cs = 10, uint8_t rst = 9);
	void Init(uint16_t width, uint16_t height, uint8_t cs = 10, uint8_t rst = 9) override;
	void drawPixel(int16_t x, int16_t y, uint32_t color) override;
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color) override;
	void setRotation(eDisplayRotation rotation) override;
	void invertDisplay() override;
	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color) override;
	void fillScreen(uint32_t color) override;
	void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color) override;
	void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color, uint8_t lineWidth);	
	void drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color) override;
	void drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color, uint8_t lineWidth);
	void fillCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color) override;
	void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint32_t color) override;
	void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint32_t color, uint8_t lineWidth);
	void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint32_t color) override;
	void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
		int16_t radius, uint32_t color) override;
	void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
		int16_t radius, uint32_t color, uint8_t lineWidth);
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
	
	// Backlight
	void backlightOn(bool value) override;
	void backlightPower(uint8_t value) override;

	// Touch screen
	void touchEnable(bool value) override;
	bool touched() override;
	bool touchRead(uint16_t *x, uint16_t *y) override;

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

	// FT8XX Driver specific functions
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color, uint8_t lineWidth);
	~FT8XXDriver();
private:
	uint8_t currentFont = 31;
};

#endif