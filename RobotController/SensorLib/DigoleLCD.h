#pragma once
#include <vector>
#include <sstream>
#include <errno.h>
#include <string.h>
#include <string>
#include <cmath>
#include <thread>
#include <sstream>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "../../RobotLib/DeviceRegistry.h"
#include "../../RobotLib/RobotLib.h"
#include "../../RobotLib/Point.h"
#include "DeviceBase.h"
#include <vector>
#include "../../3rdParty/wiringPi/wiringPi/wiringPiI2C.h"


/* Driver for Digole LCD */
class DigoleLCD : public DeviceBase
{
public:
	enum eDrawRot
	{
		rot0,
		rot90,
		rot180,
		rot270
	};
	
	enum eDrawMode
	{
		Copy,
		Not,
		And,
		Xor,
		Overwrite			
	};
	
	enum ePosMode
	{
		Text,
		Graphics
	};
	
	enum eOrientation
	{
		Portrait,
		Landscape
	};
	
	DigoleLCD(RobotLib *robotLib);
	DigoleLCD(RobotLib *robotLib, uint8_t i2cAddr);
	DigoleLCD(RobotLib *robotLib, uint8_t i2cAddr, int width, int height);
	~DigoleLCD();	
	device_type_t getDeviceType() override
	{
		return device_type_t::DEVICETYPE_IO;
	}
	std::string getDeviceName() override
	{
		return "DigoleLCD";
	}
	std::string getDeviceDescription() override
	{
		return "Digole LCD Module with touch screen";
	}
	static device_status_t getDeviceStatus(RobotLib *robotLib) 
	{
		// We cant really autodetect this
		return device_status_t::DEVICE_UNKNOWN;
	}		
	
	bool setRotation(eDrawRot rotation);
	bool setContrast(uint8_t contrast);
	bool displayStartScreen(uint8_t screenNum);
	bool setColor(uint8_t color);
	bool setTrueColor(uint8_t r, uint8_t g, uint8_t b);
	bool drawBox(int x, int y, int w, int h);
	bool drawBoxFill(int x, int y, int w, int h);
	bool drawFrame(int x, int y, int w, int h);
	bool clearobd();
	bool drawCircle(int x, int y, int radius, bool filled);
	bool setPixel(int x, int y, int color);
	bool drawLine(int x, int y, int x1, int y1);
	bool drawLineTo(int x, int y);
	bool drawHLine(int x, int y, int width);
	bool drawVLine(int x, int y, int height);
	bool nextTextLine();
	bool setFont(uint8_t font);
	bool directCommand(uint8_t cmd);
	bool directData(int data);
	bool moveArea(int x0, int y0, int x1, int y1, uint8_t xoffset, uint8_t yoffset);
	bool uploadStartScreen(int lon, uint8_t *data, int xdelay);
	bool uploadUserFont(int lon, uint8_t *data, uint8_t sect);
	bool clearScreen();
	bool setDrawMode(eDrawMode mode);
	bool setTextPosBack();
	bool setTextPosOffset(int xoffset, int yoffset);
	bool setTextPosAbs(int x, int y);
	bool setLinePattern(uint8_t pattern);
	bool setPrintPos(int x, int y, ePosMode mode);
	bool disableCursor();
	bool enableCursor();
	bool writeString(int x, int y, std::string text);
	bool drawBitmap(int x, int y, int w, int h, const uint8_t *bitmap);
	bool drawBitmap(int x, int y, int w, int h, const uint8_t *bitmap, uint8_t c);
	bool printxy(int x, int y, std::string text);
	bool printxy_abs(int x, int y, std::string text);
	bool printxyf_abs(int x, int y, uint8_t font, std::string text);
	bool printxyf(int x, int y, uint8_t font, std::string text);
	bool calibrateTouchScreen();
	Point getTouchEvent();
	bool setSleepMode();
	bool backLightBrightness(uint8_t brightness);
	eOrientation getOrientation();
	
private:
	uint8_t i2cAddr, i2cfd;	
	int lcdWidth, lcdHeight;	
	bool initialized = false;
	void initialize(int width, int height);
	bool writeCmd(std::string command);
	bool writeInt(int value);
	void delay(unsigned int len);
	bool writeText(std::string text);
	std::vector<int> fonts = { 0, 6, 10, 18, 51, 120, 123 };
	eOrientation orientation = eOrientation::Landscape;
};
