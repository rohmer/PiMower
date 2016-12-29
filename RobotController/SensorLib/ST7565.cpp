#include "ST7565.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPi.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringShift.h"

ST7565::ST7565(RobotLib *robotLib)
	: DeviceBase(robotLib)
{
	if (robotLib->getEmulator())
		return;

	initialize(LCD_SID,LCD_SCK,LCD_A0,LCD_nRST,LCD_nCS,true);	
}

ST7565::ST7565(RobotLib *robotLib, int8_t SID, int8_t SCLK, int8_t A0, int8_t RST, int8_t CS, bool fullfont) 
	: DeviceBase(robotLib)
{
	if (robotLib->getEmulator())
		return;
	initialize(SID,SCLK,A0,RST,CS,fullfont);
}

void ST7565::initialize(int8_t SID, int8_t SCLK, int8_t A0, int8_t RST, int8_t CS, bool fullfont)
{
	partialUpdateEnabled = true;
	this->sid = SID;
	this->sclk  = SCLK;
	this->a0 = A0;
	this->rst = RST;
	this->cs = CS;
	this->fullfont = fullfont;
	
	pinMode(sid, OUTPUT);
	pinMode(sclk, OUTPUT);
	pinMode(a0, OUTPUT);
	pinMode(rst, OUTPUT);
	pinMode(cs, OUTPUT);
	
	// toggle RST low to reset; CS low so it'll listen to us
	if (cs > 0)
	{
		digitalWrite(CS, 0);
	}
	
	digitalWrite(rst, 0);
	usleep(50000);
	digitalWrite(rst, 1);
	
	// LCD bias select
	cmd(CMD_SET_BIAS_7);
	// ADC select
	cmd(CMD_SET_ADC_NORMAL);
	// SHL select
	cmd(CMD_SET_COM_NORMAL);
	// Initial display line
	cmd(CMD_SET_DISP_START_LINE);
	
	// Turn on voltage converter
	cmd(CMD_SET_POWER_CONTROL | 0x4);
	
	usleep(50000);
	
	// turn on voltage regulator (VC=1, VR=1, VF=0)
	cmd(CMD_SET_POWER_CONTROL | 0x6);
	// wait >=50ms
	usleep(50000);
	
	// turn on voltage follower (VC=1, VR=1, VF=1)
	cmd(CMD_SET_POWER_CONTROL | 0x7);
	// wait
	usleep(10000);
	
	// set lcd operating voltage (regulator resistor, ref voltage resistor)
	cmd(CMD_SET_RESISTOR_RATIO | 0x6);
	
	updateBoundingBox(0, 0, LCDWIDTH - 1, LCDHEIGHT - 1);
	cmd(CMD_DISPLAY_ON);
	cmd(CMD_SET_ALLPTS_NORMAL);
}

// draw a circle outline
void ST7565::drawcircle(uint8_t x0,	uint8_t y0,	uint8_t r, uint8_t color) 
{
	updateBoundingBox(x0 - r, y0 - r, x0 + r, y0 + r);

	int8_t f = 1 - r;
	int8_t ddF_x = 1;
	int8_t ddF_y = -2 * r;
	int8_t x = 0;
	int8_t y = r;

	isetpixel(x0, y0 + r, color);
	isetpixel(x0, y0 - r, color);
	isetpixel(x0 + r, y0, color);
	isetpixel(x0 - r, y0, color);

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
  
		isetpixel(x0 + x, y0 + y, color);
		isetpixel(x0 - x, y0 + y, color);
		isetpixel(x0 + x, y0 - y, color);
		isetpixel(x0 - x, y0 - y, color);
    
		isetpixel(x0 + y, y0 + x, color);
		isetpixel(x0 - y, y0 + x, color);
		isetpixel(x0 + y, y0 - x, color);
		isetpixel(x0 - y, y0 - x, color);
    
	}
}

void ST7565::drawstring(uint8_t x, uint8_t line, char *c) {
	while (c[0] != 0) {
		drawchar(x, line, c[0]);
		c++;
		x += 6; // 6 pixels wide
		if (x + 6 >= LCDWIDTH) {
			x = 0;    // ran out of this line
			line++;
		}
		if (line >= (LCDHEIGHT / 8))
			return;        // ran out of space :(
	}
}

void ST7565::drawbitmap(uint8_t x, uint8_t y, const uint8_t *bitmap, uint8_t w,	uint8_t h, uint8_t color) 
{
	for (uint8_t j = 0; j < h; j++) {
		for (uint8_t i = 0; i < w; i++) {
			if ((bitmap[i + (j / 8) * w]) & (1 << (j % 8))) {
				isetpixel(x + i, y + j, color);
			}
		}
	}

	updateBoundingBox(x, y, x + w, y + h);
}


void ST7565::drawstring_P(uint8_t x, uint8_t line, const char *str) 
{
	while (1) {
		char c = *str++;
		if (!c)
			return;
		drawchar(x, line, c);
		x += 6; // 6 pixels wide
		if (x + 6 >= LCDWIDTH) {
			x = 0;    // ran out of this line
			line++;
		}
		if (line >= (LCDHEIGHT / 8))
			return;        // ran out of space :(
	}
}

void  ST7565::drawchar(uint8_t x, uint8_t line, char c) 
{
	if (fullfont)
	{		
		for (uint8_t i = 0; i < 5; i++)
		{
			st7565_buffer[x + (line * 128)] = gca_fontfull[(c * 5) + i];
			x++;
		}
	}
	else
	{
		for (uint8_t i = 0; i < 5; i++)
		{
			st7565_buffer[x + (line * 128)] = gca_font[(c * 5) + i];
			x++;
		}
	}
	updateBoundingBox(x, line * 8, x + 5, line * 8 + 8);
}

// bresenham's algorithm - thx wikpedia
void ST7565::drawline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color) 
{
	uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		std::swap(x0, y0);
		std::swap(x1, y1);
	}

	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	  // much faster to put the test here, since we've already sorted the points
	updateBoundingBox(x0, y0, x1, y1);

	uint8_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int8_t err = dx / 2;
	int8_t ystep;

	if (y0 < y1) {
		ystep = 1;
	}
	else {
		ystep = -1;
	}

	for (; x0 <= x1; x0++) {
		if (steep) {
			isetpixel(y0, x0, color);
		}
		else {
			isetpixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

// filled rectangle
void ST7565::fillrect(uint8_t x, uint8_t y,	uint8_t w, uint8_t h, uint8_t color) 
{
	  
	for (uint8_t i = x; i < x + w; i++) {
		for (uint8_t j = y; j < y + h; j++) {
			isetpixel(i, j, color);
		}
	}

	updateBoundingBox(x, y, x + w, y + h);
}

// draw a rectangle
void ST7565::drawrect(uint8_t x, uint8_t y,	uint8_t w, uint8_t h, uint8_t color) 
{
	for (uint8_t i = x; i < x + w; i++) {
		isetpixel(i, y, color);
		isetpixel(i, y + h - 1, color);
	}
	for (uint8_t i = y; i < y + h; i++) {
		isetpixel(x, i, color);
		isetpixel(x + w - 1, i, color);
	} 

	updateBoundingBox(x, y, x + w, y + h);
}

void ST7565::fillcircle(uint8_t x0,
	uint8_t y0,
	uint8_t r, 
	uint8_t color) 
{
	updateBoundingBox(x0 - r, y0 - r, x0 + r, y0 + r);

	int8_t f = 1 - r;
	int8_t ddF_x = 1;
	int8_t ddF_y = -2 * r;
	int8_t x = 0;
	int8_t y = r;

	for (uint8_t i = y0 - r; i <= y0 + r; i++) {
		isetpixel(x0, i, color);
	}

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
  
		for (uint8_t i = y0 - y; i <= y0 + y; i++) {
			isetpixel(x0 + x, i, color);
			isetpixel(x0 - x, i, color);
		} 
		for (uint8_t i = y0 - x; i <= y0 + x; i++) {
			isetpixel(x0 + y, i, color);
			isetpixel(x0 - y, i, color);
		}    
	}
}

void ST7565::isetpixel(uint8_t x, uint8_t y, uint8_t color)
{
	if ((x >= LCDWIDTH) || (y >= LCDHEIGHT))
		return;

	// x is which column
	if (color) 
		st7565_buffer[x + (y / 8) * 128] |= (1 << (7 - (y % 8)));  
	else
		st7565_buffer[x + (y / 8) * 128] &= ~(1 << (7 - (y % 8))); 

}


void ST7565::setpixel(uint8_t x, uint8_t y, uint8_t color)
{
	if ((x >= LCDWIDTH) || (y >= LCDHEIGHT))
		return;

	// x is which column
	if (color) 
		st7565_buffer[x + (y / 8) * 128] |= (1 << (7 - (y % 8)));  
	else
		st7565_buffer[x + (y / 8) * 128] &= ~(1 << (7 - (y % 8))); 

	updateBoundingBox(x, y, x, y);
}

// Returns the value of a single pixel
uint8_t ST7565::getpixel(uint8_t x, uint8_t y) 
{
	if ((x >= LCDWIDTH) || (y >= LCDHEIGHT))
		return 0;

	return (st7565_buffer[x + (y / 8) * 128] >> (7 - (y % 8))) & 0x1;  
}

void ST7565::updateBoundingBox(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax)
{
	if (partialUpdateEnabled)
	{
		if (xmin < xUpdateMin) xUpdateMin = xmin;
		if (xmax > xUpdateMax) xUpdateMax = xmax;
		if (ymin < yUpdateMin) yUpdateMin = ymin;
		if (ymax > yUpdateMax) yUpdateMax = ymax;
	}
}
void ST7565::spiWrite(uint8_t c)
{
	shiftOut(sid, sclk, MSBFIRST, c);
}

void ST7565::cmd(uint8_t c)
{
	digitalWrite(a0, LOW);
	spiWrite(c);
}

void ST7565::data(uint8_t c)
{
	digitalWrite(a0, HIGH);
	spiWrite(c);
}

void ST7565::setBrightness(uint8_t val)
{
	cmd(CMD_SET_VOLUME_FIRST);
	cmd(CMD_SET_VOLUME_SECOND | (val & 0x3f));
}

void ST7565::clear()
{
	memset(st7565_buffer, 0, 1024);
	updateBoundingBox(0, 0, LCDWIDTH - 1, LCDHEIGHT - 1);
}

// Doesnt affect the buffer, just clears display RAM
void ST7565::clearDisplay()
{
	uint8_t p, c;
  
	for (p = 0; p < 8; p++) 
	{
		cmd(CMD_SET_PAGE | p);
		for (c = 0; c < 129; c++) 
		{			
			cmd(CMD_SET_COLUMN_LOWER | (c & 0xf));
			cmd(CMD_SET_COLUMN_UPPER | ((c >> 4) & 0xf));
			data(0x0);
		}     
	}
}

void ST7565::display()
{
	uint8_t col, maxcol, p;
	for (p = 0; p < 8; p++)
	{		
		if (partialUpdateEnabled)	
		{
			if (yUpdateMin >= ((p + 1) * 8))
			{
				continue;
			}
			if (yUpdateMax < p * 8)
			{
				break;				
			}
		}
		cmd(CMD_SET_PAGE | pagemap[p]);
		
		if (partialUpdateEnabled)
		{
			col = xUpdateMin;
			maxcol = xUpdateMax;			
		}
		
		cmd(CMD_SET_COLUMN_LOWER | ((col + ST7565_STARTBYTES) & 0xf));
		cmd(CMD_SET_COLUMN_UPPER | (((col + ST7565_STARTBYTES) >> 4) & 0x0F));
		cmd(CMD_RMW);
		for (; col <= maxcol; col++)
		{
			data(st7565_buffer[(128*p) + col]);
		}
	}
	if (partialUpdateEnabled)
	{
		xUpdateMin = LCDWIDTH - 1;
		xUpdateMax = 0;
		yUpdateMin = LCDHEIGHT - 1;
		yUpdateMax = 0;
	}
}

bool ST7565::isAvailable()
{
}

bool ST7565::isConnected()
{
}

ST7565::~ST7565()
{
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(ST7565);