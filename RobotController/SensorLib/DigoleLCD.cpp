#include "DigoleLCD.h"

DigoleLCD::DigoleLCD(RobotLib *robotLib)
	: DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	i2cAddr = 0x27;
	initialize(320,240);
}

DigoleLCD::DigoleLCD(RobotLib *robotLib, uint8_t i2cAddr)
	: DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	this->i2cAddr = i2cAddr;
	initialize(320, 240);
}

DigoleLCD::DigoleLCD(RobotLib *robotLib, uint8_t i2cAddr, int width, int height)
	: DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	this->i2cAddr = i2cAddr;
	initialize(width, height);
}

void DigoleLCD::initialize(int width, int height)
{
	i2cfd = DeviceManager::getI2CFD(i2cAddr);
	if (i2cfd < 0)
	{
		robotLib->LogWarn("Couldnt connect to I2C address");
		initialized = false;
		return;
	}
	
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

bool DigoleLCD::writeCmd(std::string command)
{
	for (int a = 0; a < command.size(); a++)
	{
		if (wiringPiI2CWrite(i2cfd, command[a]) == -1)
		{
			robotLib->LogError("Error writing to I2C Bus");
			return false;
		}			
	}
	
	return true;
}

bool DigoleLCD::setRotation(eDrawRot rotation)
{
	std::string cmd;
	switch (rotation)
	{		
		case(eDrawRot::rot0):
			{
				cmd = "SD0";
				break;
			}
		case(eDrawRot::rot90):
			{
				cmd = "SD1";
				break;
			}
		case(eDrawRot::rot180):
			{
				cmd = "SD2";
				break;
			}
		case(eDrawRot::rot270):
			{
				cmd = "SD3";
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

bool DigoleLCD::writeInt(int value)
{
	std::stringstream ss;	
	if (value > 255)
	{
		ss << 255;
		if (!writeCmd(ss.str()))
			return false;
		ss.clear();
		value -= 255;
	}
	ss << value;
	return writeCmd(ss.str());
}

bool DigoleLCD::setColor(uint8_t color)
{
	std::stringstream ss;
	ss << "SC" << color;
	return writeCmd(ss.str());
}

bool DigoleLCD::setTrueColor(uint8_t r, uint8_t g, uint8_t b)
{
	if (!writeCmd("ESC"))
		return false;
	if (!writeInt(r))
		return false;
	if (!writeInt(g))
		return false;
	if (!writeInt(b))
		return false;
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
	
	if (y>lcdHeight)
	{
		std::stringstream ss;
		ss << y << " > lcdHeight: " << lcdHeight;
		robotLib->LogError(ss.str());
		return false;
	}
	
	if (!writeCmd("FR"))
	{
		return false;
	}
	if (!writeInt(x))
		return false;
	if (!writeInt(y))
		return false;
	if (!writeInt(x + width))
		return false;
	if (!writeInt(y + height))
		return false;
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
	
	if (!writeCmd("DR"))
		return false;
	if (!writeInt(x))
		return false;
	if (!writeInt(y))
		return false;
	if (!writeInt(x + width))
		return false;
	if (!writeInt(y + height))
		return false;
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
	if (!writeInt(x))
		return false;
	if (!writeInt(y))
		return false;
	if (!writeInt(radius))
		return false;
	if (!writeCmd(fStr))
		return false;		
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
	if (!writeCmd("DP"))
		return false;
	if (!writeInt(x))
		return false;
	if (!writeInt(y))
		return false;
	if (!writeInt(color))
		return false;
	return true;
}

bool DigoleLCD::drawLine(int x, int y, int x1, int y1)
{
	if (x1 < 0)
	{
		robotLib->LogError("X1<0");
		return false;
	}
	if (y1 < 0)
	{
		robotLib->LogError("Y1<0");
		return false;
	}
	if (x1 > lcdWidth)
	{
		std::stringstream ss;
		ss << x1 << " > lcdWidth: " << lcdWidth;
		robotLib->LogError(ss.str());
		return false;
	}
	
	if (y1 > lcdHeight)
	{
		std::stringstream ss;
		ss << y1 << " > lcdHeight: " << lcdHeight;
		robotLib->LogError(ss.str());
		return false;
	}
	
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
	if (!writeCmd("LN"))
		return false;
	if (!writeInt(x))
		return false;
	if (!writeInt(y))
		return false;
	if (!writeInt(x1))
		return false;
	if (!writeInt(y1))
		return false;
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
	if (!writeCmd("LT"))
		return false;
	if (!writeInt(x))
		return false;
	if (!writeInt(y))
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
	if (!writeInt(0))
		return false;
	if (!writeCmd("TRT"))
		return false;
	return true;
}

bool DigoleLCD::setFont(uint8_t font)
{
	if (!writeCmd("SF"))
		return false;
	if (!writeInt(font))
		return false;
	return true;
}

bool DigoleLCD::directCommand(uint8_t cmd)
{
	if (!writeCmd("MCD"))
		return false;
	if (!writeInt(cmd))
		return false;
	return true;
}

bool DigoleLCD::directData(int data)
{
	if (!writeCmd("MCT"))
		return false;
	if (!writeInt(data))
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
	
	if (!writeCmd("MA"))
	{
		return false;
	}
	if(!writeInt(x0))
	{
		return false;
	}
	if (!writeInt(y0))	
	{
		return false;
	}
	if (!writeInt(x1))	
	{
		return false;
	}
	if (!writeInt(y1))	
	{
		return false;
	}
	if (!writeInt(xoffset))	
	{
		return false;
	}
	if (!writeInt(yoffset))	
	{
		return false;
	}
	return true;
}

bool DigoleLCD::uploadStartScreen(int lon, uint8_t *data, int xdelay)
{
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
		if (!writeInt(c))
		{
			return false;
		}		
	}
	return true;
}

bool DigoleLCD::uploadUserFont(int lon, uint8_t *data, uint8_t sect)
{
	uint8_t c;
	if (!writeCmd("SUF"))
	{
		return false;		
	}
	if (!writeInt(sect))
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
	
	for (int j = 0; j < lon; j++)
	{
		if ((j % 32) == 0)
		{
			delay(10);
		}
		else
		{
			delay(2);
		}
		c = *(data + j);
		if (!writeInt(c))
		{
			return false;
		}
	}
	return true;
}

bool DigoleLCD::clearScreen()
{
	if (!writeCmd("C"))
	{
		return false;
	}
	if (!writeCmd("L"))
	{
		return false;
	}
	if (!writeInt(0))
	{
		return false;
	}
	if (!writeCmd("C"))
	{
		return false;
	}
	if (!writeCmd("L"))
	{
		return false;
	}
	if (!writeInt(0))
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

bool DigoleLCD::setTextPosBack()
{
	if (!writeCmd("ETB"))
		return false;
	return true;
}

bool DigoleLCD::setTextPosOffset(int xoffset, int yoffset)
{
	if (!writeCmd("ETC"))
		return false;
	std::stringstream s;
	s << xoffset;
	if (!writeCmd(s.str()))
		return false;
	s.clear();
	s << yoffset;
	if (!writeCmd(s.str()))
		return false;
	return true;
}

bool DigoleLCD::setTextPosAbs(int x, int y)
{
	if (!writeCmd("ETP"))
		return false;
	if (!writeInt(x))
		return false;
	if (!writeInt(y))
		return false;
	return true;
}

bool DigoleLCD::setLinePattern(uint8_t pattern)
{
	if (!writeCmd("SLP"))
		return false;
	if (!writeInt(pattern))
		return false;
	return true;	
}

bool DigoleLCD::setPrintPos(int x, int y, ePosMode mode)
{
	if (mode == ePosMode::Text)
	{
		if (!writeCmd("TP")) 
			return false;
	}
	else
	{
		if (!writeCmd("GP"))
			return false;
	}
	if (!writeInt(x))
		return false;
	if (!writeInt(y))
		return false;
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
	if (!writeCmd("TT"))
		return false;
	if (!writeCmd(text))
		return false;
	if (!writeInt(0))
		return false;
	return true;
}

bool DigoleLCD::writeString(int x, int y, std::string text)
{
	if (!setTextPosOffset(x, y))
		return false;
	if (!writeText(text))
		return false;
	return true;
}

bool DigoleLCD::drawBitmap(int x, int y, int w, int h, const uint8_t *bitmap)
{
	uint8_t i = 0;
	int j;
	if ((w & 7 != 0))
		i = 1;
	if (!writeCmd("DIM"))
		return false;
	if (!writeInt(x))
		return false;
	if (!writeInt(y))
		return false;
	if (!writeInt(w))
		return false;
	if (!writeInt(h))
		return false;
	for (j = 0; j < h * ((w >> 3) + i); j++)
	{
		if(!writeInt(*(bitmap + j)))
			return false;
	}
}

bool DigoleLCD::drawBitmap(int x, int y, int w, int h, const uint8_t *bitmap, uint8_t c)
{
	uint8_t i = 0;
	int j;
	if (c != 0)
		c = 0xff;
	if ((w & 7 != 0))
		i = 1;
	if (!writeCmd("DIM"))
		return false;
	if (!writeInt(x))
		return false;
	if (!writeInt(y))
		return false;
	if (!writeInt(w))
		return false;
	if (!writeInt(h))
		return false;
	for (j = 0; j < h * ((w >> 3) + i); j++)
	{
		if(!writeInt(*((bitmap + j))^c))
			return false;
	}
	return true;
}

bool DigoleLCD::printxy(int x, int y, std::string text)
{
	if (!setPrintPos(x, y, ePosMode::Text))
		return false;
	if (!writeCmd("TT"))
		return false;
	if (!writeCmd(text))
		return false;
	if (!writeInt(0))
		return false;
	return true;	
}

bool DigoleLCD::printxy_abs(int x, int y, std::string text)
{
	if (!setTextPosAbs(x, y))
		return false;
	if (!writeCmd("TT"))
		return false;
	if (!writeCmd(text))
		return false;
	if (!writeInt(0))
		return false;
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
	if (!writeCmd("RPNXYI"))
	{
		return Point(-1,-1);
	}
	int x, y;
	int c = wiringPiI2CRead(i2cfd);
	c <<= 8;
	c |= wiringPiI2CRead(i2cfd);
	x = c;
	c = wiringPiI2CRead(i2cfd);
	c <<= 8;
	c |= wiringPiI2CRead(i2cfd);
	y = c;
	if (x > 0 && x<lcdWidth && y>0 && y < lcdHeight)
		return Point(x, y);
	return Point(-1, -1);
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(DigoleLCD);