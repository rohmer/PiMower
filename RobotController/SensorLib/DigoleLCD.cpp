#include "DigoleLCD.h"

DigoleLCD::DigoleLCD(RobotLib *robotLib)
	: DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	robotLib->Log("Called single");
	i2cAddr = 0x27;
	initialize(320, 240);
}

DigoleLCD::DigoleLCD(RobotLib *robotLib, uint8_t i2cAddr)
	: DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	robotLib->Log("Called double");
	this->i2cAddr = i2cAddr;
	initialize(320, 240);
}

DigoleLCD::DigoleLCD(RobotLib *robotLib, uint8_t i2cAddr, int width, int height)
	: DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	robotLib->Log("Called triple");
	this->i2cAddr = i2cAddr;
	initialize(width, height);
}

void DigoleLCD::setup(uint8_t i2cAddr)
{
	this->i2cAddr = i2cAddr;
	initialize(320, 240);
}

void DigoleLCD::setup(uint8_t i2cAddr, int width, int height)
{
	this->i2cAddr = i2cAddr;
	initialize(width, height);
}

void DigoleLCD::initialize(int width, int height)
{
	std::stringstream ss;
	ss << "Initializing DigoleLCD (" << width << "," << height << ")";
	robotLib->Log(ss.str());
	i2cfd = DeviceManager::getI2CFD(i2cAddr);
	if (i2cfd < 0)
	{
		robotLib->LogWarn("Couldnt connect to I2C address");
		initialized = false;
		return;
	}
	setRotation(eDrawRot::rot90);
	setColor(LCDColor::WHITE);
	setBackgroundColor(LCDColor::BLACK);
	clearScreen();
	lcdWidth = width;
	lcdHeight = height;
}

DigoleLCD::~DigoleLCD()
{
}

void DigoleLCD::delay(unsigned int len)
{
	struct timespec sleeper, dummy;
	sleeper.tv_sec = (time_t)(len / 1000);
	sleeper.tv_nsec = (long)(len % 1000) * 1000000;
	nanosleep(&sleeper, &dummy);
}

bool DigoleLCD::writeUint(uint8_t c)
{
	if (wiringPiI2CWrite(i2cfd, c) == -1)
	{
		std::stringstream ss;
		ss << "Error writing to (" << i2cfd << ") on I2C bus";
		robotLib->LogError(ss.str());
		return false;
	}
	return true;
}

// Similar to writeCmd, but without the trailing \0
bool DigoleLCD::writeStr(std::string command)
{
	for (int a = 0; a < command.size(); a++)
	{
		if (wiringPiI2CWrite(i2cfd, command[a]) == -1)
		{
			std::stringstream ss;
			ss << "Error writing to (" << i2cfd << ") on I2C bus, cmd: " << command;
			robotLib->LogError(ss.str());
			return false;
		}
	}
	return true;
}

bool DigoleLCD::writeCmd(std::string command)
{
	for (int a = 0; a < command.size(); a++)
	{
		if (wiringPiI2CWrite(i2cfd, command[a]) == -1)
		{
			std::stringstream ss;
			ss << "Error writing to (" << i2cfd << ") on I2C bus, cmd: " << command;
			robotLib->LogError(ss.str());
			return false;
		}
	}
	wiringPiI2CWrite(i2cfd, '\0');
	delay(50);
	return true;
}

bool DigoleLCD::setRotation(eDrawRot rotation)
{
	std::string cmd;
	int tmp;
	switch (rotation)
	{
	case(eDrawRot::rot0):
		{
			cmd = "SD0";
			if (orientation == eOrientation::Portrait)
			{
				lcdHeight = 240;
				lcdWidth = 320;
			}
			orientation = eOrientation::Landscape;
			break;
		}
	case(eDrawRot::rot90):
		{
			cmd = "SD1";
			if (orientation == eOrientation::Landscape)
			{
				lcdHeight = 240;
				lcdWidth = 320;
			}
			orientation = eOrientation::Portrait;
			break;
		}
	case(eDrawRot::rot180):
		{
			cmd = "SD2";
			if (orientation == eOrientation::Portrait)
			{
				lcdHeight = 320;
				lcdWidth = 240;
			}
			orientation = eOrientation::Landscape;
			break;
		}
	case(eDrawRot::rot270):
		{
			cmd = "SD3";
			if (orientation == eOrientation::Landscape)
			{
				lcdHeight = 240;
				lcdWidth = 320;
			}
			orientation = eOrientation::Portrait;
			break;
		}
	}
	return writeCmd(cmd);
}

bool DigoleLCD::setContrast(uint8_t contrast)
{
	std::stringstream ss;
	ss << "CT" << contrast;
	return writeCmd(ss.str());
}

bool DigoleLCD::displayStartScreen(uint8_t screenNum)
{
	std::stringstream ss;
	ss << "DSS" << screenNum;
	return writeCmd(ss.str());
}

std::string DigoleLCD::writeInt(int value)
{
	std::stringstream ss;
	if (value > 255)
	{
		ss << (char)255;
		value -= 255;
	}
	ss << (char)value;
	return ss.str();
}

bool DigoleLCD::setColor(uint8_t color)
{
	std::stringstream ss;
	ss << "SC" << color;
	return writeCmd(ss.str());
}

bool DigoleLCD::setTrueColor(uint8_t r, uint8_t g, uint8_t b)
{
	std::stringstream ss;
	ss << "ESC" << writeInt(r) << writeInt(g) << writeInt(b);
	if (!writeCmd(ss.str()))
	{
		return false;
	}
	return true;
}

bool DigoleLCD::drawBox(int x, int y, int width, int height)
{
	if (x < 0)
	{
		robotLib->LogError("X<0");
		return false;
	}
	if (y < 0)
	{
		robotLib->LogError("Y<0");
		return false;
	}
	if (x > lcdWidth)
	{
		std::stringstream ss;
		ss << x << " > lcdWidth: " << lcdWidth;
		robotLib->LogError(ss.str());
		return false;
	}

	if (y > lcdHeight)
	{
		std::stringstream ss;
		ss << y << " > lcdHeight: " << lcdHeight;
		robotLib->LogError(ss.str());
		return false;
	}

	std::stringstream ss;
	ss << "FR" << writeInt(x) << writeInt(y) << writeInt(x + width) << writeInt(y + height);
	if (!writeCmd(ss.str()))
	{
		return false;
	}
	return true;
}

bool DigoleLCD::drawFrame(int x, int y, int width, int height)
{
	if (x < 0)
	{
		robotLib->LogError("X<0");
		return false;
	}
	if (y < 0)
	{
		robotLib->LogError("Y<0");
		return false;
	}
	if (x > lcdWidth)
	{
		std::stringstream ss;
		ss << x << " > lcdWidth: " << lcdWidth;
		robotLib->LogError(ss.str());
		return false;
	}

	if (y > lcdHeight)
	{
		std::stringstream ss;
		ss << y << " > lcdHeight: " << lcdHeight;
		robotLib->LogError(ss.str());
		return false;
	}
	std::stringstream ss;
	ss << "DR" << writeInt(x) << writeInt(y) << writeInt(x + width) << writeInt(y + height);
	if (!writeCmd(ss.str()))
	{
		return false;
	}

	return true;
}

bool DigoleLCD::drawBoxFill(int x, int y, int width, int height)
{
	if (x < 0)
	{
		robotLib->LogError("X<0");
		return false;
	}
	if (y < 0)
	{
		robotLib->LogError("Y<0");
		return false;
	}
	if (x > lcdWidth)
	{
		std::stringstream ss;
		ss << x << " > lcdWidth: " << lcdWidth;
		robotLib->LogError(ss.str());
		return false;
	}

	if (y > lcdHeight)
	{
		std::stringstream ss;
		ss << y << " > lcdHeight: " << lcdHeight;
		robotLib->LogError(ss.str());
		return false;
	}
	if (!setColor(0))
		return false;
	if (!drawBox(x, y, width, height))
		return false;
	if (!setColor(1))
		return false;
	if (!drawFrame(x, y, width, height))
		return false;
	return true;
}

bool DigoleLCD::clearobd()
{
	if (!setColor(0))
		return false;
	if (!drawBox(0, 0, lcdWidth, lcdHeight))
		return false;
	if (!setColor(1))
		return false;
	return true;
}

bool DigoleLCD::drawCircle(int x, int y, int radius, bool filled)
{
	if (x < 0)
	{
		robotLib->LogError("X<0");
		return false;
	}
	if (y < 0)
	{
		robotLib->LogError("Y<0");
		return false;
	}
	if (x > lcdWidth)
	{
		std::stringstream ss;
		ss << x << " > lcdWidth: " << lcdWidth;
		robotLib->LogError(ss.str());
		return false;
	}

	if (y > lcdHeight)
	{
		std::stringstream ss;
		ss << y << " > lcdHeight: " << lcdHeight;
		robotLib->LogError(ss.str());
		return false;
	}
	std::stringstream ss;
	std::string fStr = "0";
	if (filled)
		fStr = "1";
	if (!writeCmd("CC"))
		return false;

	ss << "CC" << writeInt(x) << writeInt(y) << writeInt(radius) << fStr;
	robotLib->Log(ss.str());
	std::stringstream s;
	s << "rad: " << radius << char(radius);
	robotLib->Log(s.str());
	if (!writeCmd(ss.str()))
	{
		return false;
	}

	return true;
}

bool DigoleLCD::setPixel(int x, int y, int color)
{
	if (x < 0)
	{
		robotLib->LogError("X<0");
		return false;
	}
	if (y < 0)
	{
		robotLib->LogError("Y<0");
		return false;
	}
	if (x > lcdWidth)
	{
		std::stringstream ss;
		ss << x << " > lcdWidth: " << lcdWidth;
		robotLib->LogError(ss.str());
		return false;
	}

	if (y > lcdHeight)
	{
		std::stringstream ss;
		ss << y << " > lcdHeight: " << lcdHeight;
		robotLib->LogError(ss.str());
		return false;
	}
	std::stringstream ss;
	ss << "DP" << writeInt(x) << writeInt(y) << writeInt(color);
	if (!writeCmd(ss.str()))
	{
		return false;
	}
	return true;
}

bool DigoleLCD::drawLine(int x, int y, int x1, int y1)
{
	std::stringstream ss;
	ss << "LN" << writeInt(x) << writeInt(y) << writeInt(x1) << writeInt(y1);
	if (!writeCmd(ss.str()))
	{
		return false;
	}
	return true;
}

bool DigoleLCD::drawLineTo(int x, int y)
{
	if (x < 0)
	{
		robotLib->LogError("X<0");
		return false;
	}
	if (y < 0)
	{
		robotLib->LogError("Y<0");
		return false;
	}
	if (x > lcdWidth)
	{
		std::stringstream ss;
		ss << x << " > lcdWidth: " << lcdWidth;
		robotLib->LogError(ss.str());
		return false;
	}

	if (y > lcdHeight)
	{
		std::stringstream ss;
		ss << y << " > lcdHeight: " << lcdHeight;
		robotLib->LogError(ss.str());
		return false;
	}
	std::stringstream ss;
	ss << "LT" << writeInt(x) << writeInt(y);
	if (!writeCmd(ss.str()))
		return false;
	return true;
}

bool DigoleLCD::drawHLine(int x, int y, int width)
{
	return (drawLine(x, y, x + width, y));
}

bool DigoleLCD::drawVLine(int x, int y, int height)
{
	return (drawLine(x, y, x, y + height));
}

bool DigoleLCD::nextTextLine()
{
	if (!writeCmd("0"))
		return false;
	if (!writeCmd("TRT"))
		return false;
	return true;
}

bool DigoleLCD::setFont(uint8_t font)
{
	std::stringstream ss;
	ss << "SF" << font;
	if (!writeCmd(ss.str()))
		return false;
	return true;
}

bool DigoleLCD::directCommand(uint8_t cmd)
{
	std::stringstream ss;
	ss << "MCD" << cmd;
	if (!writeCmd(ss.str()))
		return false;
	return true;
}

bool DigoleLCD::directData(int data)
{
	std::stringstream ss;
	ss << "MCT" << data;
	if (!writeCmd(ss.str()))
		return false;
	return true;
}

bool DigoleLCD::moveArea(int x0, int y0, int x1, int y1, uint8_t xoffset, uint8_t yoffset)
{
	if (x0 < 0)
	{
		robotLib->LogError("X0 < 0");
		return false;
	}
	if (y0 < 0)
	{
		robotLib->LogError("Y0 < 0");
		return false;
	}
	if (x1 < 0)
	{
		robotLib->LogError("X1 < 0");
		return false;
	}
	if (y1 < 0)
	{
		robotLib->LogError("Y1 < 0");
		return false;
	}

	std::stringstream ss;
	ss << "MA" << writeInt(x0) << writeInt(y0) << writeInt(x1) << writeInt(y1) << writeInt(xoffset) << writeInt(yoffset);
	if (!writeCmd(ss.str()))
	{
		return false;
	}
	return true;
}

//TODO: Fix this
bool DigoleLCD::uploadStartScreen(int lon, uint8_t *data, int xdelay)
{
	/*
	if (!writeCmd("SSS"))
	{
		return false;
	}

	if (!writeInt((uint8_t)(lon % 256)))
	{
		return false;
	}
	if (!writeInt((uint8_t)(lon / 256)))
	{
		return false;
	}
	uint8_t c;
	for (int j = 0; j < lon; j++)
	{
		delay(xdelay);
		c =*(data+j);
		if (!writeCmd(c))
		{
			return false;
		}
	}
	*/
	return true;
}

bool DigoleLCD::uploadUserFont(int len, uint8_t *data, uint8_t sect)
{
	uint8_t u;
	if (!writeStr("SUF"))
		return false;
	if (!writeUint(sect))
		return false;
	u = (len % 256);
	if (!writeUint(u))
		return false;
	u = (len / 256);
	if (!writeUint(u))
		return false;
	for (int a = 0; a < len; a++)
	{
		if ((a % 32) == 0)
		{
			delay(BITMAP_DELAY);
		}
		if (!writeUint(data[a]))
			return false;
	}
	return true;
}

bool DigoleLCD::drawBitmap256K(int x, int y, int w, int h, const uint8_t *bitmap)
{
	std::stringstream ss;
	ss << "EDIM3" << writeInt(x) << writeInt(y) << writeInt(w) << writeInt(h);
	if (!writeStr(ss.str()))
		return false;
	for (int a = 0; (a < h*w * 3); a++)
	{
		if ((a % 1024) == 0)
		{
			delay(BITMAP_DELAY);
		}
		if (!writeUint(bitmap[a]))
			return false;
	}
	return true;
}

bool DigoleLCD::clearScreen()
{
	if (!writeCmd("CL"))
	{
		return false;
	}
	return true;
}

bool DigoleLCD::setDrawMode(eDrawMode mode)
{
	std::string cmd;
	switch (mode)
	{
	case(eDrawMode::Copy):
		cmd = "DMC";
		break;
	case(eDrawMode::And):
		cmd = "DM&";
		break;
	case(eDrawMode::Not):
		cmd = "DM!";
		break;
	case(eDrawMode::Overwrite):
		cmd = "DMO";
		break;
	case(eDrawMode::Xor):
		cmd = "DM^";
		break;
	}
	if (!writeCmd(cmd))
	{
		return false;
	}
	return true;
}

bool DigoleLCD::setTextPos(int x, int y)
{
	std::stringstream ss;
	ss << "TP" << writeInt(x) << writeInt(y);
	return writeCmd(ss.str());
}

bool DigoleLCD::setTextPosBack()
{
	if (!writeCmd("ETB"))
		return false;
	return true;
}

bool DigoleLCD::setTextPosOffset(int xoffset, int yoffset)
{
	std::stringstream s;
	s << "ETP" << writeInt(xoffset) << writeInt(yoffset) << "\n";
	if (!writeCmd(s.str()))
		return false;
	writeCmd("\n");
	return true;
}

bool DigoleLCD::setTextPosAbs(int x, int y)
{
	std::stringstream ss;
	ss << "ETP" << writeInt(x) << writeInt(y);
	if (!writeCmd(ss.str()))
		return false;
	return true;
}

bool DigoleLCD::setLinePattern(uint8_t pattern)
{
	std::stringstream ss;
	ss << "SLP" << pattern;
	if (!writeCmd(ss.str()))
		return false;
	return true;
}

bool DigoleLCD::setPrintPos(int x, int y, ePosMode mode)
{
	std::stringstream ss;
	if (mode == ePosMode::Text)
	{
		ss << "TP";
	}
	else
	{
		ss << "GP";
	}
	ss << writeInt(x) << writeInt(y);
	if (!writeCmd(ss.str()))
	{
		return false;
	}
	return true;
}

bool DigoleLCD::disableCursor()
{
	if (!writeCmd("CS0"))
		return false;
	return true;
}

bool DigoleLCD::enableCursor()
{
	if (!writeCmd("CS1"))
		return false;
	return true;
}

bool DigoleLCD::writeText(std::string text)
{
	std::stringstream ss;
	ss << "TT" << text;
	if (!writeCmd(ss.str()))
		return false;
	return true;
}

bool DigoleLCD::writeStringCP(int x, int y, std::string text)
{
	if (!setTextPos(x, y))
		return false;
	return writeText(text);
}

bool DigoleLCD::writeString(int x, int y, std::string text)
{
	if (!setTextPosOffset(x, y))
		return false;
	if (!writeText(text))
		return false;
	return true;
}

bool DigoleLCD::drawBitmap256(int x, int y, int w, int h, const uint8_t *bitmap)
{
	int j;
	std::stringstream ss;
	ss << "EDIM1" << writeInt(x) << writeInt(y) << writeInt(w) << writeInt(h);
	if (!writeStr(ss.str()))
		return false;
	for (j = 0; j < h*w; j++)
	{
		if ((j % 1024) == 0)
		{
			delay(BITMAP_DELAY);
		}
		if (!writeUint(bitmap[j]))
			return false;
	}
}

bool DigoleLCD::drawBitmap(int x, int y, int w, int h, const uint8_t *bitmap, uint8_t c)
{
	uint8_t i;
	if ((w & 7) != 0)
	{
		i = 1;
	}
	std::stringstream ss;
	ss << "DIM" << writeInt(x) << writeInt(y) << writeInt(w) << writeInt(h);
	if (!writeStr(ss.str()))
		return false;
	for (int a = 0; a < h *((w >> 3) + i); a++)
	{
		if (!writeUint(bitmap[a]))
			return false;
	}
	return true;
}

bool DigoleLCD::printxy(int x, int y, std::string text)
{
	if (!setPrintPos(x, y, ePosMode::Text))
		return false;
	writeText(text);
	return true;
}

bool DigoleLCD::printxy_abs(int x, int y, std::string text)
{
	if (!setTextPosAbs(x, y))
		return false;
	writeText(text);
	return true;
}

bool DigoleLCD::printxyf_abs(int x, int y, uint8_t font, std::string text)
{
	if (!setFont(fonts[font]))
		return false;
	return printxy_abs(x, y, text);
}

bool DigoleLCD::printxyf(int x, int y, uint8_t font, std::string text)
{
	if (!setFont(fonts[font]))
		return false;
	return printxy(x, y, text);
}

bool DigoleLCD::calibrateTouchScreen()
{
	if (!writeCmd("TUCHC"))
		return false;
	return true;
}

Point DigoleLCD::getTouchEvent()
{
	if (!writeCmd("RPNXYC"))
	{
		return Point(-1, -1);
	}
	delay(50);
	int x, y;
	int c = wiringPiI2CRead(i2cfd);
	std::stringstream ss;
	c <<= 8;
	c |= wiringPiI2CRead(i2cfd);
	x = c;
	c = wiringPiI2CRead(i2cfd);
	c <<= 8;
	c |= wiringPiI2CRead(i2cfd);
	y = c;
	ss << x << "," << "y";
	robotLib->Log(ss.str());
	if (x > 0 && x<lcdWidth && y>0 && y < lcdHeight)
		return Point(x, y);
	return Point(-1, -1);
}

bool DigoleLCD::setSleepMode()
{
	if (!writeCmd("DNALL"))
		return false;
	return true;
}

bool DigoleLCD::backLightBrightness(uint8_t brightness)
{
	if (brightness > 100)
		brightness = 100;
	std::stringstream ss;
	ss << "BL" << brightness;
	if (!writeCmd(ss.str()))
		return false;
	return true;
}

DigoleLCD::eOrientation DigoleLCD::getOrientation()
{
	return orientation;
}

bool DigoleLCD::setBackgroundColor(uint8_t color)
{
	std::stringstream ss;
	ss << "BGC" << color;
	return writeCmd(ss.str());
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(DigoleLCD);