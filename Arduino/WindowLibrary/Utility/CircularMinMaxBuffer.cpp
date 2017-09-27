#include "CircularMinMaxBuffer.h"

CircularMinMaxBuffer::CircularMinMaxBuffer(uint16_t maxSize)
{
	this->maxSize = maxSize;		
}


CircularMinMaxBuffer::~CircularMinMaxBuffer()
{	
}


void CircularMinMaxBuffer::PushItem(float item)
{	
	values.push_back(item);	
	itemCount++;
	if (itemCount > maxSize)
	{
		min = values.at(0);
		max = values.at(0);

		itemCount = maxSize / 2;
		values.erase(values.begin(), values.begin() + values.size() / 2);
		currentTotal = 0;		
		for (int i = 0; i < values.size(); i++)
		{
			currentTotal += values.at(i);
			if (values.at(i) > max)
				max = values.at(i);
			if (values.at(i) < min)
				min = values.at(i);
		}
	}
	else
	{
		if (itemCount==1)
		{
			min = item;
			max = item;
		}
		currentTotal += item;
		if (item > max)
			max = item;
		if (item < min)
			min = item;
	}
	avg = currentTotal / itemCount;	
	// Calculate a simple checkum
	checksum = ((int)currentTotal*itemCount) % 65536;
}
