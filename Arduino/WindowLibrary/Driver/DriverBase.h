#pragma once
#include <string>
#include <cstdint>
#include "../Options.h"
#include "../Utility/Color.h"
#ifdef RA8875
#include "../UIElements/RA8875/Fonts.h"
#endif
#ifdef FT8XX
#include "../UIElements/FT8XX/Fonts.h"
#endif

// The base for all display drivers (Initially RA8875 and FT81x)

enum eDisplayRotation
{
	Landscape				= 0,
	Portrait				= 1,
	LandscapeInverted		= 2,
	PortraitInverted		= 3,
	LandscapeMirrored		= 4,
	LandscapeMirrorInverted = 5,
	PortraitMirrored		= 6,
	PortraitMirroredInveted = 7
};

enum eDriverType
{
	DriverRA8875 = 0,
	DriverFT8XX = 1	
};

class DriverBase
{
public:
	DriverBase(uint16_t width, uint16_t height, eDriverType driverType)
	{
		this->tftWidth = width;
		this->tftHeight = height;
		this->driverType = driverType;
	}

	virtual void Init(uint16_t width, uint16_t height, uint8_t cs = 10, uint8_t rst = 9);
	
	/* Standard functions used by all drivers
	 * Some drivers may have specific functions that they can do beyond these
	 */
	virtual void drawPixel(int16_t x, int16_t y, uint32_t color) = 0;
	virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color)=0;
	virtual void setRotation(eDisplayRotation rotation)=0;
	eDisplayRotation getRotation()
	{
		return rotation;
	}
	bool isLandscape()
	{
		if (rotation == 0 || rotation == 2 || rotation == 4 || rotation == 5)
			return true;
		return false;
	}

	virtual void invertDisplay()=0;
	virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)=0;
	virtual void fillScreen(uint32_t color)=0;
	virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)=0;
	virtual void drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color)=0;
	virtual void fillCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color)=0;
	virtual void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint32_t color) = 0;
	virtual void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint32_t color) = 0;
	virtual void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
		int16_t radius, uint32_t color) = 0;
	virtual void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
		int16_t radius, uint32_t color) = 0;
	virtual void drawChar(int16_t x, int16_t y, unsigned char c, uint32_t color,
		uint16_t bg, uint8_t size) = 0;
	virtual void setCursor(int16_t x, int16_t y) = 0;
	virtual void setTextColor(uint32_t color) = 0;
	virtual void setTextColor(uint32_t color, uint32_t bgColor) = 0;
	virtual void setTextSize(uint8_t s) = 0;
	virtual void getTextBounds(std::string string, int16_t x, int16_t y,
		int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) = 0;
	virtual void drawEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis, 
		int16_t shortAxis, uint32_t color) = 0;
	virtual void fillEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis,
		int16_t shortAxis, uint32_t color) = 0;
	virtual void drawCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis,
		int16_t shortAxis, uint8_t curvePart, uint32_t color) = 0;
	virtual void fillCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis,
		int16_t shortAxis, uint8_t curvePart, uint32_t color) = 0;

	// Power type functions
	virtual void softReset() = 0;
	virtual void displayPower(bool powerMode) = 0;
	virtual void displaySleep(bool sleepModeOn) = 0;

	// Text functions
	virtual void textMode() = 0;
	virtual void setTextCursor(uint16_t x, uint16_t y) = 0;
	virtual void textTransparent(uint32_t foreColor) = 0;
	virtual void textWrite(std::string text) = 0;
	virtual void textWriteLn(std::string text) = 0;

	// Graphics functions
	virtual void graphicsMode() = 0;
	virtual void setXY(uint16_t x, uint16_t y) = 0;
	virtual void pushPixels(uint32_t num, uint32_t color) = 0;

	// Backlight
	virtual void backlightOn(bool value) = 0;
	virtual void backlightPower(uint8_t value) = 0;
	
	// Touch screen
	virtual void touchEnable(bool value) = 0;
	virtual bool touched() = 0;
	virtual bool touchRead(uint16_t *x, uint16_t *y) = 0;

	// Low level functions
	virtual void writeReg(uint8_t reg, uint8_t val) = 0;
	virtual uint8_t readReg(uint8_t reg) = 0;
	virtual void    writeData(uint8_t d) = 0;
	virtual uint8_t readData() = 0;
	virtual void    writeCommand(uint8_t d) = 0;
	virtual uint8_t readStatus() = 0;
	virtual bool waitPoll(uint8_t r, uint8_t f) = 0;
	virtual void fillQuad(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, tColor color, bool triangled = true)=0;
	uint16_t width()
	{
		return tftWidth;
	}
	uint16_t height()
	{
		return tftHeight;
	}

	virtual void textWrite(uint16_t x, uint16_t y, eUITextFont font, uint32_t textColor,
		uint16_t justification, std::string text)=0;

	uint16_t Color565(uint8_t r, uint8_t g, uint8_t b)
	{
		return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
	}

	uint16_t Color24To565(int32_t color_)
	{
		return ((((color_ >> 16) & 0xFF) / 8) << 11) | ((((color_ >> 8) & 0xFF) / 4) << 5) | (((color_) & 0xFF) / 8);
	}

	uint16_t htmlTo565(int32_t color_)
	{
		return (uint16_t)(((color_ & 0xF80000) >> 8) | ((color_ & 0x00FC00) >> 5) | ((color_ & 0x0000F8) >> 3));
	}

	void Color565ToRGB(uint16_t color, uint8_t &r, uint8_t &g, uint8_t &b)
	{
		r = (((color & 0xF800) >> 11) * 527 + 23) >> 6; g = (((color & 0x07E0) >> 5) * 259 + 33) >> 6; b = ((color & 0x001F) * 527 + 23) >> 6;
	}

	uint16_t colorInterpolation565(uint16_t color1, uint16_t color2, uint16_t pos,
		uint16_t div)
	{
		if (pos == 0)
			return color1;
		if (pos >= div)
			return color2;
		uint8_t r1, g1, b1;
		Color565ToRGB(color1, r1, g1, b1);
		uint8_t r2, g2, b2;
		Color565ToRGB(color2, r2, g2, b2);
		return colorInterpolation565(r1, g1, b1, r2, g2, b2, pos, div);
	}

	uint16_t colorInterpolation565(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint16_t pos, uint16_t div)
	{
		if (pos == 0) return Color565(r1, g1, b1);
		if (pos >= div) return Color565(r2, g2, b2);
		float pos2 = (float)pos / div;
		return Color565(
			(uint8_t)(((1.0 - pos2) * r1) + (pos2 * r2)),
			(uint8_t)((1.0 - pos2) * g1 + (pos2 * g2)),
			(uint8_t)(((1.0 - pos2) * b1) + (pos2 * b2))
		);
	}

#ifdef RA8875
	uint16_t getBackgroundColor()
	{
		return backgroundColor;
	}
#else
	uint32_t getBackgroundColor()
	{
		return backgroundColor;
	}
#endif

#ifdef FT8XX
	virtual void swapDisplay();
	virtual void colorA(uint8_t alpha);
	virtual void clearScreen(uint32_t clearToColor = Color::Black);
#endif

protected:
	eDriverType driverType;
	uint16_t tftWidth, tftHeight;
	eDisplayRotation rotation = eDisplayRotation::Landscape;
#ifdef RA8875
	uint16_t backgroundColor;
#else
	uint32_t backgroundColor;
#endif
};