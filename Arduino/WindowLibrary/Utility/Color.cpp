#include "Color.h"

uint16_t Color::GetColor565(ColorDefs color)
{ 
	uint8_t a = (color & 0xFF000000) >> 24;
	uint8_t r = (color & 0x00FF0000) >> 16;
	uint8_t g = (color & 0x0000FF00) >> 8;
	uint8_t b = (color & 0x000000FF);
	uint16_t c = (uint16_t)((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
#ifdef DEBUG
	Logger::Trace("RGB, C (%d,%d,%d) %d", r, g, b, c);
#endif
	return c;
}
uint16_t Color::Color32To565(int32_t color) 
{ 
	if (color & 0xFF000000)
		color = color - 0xFF000000;
	uint8_t r = (color & 0x00FF0000) >> 16;
	uint8_t g = (color & 0x0000FF00) >> 8;
	uint8_t b = (color & 0x000000FF);
	uint16_t c=((((color >> 16) & 0xFF) / 8) << 11) | ((((color >> 8) & 0xFF) / 4) << 5) | (((color) &  0xFF) / 8);	
	return c;
}