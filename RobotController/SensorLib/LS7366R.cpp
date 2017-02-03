#include "LS7366R.h"

LS7366R::LS7366R(RobotLib *robotLib)
	: SensorBase(robotLib)
{
	if (robotLib->getEmulator())
	{
		initialized = true;
		return;
	}	
}

LS7366R::LS7366R(RobotLib *robotLib, uint8_t slaveSelectEnc1, uint8_t slaveSelectEnc2)
	: SensorBase(robotLib)
{
	if (robotLib->getEmulator())
	{
		initialized = true;
		return;
	}	
	initialize(slaveSelectEnc1, slaveSelectEnc2);
}

LS7366R::~LS7366R()
{
}

void LS7366R::initialize(uint8_t slaveEncPin1, uint8_t slaveEncPin2)
{
	this->slaveSelectEnc1 = slaveEncPin1;
	this->slaveSelectEnc2 = slaveEncPin2;
	pinMode(slaveSelectEnc1, OUTPUT);
	pinMode(slaveSelectEnc2, OUTPUT);
	
	// Intialize encoder 1
	digitalWrite(slaveSelectEnc1, LOW);
	clearCounter();
	clearStatus();
	wiringPiSPIDataRW(0, (unsigned char *)WRITE_MODE0,sizeof((unsigned char *)WRITE_MODE0));
	wiringPiSPIDataRW(0, (unsigned char *)WRITE_MODE0, sizeof((unsigned char *)WRITE_MODE0));
	
}

void LS7366R::clearCounter()
{
	int ret = wiringPiSPIDataRW(0, (unsigned char *)(CLEAR_COUNTER), sizeof((unsigned char *)CLEAR_COUNTER));
	if (ret == -1)
		robotLib->LogError("Error writing to SPI for CLEAR_COUNTER in LS7366R");	
}

void LS7366R::clearStatus()
{
	int ret = wiringPiSPIDataRW(0, (unsigned char *)(CLEAR_STATUS), sizeof((unsigned char *)CLEAR_STATUS));
	if (ret == -1)
		robotLib->LogError("Error writing to SPI for CLEAR_STATUS in LS7366R");	
}

std::pair<long, long> LS7366R::readCounters()
{
	// Read enc 1
	digitalWrite(slaveSelectEnc1, LOW);
	unsigned char returnVal[4];
	returnVal[0] = returnVal[1] = returnVal[2] = returnVal[3] = READ_COUNTER;
	wiringPiSPIDataRW(0, returnVal, 4);
	long enc1Count = (returnVal[0] << 8) + returnVal[1];
	enc1Count = (enc1Count << 8) + returnVal[2];
	enc1Count = (enc1Count << 8) + returnVal[3];
	digitalWrite(slaveSelectEnc1, HIGH);
	returnVal[0] = returnVal[1] = returnVal[2] = returnVal[3] = READ_COUNTER;
	digitalWrite(slaveSelectEnc2, LOW);
	wiringPiSPIDataRW(0, returnVal, 4);
	long enc2Count = (returnVal[0] << 8) + returnVal[1];
	enc2Count = (enc2Count << 8) + returnVal[2];
	enc2Count = (enc2Count << 8) + returnVal[3];
	digitalWrite(slaveSelectEnc2, HIGH);
	return std::make_pair(enc1Count, enc2Count);
}