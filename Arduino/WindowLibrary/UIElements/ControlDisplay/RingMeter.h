#pragma once
#include "../../Options.h"

#ifdef RA8875
#include "../RA8875/UIPrimitives.h"

class RingMeter
{
//	int val, int minV, int maxV, int16_t x, int16_t y, uint16_t r, const char* units, uint16_t colorScheme, 
//	uint16_t backSegColor, int16_t angle, uint8_t inc)
public:
	static void Draw(DriverBase &tft, eUITextFont font, int value, int minValue, int maxValue,
		int16_t x, int16_t y, int16_t radius, std::string units, uint16_t colorScheme, uint16_t segmentColor,
		int16_t angle, uint8_t increment, uint16_t textColor);

private:
	static uint16_t RingMeter::gradient(uint8_t val);	
};
#endif