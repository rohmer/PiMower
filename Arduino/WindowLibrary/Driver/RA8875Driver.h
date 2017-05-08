#pragma once
#include "DriverBase.h"
#include "../Utility/Logger.h"
#include "../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "../Utility/FontHelper.h"

class RA8875Driver : public DriverBase
{
public:
	RA8875Driver(uint16_t width, uint16_t height, 
		uint8_t cs = 10, uint8_t rst = 9);

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

	void virtual textWrite(uint16_t x, uint16_t y, uint32_t textColor, eUITextFont font,
		uint16_t justification, std::string text);

	// RA8875 Specific functions
	inline uint16_t Color565(uint8_t r, uint8_t g, uint8_t b) { return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3); }
	inline uint16_t Color24To565(int32_t color_) { return ((((color_ >> 16) & 0xFF) / 8) << 11) | ((((color_ >> 8) & 0xFF) / 4) << 5) | (((color_) & 0xFF) / 8); }
	inline uint16_t htmlTo565(int32_t color_) { return (uint16_t)(((color_ & 0xF80000) >> 8) | ((color_ & 0x00FC00) >> 5) | ((color_ & 0x0000F8) >> 3)); }
	inline void 	Color565ToRGB(uint16_t color, uint8_t &r, uint8_t &g, uint8_t &b) { r = (((color & 0xF800) >> 11) * 527 + 23) >> 6; g = (((color & 0x07E0) >> 5) * 259 + 33) >> 6; b = ((color & 0x001F) * 527 + 23) >> 6; }	

	~RA8875Driver();

private:
	Adafruit_RA8875 *tft = NULL;
	bool initalized = false;
	
	bool checkInit();
};
