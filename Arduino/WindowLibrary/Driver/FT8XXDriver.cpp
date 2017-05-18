#include "FT8XXDriver.h"
#ifdef FT8XX
FT8XXDriver::FT8XXDriver(uint16_t width, uint16_t height, uint8_t cs = 10, uint8_t rst = 9) :
	DriverBase(width, height,eDriverType::FT8XXDriver)
{
	GD.begin();
#ifdef DEBUG
	Logger::Trace("FT8XXDriver(%d,%d,%d,%d) initalized", width, height, cs, rst);
#endif
}

FT8XXDriver::~FT8XXDriver()
{
}

void FT8XXDriver::drawPixel(int16_t x, int16_t y, uint32_t color)
{
	GD.ColorRGB(color);
	GD.Begin(POINTS);
	GD.Vertex2ii(x, y);	
}

void FT8XXDriver::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color)
{
	GD.ColorRGB(color);
	GD.LineWidth(16);
	GD.Vertex2f(x0, y0);
	GD.Vertex2f(x1, y1);
	GD.swap();
}

void FT8XXDriver::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
	uint32_t color, uint8_t lineWidth)
{
	GD.ColorRGB(color);
	GD.LineWidth(16*lineWidth);
	GD.Vertex2f(x0, y0);
	GD.Vertex2f(x1, y1);
	GD.swap();
}

void FT8XXDriver::setRotation(eDisplayRotation rotation)
{
	this->rotation = rotation;
	switch (rotation)
	{
	case(eDisplayRotation::Landscape):
		GD.cmd_setrotate(0);
		break;
	case(eDisplayRotation::Portrait):
		GD.cmd_setrotate(2);
		break;
	case(eDisplayRotation::LandscapeInverted):
		GD.cmd_setrotate(1);
		break;
	case(eDisplayRotation::PortraitInverted):
		GD.cmd_setrotate(3);
		break;
	case(eDisplayRotation::LandscapeMirrored):
		GD.cmd_setrotate(4);
		break;
	case(eDisplayRotation::LandscapeMirrorInverted):
		GD.cmd_setrotate(5);
		break;
	case(eDisplayRotation::PortraitMirrored):
		GD.cmd_setrotate(6);
		break;
	case(eDisplayRotation::PortraitMirroredInveted):
		GD.cmd_setrotate(7);
		break;
	}
	GD.swap();
}

void FT8XXDriver::invertDisplay()
{
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
	case(eDisplayRotation::LandscapeMirrored):
		setRotation(eDisplayRotation::LandscapeMirrorInverted);
		break;
	case(eDisplayRotation::LandscapeMirrorInverted):
		setRotation(eDisplayRotation::LandscapeMirrored);
		break;
	case(eDisplayRotation::PortraitMirrored):
		setRotation(eDisplayRotation::PortraitInverted);
		break;
	case(eDisplayRotation::PortraitMirroredInveted):
		setRotation(eDisplayRotation::PortraitMirrored);
		break;
	}
}

void FT8XXDriver::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
{
	GD.ColorRGB(color);
	GD.Begin(RECTS);
	GD.Vertex2ii(x, y);
	GD.Vertex2ii(x + w, y + h);
	GD.swap();
}

void FT8XXDriver::fillScreen(uint32_t color)
{
	GD.ClearColorRGB(color);
	GD.Clear();
	GD.swap();
}

void FT8XXDriver::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
{
	GD.Begin(LINE_STRIP);
	GD.ColorRGB(color);
	GD.LineWidth(16);
	GD.Vertex2ii(x, y);
	GD.Vertex2ii(x + w, y);
	GD.Vertex2ii(x + w, y + h);
	GD.Vertex2ii(x, y + h);
	GD.Vertex2ii(x, y);
	GD.swap();
}

void FT8XXDriver::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color, uint8_t lineWidth)
{
	GD.Begin(LINE_STRIP);
	GD.ColorRGB(color);
	GD.LineWidth(16*lineWidth);
	GD.Vertex2ii(x, y);
	GD.Vertex2ii(x + w, y);
	GD.Vertex2ii(x + w, y + h);
	GD.Vertex2ii(x, y + h);
	GD.Vertex2ii(x, y);
	GD.swap();
}

void FT8XXDriver::fillCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color)
{
	GD.Begin(POINTS);
	GD.ColorRGB(color);
	GD.PointSize(16 * r);
	GD.Vertex2ii(x0, y0);
	GD.swap();
}

void FT8XXDriver::drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color)
{
	drawCircle(x0, y0, r, color, 1);
}

void FT8XXDriver::drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color, uint8_t lineWidth)
{
	GD.ColorMask(0, 0, 0, 1);
	GD.BlendFunc(ONE, ONE_MINUS_SRC_ALPHA);
	GD.Begin(POINTS);
	GD.ColorRGB(color);
	GD.PointSize(16 * r);
	GD.Vertex2ii(x0, y0);
	GD.BlendFunc(ZERO, ONE_MINUS_SRC_ALPHA);
	GD.PointSize(16 * (r - lineWidth));
	GD.Vertex2ii(x0, y0);
	GD.ColorMask(1, 1, 1, 0);
	GD.BlendFunc(DST_ALPHA, ONE);
	GD.ColorRGB(0x808080);
	GD.Begin(RECTS); // Visit every pixel on the screen
	GD.Vertex2ii(0, 0);
	GD.Vertex2ii(tftWidth, tftHeight);
	GD.swap();
}

void FT8XXDriver::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
	int16_t x2, int16_t y2, uint32_t color)
{
	drawTriangle(x0, y0, x1, y1, x2, y2, color, 1);
}

void FT8XXDriver::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
	int16_t x2, int16_t y2, uint32_t color, uint8_t lineWidth)
{
	GD.Begin(LINE_STRIP);
	GD.ColorRGB(color);
	GD.LineWidth(16 * lineWidth);
	GD.Vertex2ii(x0, y0);
	GD.Vertex2ii(x1, y1);
	GD.Vertex2ii(x2, y2);
	GD.swap();
}

void FT8XXDriver::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
	int16_t x2, int16_t y2, uint32_t color)
{
	GD.ColorRGB(color);
	Poly poly;
	poly.begin();
	poly.v(16 * x0, 16 * y0);
	poly.v(16 * x1, 16 * y1);
	poly.v(16 * x2, 16 * y2);
	poly.draw();
	GD.swap();
}

void FT8XXDriver::drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
	int16_t radius, uint32_t color)
{
	drawRoundRect(x0, y0, w, h, radius, color, 1);
}

void FT8XXDriver::drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
	int16_t radius, uint32_t color, uint8_t lineWidth)
{
	GD.ColorRGB(color);
	GD.ColorMask(0, 0, 0, 1);
	GD.BlendFunc(ONE, ONE_MINUS_SRC_ALPHA);
	GD.Begin(RECTS);

	GD.LineWidth(radius * 16);
	GD.Vertex2ii(x0, y0);
	GD.Vertex2ii(x0+w, y0+h);
	
	GD.BlendFunc(ZERO, ONE_MINUS_SRC_ALPHA);
	GD.Vertex2f(x0 + lineWidth*16, y0 + lineWidth*16);
	GD.Vertex2f(x0 + w - (lineWidth * 16) * 2, y0 + w - (lineWidth * 16) * 2);
	
	GD.ColorMask(1, 1, 1, 0);
	GD.BlendFunc(DST_ALPHA, ONE);
	GD.ColorRGB(0x808080);
	GD.Begin(RECTS);
	GD.Vertex2ii(0, 0);
	GD.Vertex2ii(tftWidth, tftHeight);
	GD.swap();
}

void FT8XXDriver::fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
	int16_t radius, uint32_t color)
{
	GD.ColorRGB(color);
	GD.LineWidth(radius * 16);
	GD.Begin(RECTS);
	GD.Vertex2ii(x0, y0);
	GD.Vertex2ii(x0+w, y0+h);
	GD.swap();
}

void FT8XXDriver::drawChar(int16_t x, int16_t y, unsigned char c, uint32_t color,
	uint16_t bg, uint8_t size)
{
	GD.ColorRGB(color);
	GD.cmd_text(x, y, currentFont, OPT_CENTER, (char *)&c);
	GD.swap();
}

void FT8XXDriver::setCursor(int16_t x, int16_t y)
{
	// NOOP
}

void FT8XXDriver::setTextColor(uint32_t c)
{
	//NOOP
}

void FT8XXDriver::setTextColor(uint32_t c, uint32_t bg)
{
	//NOOP
}

void FT8XXDriver::setTextSize(uint8_t s)
{
	//NOOP
}
void FT8XXDriver::getTextBounds(std::string str, int16_t x, int16_t y,
	int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h)
{
	// NOOP
}

void FT8XXDriver::drawEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis,
	int16_t shortAxis, uint32_t color)
{
	// NOOP
}
void FT8XXDriver::fillEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis,
	int16_t shortAxis, uint32_t color)
{
	// NOOP
}
void FT8XXDriver::drawCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis,
	int16_t shortAxis, uint8_t curvePart, uint32_t color)
{
	// NOOP
}
void FT8XXDriver::fillCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis,
	int16_t shortAxis, uint8_t curvePart, uint32_t color)
{
	// NOOP
}

void FT8XXDriver::softReset()
{
	GD.cmd_coldstart();
}

void FT8XXDriver::displayPower(bool powerMode)
{
	if (powerMode)
	{
		GD.wr(REG_PWM_DUTY, 128);
		GD.wr(REG_GPIO, 0x80);
		GD.wr(REG_PCLK, 5);
	}
	else
	{
		GD.wr(REG_PWM_DUTY, 0);
		GD.wr(REG_GPIO, 0);
		GD.wr(REG_PCLK, 0);
	}
}

void FT8XXDriver::displaySleep(bool sleepModeOn)
{
	displayPower(sleepModeOn);
}

void FT8XXDriver::backlightOn(bool value)
{
	if (value)
	{
		GD.wr(REG_PWM_DUTY, 128);
	}
	else
	{
		GD.wr(REG_PWM_DUTY, 0);
	}
}

void FT8XXDriver::backlightPower(uint8_t value)
{
	if (value > 128)
		value = 128;
	GD.wr(REG_PWM_DUTY, value);
}

void FT8XXDriver::touchEnable(bool value)
{
	if (true)
	{
		GD.wr(REG_TOUCH_MODE, 0x3);
		GD.wr(REG_TOUCH_ADC_MODE, 0x1);
	}
	else
	{
		GD.wr(REG_TOUCH_MODE, 0x1);
		GD.wr(REG_TOUCH_ADC_MODE, 0x00);
	}
}

bool FT8XXDriver::touched()
{
	GD.get_inputs();
	if (GD.inputs.x == -32768 && GD.inputs.x == -32768)
		return false;
	return true;
}

bool FT8XXDriver::touchRead(uint16_t *x, uint16_t *y)
{
	GD.get_inputs();
	x = ((uint16_t *)&GD.inputs.x);
	y = ((uint16_t *)&GD.inputs.y);
}

void FT8XXDriver::writeReg(uint8_t reg, uint8_t val)
{
	GD.wr16(reg, val);
}
uint8_t FT8XXDriver::readReg(uint8_t reg)
{
	return (uint8_t)GD.rd16(reg);
}

void FT8XXDriver::writeData(uint8_t d)
{
	// NOOP
}

uint8_t FT8XXDriver::readData()
{
	// NOOP
}

void FT8XXDriver::writeCommand(uint8_t d)
{
	GD.cmd32(d);
}

uint8_t FT8XXDriver::readStatus()
{
	// NOOP
	return 0;
}

bool FT8XXDriver::waitPoll(uint8_t r, uint8_t f)
{
	// NOOP
	return true;
}

void FT8XXDriver::textWrite(uint16_t x, uint16_t y, eUITextFont font, uint32_t textColor,
	uint16_t justification, std::string text)
{
	GD.ColorRGB(textColor);
	GD.cmd_text(x, y, font, justification, text.c_str());
	GD.swap();
}
#endif