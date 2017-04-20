#pragma once
#include "DeviceBase.h"
#include "SensorLib.h"
#include "../../RobotLib/RobotLib.h"
#include "5x7FontFull.h"
#include "5x7FontNoGlyphs.h"
#include "ST7565Defines.h"
#include "../../RobotLib/DeviceRegistry.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <algorithm>

/************************************************************************/
/* Rpi-ST7565 LCD Connection with 40pin RpiB+ or 26pin RpiB             */
/************************************************************************/

/*
    Rpi Connector      ST7565 LCD
    ------------------------------
    3.3v (Pin01)     - LCD Back A
    GND  (Pin09)     - LCD Back K
    GND  (Pin06)     - GND
    3.3V (Pin17)     - VCC
    GPIO10(SPI_MOSI) - SID
    GPIO11(SPI_CLK)  - SCLK
    GPIO24           - A0
    GPIO25           - nRST
    GPIO08(SPI_CE0N) - nCS   */

/************************************************************************/

class ST7565 : public DeviceBase
{
public:
	ST7565(RobotLib *robotLib);
	ST7565(RobotLib *robotLib, int8_t SID, int8_t SCLK, int8_t A0, int8_t RST, int8_t CS, bool fullfont);
	~ST7565();

	std::string getDeviceName()
	{
		return "ST7565";
	}

	bool isConnected();
	bool isAvailable();
	device_type_t getDeviceType()
	{
		return device_type_t::DEVICETYPE_OUTPUT;
	}
	void setPartialUpdateMode(bool mode)
	{
		partialUpdateEnabled = mode;
	}
	void setBrightness(uint8_t val);
	void clearDisplay(void);
	void clear();
	void display();
	uint8_t getpixel(uint8_t x, uint8_t y);
	void setpixel(uint8_t x, uint8_t y, uint8_t color);
	void fillcircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);
	void drawcircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);
	void drawrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
	void fillrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
	void drawline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
	void drawchar(uint8_t x, uint8_t line, char c);
	void drawstring(uint8_t x, uint8_t line, char *c);
	void drawstring_P(uint8_t x, uint8_t line, const char *c);
	void drawbitmap(uint8_t x, uint8_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color);
	static device_status_t getDeviceStatus(RobotLib *robotLib)
	{
		// We cant interrogate SPI like we can I2C and there is no output from the ST7565
		return device_status_t::DEVICE_UNKNOWN;
	}
private:
	void initialize(int8_t SID, int8_t SCLK, int8_t A0, int8_t RST, int8_t CS, bool fullfont);
	void cmd(uint8_t c);
	void spiWrite(uint8_t c);
	void data(uint8_t c);
	void updateBoundingBox(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax);
	void isetpixel(uint8_t x, uint8_t y, uint8_t color);

	bool partialUpdateEnabled, fullfont;
	uint8_t sid, sclk, a0, rst, cs;
	int spiFD = 0;
	uint8_t xUpdateMin, xUpdateMax, yUpdateMin, yUpdateMax;
};
