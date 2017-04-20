#include <vector>
#include "../3rdParty/wiringPi/wiringPi/wiringPiI2C.h"
#include <stdint.h>

static std::vector<uint8_t> scanI2C()
{
	std::vector<uint8_t> returnValue;

	for (int addr = 1; addr < 127; addr++)
	{
		if (wiringPiI2CSetup(addr))
		{
			returnValue.push_back(addr);
		}
	}
	return returnValue;
}