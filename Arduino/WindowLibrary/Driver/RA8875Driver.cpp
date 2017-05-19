#include "RA8875Driver.h"

RA8875Driver::RA8875Driver() :
	DriverBase(800,480,eDriverType::DriverRA8875)
{	
}

void RA8875Driver::Init(uint16_t width, uint16_t height,
	uint8_t cs = 10, uint8_t rst = 9)
{
	tft = new Adafruit_RA8875(cs, rst);
	RA8875sizes raSize;
	if (width == 480)
	{
		raSize = RA8875sizes::RA8875_480x272;
		Logger::Trace("Size: 480x272");
	}
	else
	{
		if (width == 800)
		{
			raSize = RA8875sizes::RA8875_800x480;
			Logger::Trace("Size: 800x480");
		}
		else
		{
			Logger::Crit("Size must be 800x480 or 480x272, you requested (%d,%d) which is invalid", width, height);
			return;
		}
	}
	if (!tft->begin(raSize))
	{
		Logger::Crit("Failed to find the RA8875, check settings and wiring");
		return;
	}

	// Turn on/setup backlight	
	tft->displayOn(true);
	tft->GPIOX(true);
	tft->PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
	tft->PWM1out(255);
	tft->graphicsMode();


	rotation = eDisplayRotation::Landscape;

#ifdef DEBUG
	Logger::Trace("RA8875Driver(%d,%d,%d,%d) initialized", width, height, cs, rst);
#endif
	initalized = true;
}

RA8875Driver::RA8875Driver(uint16_t width, uint16_t height, uint8_t cs = 10, uint8_t rst = 9) :
	DriverBase(width, height,eDriverType::DriverRA8875)
{
	Init(width, height, cs, rst);	
}

RA8875Driver::~RA8875Driver()
{
	if (tft != NULL)
		delete(tft);
}

bool RA8875Driver::checkInit()
{
	if (!initalized)
	{
		Logger::Trace("RA8875 not initialized");
		return false;
	}
	return true;
}

void RA8875Driver::drawPixel(int16_t x, int16_t y, uint32_t color)
{
	if (!checkInit())
	{
		return;
	}
	uint16_t c = Color24To565(color);
	tft->drawPixel(x, y, c);
}

void RA8875Driver::RA8875Driver::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color)
{
	if(!checkInit())
		return;	
	uint16_t c = Color::Color32To565(color);
	tft->drawLine(x0, y0, x1, y1, c);
}

void RA8875Driver::RA8875Driver::setRotation(eDisplayRotation rotation)
{
	if (!checkInit())
		return;
	this->rotation = rotation;
	switch (rotation)
	{
	case(eDisplayRotation::Landscape):
		tft->setRotation(0);
		break;
	case(eDisplayRotation::Portrait):
		tft->setRotation(1);
		break;
	case(eDisplayRotation::LandscapeInverted):
		tft->setRotation(2);
		break;
	case(eDisplayRotation::PortraitInverted):
		tft->setRotation(3);
		break;
	case(eDisplayRotation::LandscapeMirrored):
		tft->setRotation(0);
		break;
	case(eDisplayRotation::PortraitMirrored):
		tft->setRotation(1);
		break;
	case(eDisplayRotation::LandscapeMirrorInverted):
		tft->setRotation(2);
		break;
	case(eDisplayRotation::PortraitMirroredInveted):
		tft->setRotation(3);
		break;
	}
}

void RA8875Driver::RA8875Driver::invertDisplay()
{
	if (!checkInit())
		return;
	switch (rotation)
	{
	case(eDisplayRotation::Landscape):
		setRotation(eDisplayRotation::LandscapeInverted);
		break;
	case(eDisplayRotation::Portrait):
		setRotation(eDisplayRotation::PortraitInverted);
		break;
	case(eDisplayRotation::LandscapeInverted):
		setRotation(eDisplayRotation::Landscape);
		break;
	case(eDisplayRotation::PortraitInverted):
		setRotation(eDisplayRotation::Portrait);
		break;
	}
}

void RA8875Driver::RA8875Driver::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
{
	if (!checkInit())
		return;
	uint16_t c = Color::Color32To565(color);
	tft->fillRect(x, y, w, h, c);
}

void RA8875Driver::RA8875Driver::fillScreen(uint32_t color)
{
	if (!checkInit())
		return;
	uint16_t c = Color::Color32To565(color);
	tft->fillScreen(c);
}

void RA8875Driver::RA8875Driver::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
{
	if (!checkInit())
		return;
	uint16_t c = Color::Color32To565(color);
	tft->drawRect(x, y, w, h, c);
}

void RA8875Driver::RA8875Driver::drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color)
{
	if (!checkInit())
		return;
	uint16_t c = Color::Color32To565(color);
	tft->drawCircle(x0, y0, r, c);
}

void RA8875Driver::RA8875Driver::fillCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color)
{
	if (!checkInit())
		return;
	uint16_t c = Color::Color32To565(color);
	tft->fillCircle(x0, y0, r, c);
}

void RA8875Driver::RA8875Driver::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
	int16_t x2, int16_t y2, uint32_t color)
{
	if (!checkInit())
		return;
	uint16_t c = Color::Color32To565(color);
	tft->fillTriangle(x0, y0, x1, y1, x2, y2, c);
}

void RA8875Driver::RA8875Driver::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
	int16_t x2, int16_t y2, uint32_t color) 
{
	if (!checkInit())
		return;
	uint16_t c = Color::Color32To565(color);
	tft->drawTriangle(x0, y0, x1, y1, x2, y2, c);
}

void RA8875Driver::RA8875Driver::drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
	int16_t radius, uint32_t color)
{
	if (!checkInit())
		return;
	uint16_t c = Color::Color32To565(color);
	tft->drawRoundRect(x0, y0, w, h, radius, c);
}

void RA8875Driver::RA8875Driver::fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
	int16_t radius, uint32_t color)
{
	if (!checkInit())
		return;
	uint16_t c = Color::Color32To565(color);
	tft->fillRoundRect(x0, y0, w, h, radius, c);
}

void RA8875Driver::RA8875Driver::drawChar(int16_t x, int16_t y, unsigned char c, uint32_t color,
	uint16_t bg, uint8_t size)
{
	if (!checkInit())
		return;
	uint16_t clr = Color::Color32To565(color);
	tft->drawChar(x, y, c, clr, bg, size);
}

void RA8875Driver::RA8875Driver::setCursor(int16_t x, int16_t y)
{
	if (!checkInit())
		return;
	tft->setCursor(x, y);
}

void RA8875Driver::RA8875Driver::setTextColor(uint32_t color)
{
	if (!checkInit())
		return;
	uint16_t c = Color::Color32To565(color);
	tft->setTextColor(c);
}

void RA8875Driver::RA8875Driver::setTextColor(uint32_t color, uint32_t bgColor)
{
	if (!checkInit())
		return;
	tft->setTextColor(Color::Color32To565(color), Color::Color32To565(bgColor));
}

void RA8875Driver::RA8875Driver::setTextSize(uint8_t s)
{
	if (!checkInit())
		return;
	tft->setTextSize(s);
}

void RA8875Driver::RA8875Driver::getTextBounds(std::string str, int16_t x, int16_t y,
	int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h)
{
	if (!checkInit())
		return;	
	char *cstr = new char[str.size() + 1];
	strcpy(cstr, str.c_str());
	tft->getTextBounds(cstr, x, y, x1, y1, w, h);
	delete[] cstr;
}

void RA8875Driver::RA8875Driver::drawEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis,
	int16_t shortAxis, uint32_t color)
{
	if (!checkInit())
		return;
	tft->drawEllipse(xCenter, yCenter, longAxis, shortAxis, Color::Color32To565(color));
}

void RA8875Driver::RA8875Driver::fillEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis,
	int16_t shortAxis, uint32_t color)
{
	if (!checkInit())
		return;
	tft->fillEllipse(xCenter, yCenter, longAxis, shortAxis, Color::Color32To565(color));
}

void RA8875Driver::RA8875Driver::drawCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis,
	int16_t shortAxis, uint8_t curvePart, uint32_t color)
{
	if (!checkInit())
		return;
	tft->drawCurve(xCenter, yCenter, longAxis, shortAxis, curvePart, Color::Color32To565(color));
}

void RA8875Driver::RA8875Driver::fillCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis,
	int16_t shortAxis, uint8_t curvePart, uint32_t color)
{
	if (!checkInit())
		return;
	tft->fillCurve(xCenter, yCenter, longAxis, shortAxis, curvePart, Color::Color32To565(color));
}

void RA8875Driver::RA8875Driver::softReset()
{
	if (!checkInit())
		return;
	tft->softReset();
}

void RA8875Driver::RA8875Driver::displayPower(bool powerMode)
{
	if (!checkInit())
		return;
	tft->displayOn(powerMode);
}

void RA8875Driver::RA8875Driver::displaySleep(bool sleepModeOn)
{
	if (!checkInit())
		return;
	tft->sleep(sleepModeOn);
}

void RA8875Driver::textMode()
{
	if (!checkInit())
		return;
	tft->textMode();
}

void RA8875Driver::setTextCursor(uint16_t x, uint16_t y)
{
	if (!checkInit())
		return;
	tft->setTextColor(x, y);
}

void RA8875Driver::textTransparent(uint32_t foreColor)
{
	if (!checkInit())
		return;
	tft->textTransparent(Color::Color32To565(foreColor));
}

void RA8875Driver::textWrite(std::string text)
{
	if (!checkInit())
		return;
	tft->print(text.c_str());
}

void RA8875Driver::textWriteLn(std::string text)
{
	if (!checkInit())
		return;
	tft->println(text.c_str());
}

void RA8875Driver::graphicsMode()
{
	if (!checkInit())
		return;
	tft->graphicsMode();
}

void RA8875Driver::setXY(uint16_t x, uint16_t y)
{
	if (!checkInit())
		return;
	tft->setXY(x, y);
}

void RA8875Driver::pushPixels(uint32_t num, uint32_t color)
{
	if (!checkInit())
		return;
	tft->pushPixels(num, Color::Color32To565(color));
}

void RA8875Driver::backlightOn(bool value)
{
	if (!checkInit())
		return;
	tft->GPIOX(value);	
}

void RA8875Driver::backlightPower(uint8_t value)
{
	if (!checkInit())
		return;
	tft->PWM1out(value);
}

void RA8875Driver::touchEnable(bool value)
{
	if (!checkInit())
		return;
	tft->touchEnable(value);
}

bool RA8875Driver::touched()
{
	if (!checkInit())
		return(false);
	return tft->touched();
}

bool RA8875Driver::touchRead(uint16_t *x, uint16_t *y)
{
	if (!checkInit())
		return(false);
	return(tft->touchRead(x, y));
}

void RA8875Driver::writeReg(uint8_t reg, uint8_t val)
{
	if (!checkInit())
		return;
	tft->writeReg(reg, val);
}

uint8_t RA8875Driver::readReg(uint8_t reg)
{
	if (!checkInit())
		return(false);
	return (tft->readReg(reg));
}

void RA8875Driver::writeData(uint8_t d)
{
	if (!checkInit())
		return;
	tft->writeData(d);
}

uint8_t RA8875Driver::readData()
{
	if (!checkInit())
		return(false);
	return (tft->readData());
}

void RA8875Driver::writeCommand(uint8_t d)
{
	if (!checkInit())
		return;
	tft->writeCommand(d);
}

uint8_t RA8875Driver::readStatus()
{
	if (!checkInit())
		return(false);
	return (tft->readStatus());
}

bool RA8875Driver::waitPoll(uint8_t r, uint8_t f)
{
	if (!checkInit())
		return(false);
	return (tft->waitPoll(r, f));
}

void RA8875Driver::textWrite(uint16_t x, uint16_t y, eUITextFont font, uint32_t textColor,
		uint16_t justification, std::string text)
{	
	tft->setTextColor(Color::Color32To565(textColor));
	FontHelper::setLCDFont(tft, font);
	// Justification is noop on RA
	tft->setCursor(x, y);
	tft->print(text.c_str());
}

void RA8875Driver::fillQuad(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t color, bool triangled)

{
	fillTriangle(x0, y0, x1, y1, x2, y2, color);
	if (triangled)
		fillTriangle(x2, y2, x3, y3, x0, y0, color);
	fillTriangle(x1, y1, x2, y2, x3, y3,color);	
}

void RA8875Driver::drawQuad(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t color)

{
	drawLine(x0, y0, x1, y1, color);//low 1
	drawLine(x1, y1, x2, y2, color);//high 1
	drawLine(x2, y2, x3, y3, color);//high 2
	drawLine(x3, y3, x0, y0, color);//low 2
}

void RA8875Driver::_triangle_helper(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color, bool filled)
{
	if (x0 >= tftWidth || x1 >= tftWidth || x2 >= tftWidth) return;
	if (y0 >= tftHeight|| y1 >= tftHeight || y2 >= tftHeight) return;
	if (rotation==eDisplayRotation::Portrait ||
		rotation==eDisplayRotation::PortraitInverted ||
		rotation == eDisplayRotation::PortraitMirrored ||
		rotation == eDisplayRotation::PortraitMirroredInveted)
	{ 
		swapvals(x0, y0); 
		swapvals(x1, y1); 
		swapvals(x2, y2); 
	}

	if (x0 == x1 && y0 == y1) {
		drawLine(x0, y0, x2, y2, color);
		return;
	}
	else if (x0 == x2 && y0 == y2) {
		drawLine(x0, y0, x1, y1, color);
		return;
	}
	else if (x0 == x1 && y0 == y1 && x0 == x2 && y0 == y2) {//new
		drawPixel(x0, y0, color);
		return;
	}

	if (y0 > y1) { swapvals(y0, y1); swapvals(x0, x1); }
	if (y1 > y2) { swapvals(y2, y1); swapvals(x2, x1); }
	if (y0 > y1) { swapvals(y0, y1); swapvals(x0, x1); }
	if (y0 == y2) { // Handle awkward all-on-same-line case as its own thing
		int16_t a, b;
		a = b = x0;
		if (x1 < a) {
			a = x1;
		}
		else if (x1 > b) {
			b = x1;
		}
		if (x2 < a) {
			a = x2;
		}
		else if (x2 > b) {
			b = x2;
		}
		drawLine(a, y0, b - a + 1, y0, color);
		return;
	}

	_line_addressing(x0, y0, x1, y1);
	//p2
	writeReg(RA8875_DTPH0, x2 & 0xFF);
	writeReg(RA8875_DTPH0 + 1, x2 >> 8);
	writeReg(RA8875_DTPV0, y2 & 0xFF);
	writeReg(RA8875_DTPV0 + 1, y2 >> 8);
	writeCommand(RA8875_DCR);
	filled == true ? writeData(0xA1) : writeData(0x81);
	waitPoll(RA8875_DCR, RA8875_DCR_LINESQUTRI_STATUS);
}

void RA8875Driver::_line_addressing(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
	//X0
	writeReg(RA8875_DLHSR0, x0 & 0xFF);
	writeReg(RA8875_DLHSR0 + 1, x0 >> 8);
	//Y0
	writeReg(RA8875_DLVSR0, y0 & 0xFF);
	writeReg(RA8875_DLVSR0 + 1, y0 >> 8);
	//X1
	writeReg(RA8875_DLHER0, x1 & 0xFF);
	writeReg(RA8875_DLHER0 + 1, x1 >> 8);
	//Y1
	writeReg(RA8875_DLVER0, y1 & 0xFF);
	writeReg(RA8875_DLVER0 + 1, y1 >> 8);
}