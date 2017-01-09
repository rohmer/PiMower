#include "TCS34725.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPiI2C.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPi.h"

bool TCS34725::tcs34725Avail = false;
bool TCS34725::initialized = false;
uint8_t TCS34725::i2cfd = 0;

TCS34725::TCS34725(RobotLib *robotLib)
	: SensorBase(robotLib)
{
	if (robotLib->getEmulator())
	{
		initialized = true;
		return;
	}
	try
	{
		i2cfd = DeviceManager::getI2CFD(TCS34725_ADDRESS);
	}
	catch (...)
	{
		robotLib->LogError("Could not initalize TCS34725");
		initialized = false;
	}

	initialize();
}

TCS34725::TCS34725(RobotLib *robotLib, uint8_t i2caddress) :
	SensorBase(robotLib)
{
	initialized = false;	
	if(i2cfd>0)
	{
		tcs34725Avail = true;
	} else
	{
		tcs34725Avail = false;
		std::stringstream ss;
		ss << "Failed to open I2C Bus on address: " << i2caddress;
		robotLib->LogError(ss.str());

		return;
	}
	initialize();
}

void TCS34725::initialize()
{
	// First check to see if we are connected
	i2cfd = DeviceManager::getI2CFD(TCS34725_ADDRESS);
	if (i2cfd < 0)
	{
		robotLib->LogWarn("Couldnt connect to I2C address");
	}
		
	uint8_t id = read8(TCS34725_ID);
	if(id==0x44)
	{
		robotLib->Log("TCS34721/TCS34725 detected");
	} else
	{
		if(id==0x4D)
		{
			robotLib->Log("TCS34723/TCS34727 detected");
		} else
		{
			robotLib->LogError("Failed to communicate with reg 0x16");
			initialized = false;
			return;
		}
	} 
	initialized = true;
	gain = TCS34725_GAIN_1X;
	integrationTime = TCS34725_INTEGRATIONTIME_2_4MS;
	setIntegrationTime(integrationTime);
	setGain(gain);
	enable();
}

void TCS34725::enable()
{
	if (!initialized)
	{
		initialize();
		if (!initialized)
		{
			robotLib->LogError("Cannot initialize TCS34725");
			return;
		}
	}
	write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);	
	delay(3);
	write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
}

// Turn off device to save power
void TCS34725::disable()
{
	uint8_t reg = 0;
	reg = read8(TCS34725_ENABLE);	
	write8(TCS34725_ENABLE, reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
}

void TCS34725::setIntegrationTime(tcs34725IntegrationTime_t it)
{
	if(!initialized)
	{
		initialize();
		if(!initialized)
		{
			robotLib->LogError("Cannot initialize TCS34725");
			return;
		}
	}

	// Update timing register
	write8(TCS34725_ATIME, it);
	integrationTime = it;
}

void TCS34725::setGain(tcs34725Gain_t gain)
{
	if (!initialized)
	{
		initialize();
		if (!initialized)
		{
			robotLib->LogError("Cannot initialize TCS34725");
			return;
		}
	}
	write8(TCS34725_CONTROL, gain);
	this->gain = gain;
}

/**************************************************************************/
/*!
@brief  Reads the raw red, green, blue and clear channel values
*/
/**************************************************************************/
void TCS34725::getRawData(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* c)
{
	if(!initialized)
	{
		initialize();
		if (!initialized)
		{
			robotLib->LogError("Cannot initialize TCS34725");
			return;
		}
	}

	*c = read16(TCS34725_CDATAL);
	*r = read16(TCS34725_RDATAL);
	*g = read16(TCS34725_GDATAL);
	*b = read16(TCS34725_BDATAL);	

	/* Sea a delay for the integration time */
	switch(integrationTime)
	{
		case TCS34725_INTEGRATIONTIME_2_4MS:
			delay(3);
			break;
		case TCS34725_INTEGRATIONTIME_24MS:
			delay(24);
			break;
		case TCS34725_INTEGRATIONTIME_50MS:
			delay(50);
			break;
		case TCS34725_INTEGRATIONTIME_101MS:
			delay(101);
			break;
		case TCS34725_INTEGRATIONTIME_154MS:
			delay(154);
			break;
		case TCS34725_INTEGRATIONTIME_700MS:
			delay(700);
			break;
	}
}

uint16_t TCS34725::calcuateColorTemperature(uint16_t r, uint16_t g, uint16_t b)
{
	float X, Y, Z;
	float xc, yc;
	float n;
	float cct;

	/* 1. Map RGB values to their XYZ counterparts.    */
	/* Based on 6500K fluorescent, 3000K fluorescent   */
	/* and 60W incandescent values for a wide range.   */
	/* Note: Y = Illuminance or lux                    */
	X = (-0.14282F * r) + (1.54924F * g) + (-0.95641F * b);
	Y = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
	Z = (-0.68202F * r) + (0.77073F * g) + (0.56332F * b);

	/* 2. Calculate the chromaticity co-ordinates      */
	xc = (X) / (X + Y + Z);
	yc = (Y) / (X + Y + Z);

	/* 3. Use McCamy's formula to determine the CCT    */
	n = (xc - 0.3320F) / (0.1858F - yc);

	/* Calculate the final CCT */
	cct = (449.0F * powf(n, 3)) + (3525.0F * powf(n, 2)) + (6823.3F * n) + 5520.33F;

	/* Return the results in degrees Kelvin */
	return (uint16_t)cct;
}

uint16_t TCS34725::calculateLux(uint16_t r, uint16_t g, uint16_t b)
{
	float illuminance;

	/* This only uses RGB ... how can we integrate clear or calculate lux */
	/* based exclusively on clear since this might be more reliable?      */
	illuminance = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);

	return (uint16_t)illuminance;
}

void TCS34725::setInterrupt(bool interruptEnable)
{
	uint8_t r = read8(TCS34725_ENABLE);
	if(interruptEnable)
	{
		r |= TCS34725_ENABLE_AIEN;
	} else
	{
		r &= ~TCS34725_ENABLE_AIEN;
	}
	write8(TCS34725_ENABLE, r);	
}

void TCS34725::clearInterrupt()
{
	
	wiringPiI2CWrite(i2cfd,TCS34725_COMMAND_BIT | 0x66);
}

void TCS34725::setIntLimits(uint16_t low, uint16_t high)
{
	write8(0x04,low && 0xFF);
	write8(0x05, low >> 8);
	write8(0x06, high & 0xFF);
	write8(0x07, high >> 8);
}

bool TCS34725::getEvent(sensors_event_t *event)
{
	if (!initialized)
	{
		initialize();
		if (!initialized)
		{
			robotLib->LogError("Cannot initialize TCS34725");
			return false;
		}
	}
	memset(event, 0, sizeof(sensors_event_t));
	uint16_t r, g, b, c;
	getRawData(&r, &g, &b, &c);
	event->light = calculateLux(r, g, b);
	event->color.colorTemp = calcuateColorTemperature(r, g, b);
	event->color.b = b;	
	event->color.g = g;
	event->color.r = r;	
	return true;
}

static device_status_t getDeviceStatus(RobotLib *robotLib)
{
	int i2cfd = DeviceManager::getI2CFD(TCS34725_ADDRESS);
	if (i2cfd < 0)
	{
		robotLib->LogWarn("Couldnt connect to I2C address");
		return device_status_t::DEVICE_UNAVAILBLE;
	}
	
	uint8_t id = wiringPiI2CReadReg8(i2cfd, (TCS34725_COMMAND_BIT | TCS34725_ID));
	
	if(id==0x44)
	{
		robotLib->Log("TCS34721/TCS34725 detected");
		return device_status_t::DEVICE_AVAILABLE;
	} else
	{
		if(id==0x4D)
		{
			robotLib->Log("TCS34723/TCS34727 detected");
			return device_status_t::DEVICE_AVAILABLE;
		} else
		{
			robotLib->Log("no TCS3472* detected");
			return device_status_t::DEVICE_UNAVAILBLE;
		}
	} 
}

void TCS34725::write8(uint8_t reg, uint8_t value)
{
	wiringPiI2CWriteReg8(i2cfd, (TCS34725_COMMAND_BIT | reg), (value & 0xff));
}

uint8_t TCS34725::read8(uint8_t reg)
{
	uint8_t value;
	value = wiringPiI2CReadReg8(i2cfd, (TCS34725_COMMAND_BIT | reg));
	return value;
}

uint16_t TCS34725::read16(uint8_t reg)
{
	uint16_t value;
	value = wiringPiI2CReadReg16(i2cfd, (TCS34725_COMMAND_BIT | reg));
	return value;
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(TCS34725);