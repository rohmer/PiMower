#pragma once
#include <vector>
#include <string>
#include <stdint.h>
#include "../Utility/Logger.h"

/// <summary>
/// Class to contain a circular buffer of a certain size
/// When the buffer is full, the first half of the items will be deleted
/// So we can always have preceding data
/// </summary>
class CircularMinMaxBuffer
{
public:
	CircularMinMaxBuffer(uint16_t maxSize);
	~CircularMinMaxBuffer();
	float GetAvg()
	{
		return avg;
	}
	float GetMin()
	{
		return min;
	}
	float GetMax()
	{
		return max;
	}
	uint16_t GetCount()
	{
		uint16_t s = values.size();
		return s;
	}
	void PushItem(float value);
	std::vector<float> GetValues()
	{
		return values;
	}
	uint16_t GetSize()
	{
		return itemCount;
	}

	uint16_t GetChecksum()
	{
		return checksum;
	}

private:
	uint16_t maxSize;
	std::vector<float> values;
	uint16_t itemCount = 0;
	float min, max, avg, currentTotal = 0;
	uint16_t checksum;
};