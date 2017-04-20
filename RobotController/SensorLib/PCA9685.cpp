#include "PCA9685.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPi.h"
#include "../../RobotLib/i2cscanner.cpp"

bool PCA9685::initialized;
uint8_t PCA9685::pca9685I2CAddr;
int PCA9685::i2cfd = 0;

PCA9685::PCA9685(RobotLib *robotLib)
	: DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	if (robotLib->getEmulator())
	{
		initialized = true;
		return;
	}
	initialized = false;
	i2cfd = scanForPCA9685();
	if (i2cfd > 0)
	{
		pca9685Avail = true;
	}
	else
	{
		pca9685Avail = false;
		return;
	}
	initialize();
}

PCA9685::PCA9685(RobotLib *robotLib, uint8_t i2caddress)
	: DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	initialized = false;
	i2cfd = wiringPiI2CSetup(i2caddress);
	if (i2cfd > 0)
	{
		pca9685Avail = true;
	}
	else
	{
		pca9685Avail = false;
		std::stringstream ss;
		ss << "Failed to open I2C Bus on address: " << i2caddress;
		robotLib->LogError(ss.str());
		return;
	}

	initialize();
}

void PCA9685::initialize()
{
	// Create a node with 16 pins [0..15] + [16] for all
	// Setup the chip enabling auto-increment of registers
	int settings = wiringPiI2CReadReg8(i2cfd, PCA9685_MODE1) & 0x7F;
	int autoInc = settings | 0x20;
	if (wiringPiI2CWriteReg8(i2cfd, PCA9685_MODE1, autoInc) == -1)
	{
		robotLib->LogError("Failed to write to Reg: PCA9685_MODE1");
		pca9685Avail = false;
		return;
	}
	pca9685PWMFreq(50);
	initialized = true;
}

// Frequency will be capped to a range of 40<freq<1000
void PCA9685::pca9685PWMFreq(float frequency)
{
	if (i2cfd <= 0)
	{
		initialize();
		if (i2cfd < 0)
		{
			robotLib->LogError("Could not initalize PCA9685, exiting without setting frequency");
			return;
		}
	}
	float newFreq = (frequency > 1000 ? 1000 : (frequency < 40 ? 40 : frequency));
	if (newFreq != frequency)
	{
		std::stringstream ss;
		ss << "Frequency capped, was: " << frequency << ", now is: " << newFreq;
		robotLib->Log(ss.str());
		frequency = newFreq;
	}

	// To set pwm frequency we have to set the prescale register. The formula is:
	// prescale = round(osc_clock / (4096 * frequency))) - 1 where osc_clock = 25 MHz
	// Further info here: http://www.nxp.com/documents/data_sheet/PCA9685.pdf Page 24
	int prescale = (int)(25000000.0f / (4096 * frequency) - 0.5f);

	// Get settings and calc bytes for the different states.
	int settings = wiringPiI2CReadReg8(i2cfd, PCA9685_MODE1) & 0x7F;	// Set restart bit to 0
	int sleep	= settings | 0x10;									// Set sleep bit to 1
	int wake 	= settings & 0xEF;									// Set sleep bit to 0
	int restart = wake | 0x80;										// Set restart bit to 1

	// Go to sleep, set prescale and wake up again.
	wiringPiI2CWriteReg8(i2cfd, PCA9685_MODE1, sleep);
	wiringPiI2CWriteReg8(i2cfd, PCA9685_PRESCALE, prescale);
	wiringPiI2CWriteReg8(i2cfd, PCA9685_MODE1, wake);

	// Now wait a millisecond until oscillator finished stabilizing and restart PWM.
	delay(1);
	wiringPiI2CWriteReg8(i2cfd, PCA9685_MODE1, restart);
	std::stringstream ss;
	ss << "PWM Frequency set to: " << frequency;
	robotLib->Log(ss.str());
}

/**
 * Enables or deactivates full-on
 * tf = true: full-on
 * tf = false: according to PWM
 */
void PCA9685::pca9685FullOn(int pin, int tf)
{
	int reg = baseReg(pin) + 1;		// LEDX_ON_H
	int state = wiringPiI2CReadReg8(i2cfd, reg);

	// Set bit 4 to 1 or 0 accordingly
	state = tf ? (state | 0x10) : (state & 0xEF);

	wiringPiI2CWriteReg8(i2cfd, reg, state);

	// For simplicity, we set full-off to 0 because it has priority over full-on
	if (tf)
		pca9685FullOff(pin, 0);
}

/**
 * Enables or deactivates full-off
 * tf = true: full-off
 * tf = false: according to PWM or full-on
 */
void PCA9685::pca9685FullOff(int pin, int tf)
{
	int reg = baseReg(pin) + 3;		// LEDX_OFF_H
	int state = wiringPiI2CReadReg8(i2cfd, reg);

	// Set bit 4 to 1 or 0 accordingly
	state = tf ? (state | 0x10) : (state & 0xEF);

	wiringPiI2CWriteReg8(i2cfd, reg, state);
}

/**
 * Helper function to get to register
 */
int PCA9685::baseReg(int pin)
{
	return (pin >= PIN_ALL ? PCA9685_LEDALL_ON : PCA9685_LED0 + 4 * pin);
}

/**
 * Set all leds back to default values (: fullOff = 1)
 */
void PCA9685::pca9685PWMReset()
{
	wiringPiI2CWriteReg16(i2cfd, PCA9685_LEDALL_ON, 0x0);
	wiringPiI2CWriteReg16(i2cfd, PCA9685_LEDALL_ON + 2, 0x1000);
}

/**
 * Write on and off ticks manually to a pin
 * (Deactivates any full-on and full-off)
 */
void PCA9685::pca9685PWMWrite(int pin, int on, int off)
{
	int reg = baseReg(pin);

	// Write to on and off registers and mask the 12 lowest bits of data to overwrite full-on and off
	wiringPiI2CWriteReg16(i2cfd, reg, on  & 0x0FFF);
	wiringPiI2CWriteReg16(i2cfd, reg + 2, off & 0x0FFF);
}

/**
 * Reads both on and off registers as 16 bit of data
 * To get PWM: mask each value with 0xFFF
 * To get full-on or off bit: mask with 0x1000
 * Note: ALL_LED pin will always return 0
 */
void PCA9685::pca9685PWMRead(int pin, int *on, int *off)
{
	int reg = baseReg(pin);

	if (on)
		*on  = wiringPiI2CReadReg16(i2cfd, reg);
	if (off)
		*off = wiringPiI2CReadReg16(i2cfd, reg + 2);
}

device_status_t PCA9685::getDeviceStatus(RobotLib *robotLib)
{
	// If for some reason we have previously initialized, go ahead and return that we are connected
	if (initialized)
	{
		return device_status_t::DEVICE_AVAILABLE;
	}

	// We havent initialized, we will scan
	if (scanForPCA9685() > 0)
	{
		return device_status_t::DEVICE_CONNECTED;
	}

	return device_status_t::DEVICE_UNAVAILBLE;
}

PCA9685::~PCA9685()
{
}

void PCA9685::pPwmWrite(int pin, int value)
{
	if (value >= 4096)
		pca9685FullOn(pin, 1);
	else if (value > 0)
		pca9685PWMWrite(pin, 0, value);		// Deactivates full on and off byitself
	else
		pca9685FullOff(pin, 1);
}

/**
 * Reads off registers as 16 bit of data
 * To get PWM: mask with 0xFFF
 * To get full-off bit: mask with 0x1000
 * Note: ALL_LED pin will always return 0
 */
int PCA9685::pOffRead(int pin)
{
	int off;
	pca9685PWMRead(pin, 0, &off);
	return off;
}

/**
 * Reads on registers as 16 bit of data
 * To get PWM: mask with 0xFFF
 * To get full-on bit: mask with 0x1000
 * Note: ALL_LED pin will always return 0
 */
int PCA9685::pOnRead(int pin)
{
	int on;
	pca9685PWMRead(pin, &on, 0);
	return on;
}

/**
 * Simple full-on and full-off control
 * If value is 0, full-off will be enabled
 * If value is not 0, full-on will be enabled
 */
void PCA9685::pOnOffWrite(int pin, int value)
{
	if (value)
		pca9685FullOn(pin, 1);
	else
		pca9685FullOff(pin, 1);
}

uint8_t PCA9685::scanForPCA9685()
{
	std::vector<uint8_t> i2cInUse = scanI2C();

	// Now go thru all the available addresses with devices attached
	// Check to see if it is between PCA9685_I2C_MIN and PCA9685_I2C_MAX
	// then try and communicate
	for (uint8_t i = 0; i < i2cInUse.size(); i++)
	{
		if (i2cInUse[i] >= PCA9685_I2C_MIN && i2cInUse[i] <= PCA9685_I2C_MAX)
		{
			int i2caddr = i2cInUse[i];
			int fd = wiringPiI2CSetup(i2caddr);
			if (fd > 0)
			{
				int settings = wiringPiI2CReadReg8(fd, 0x0);
				if (settings >= 0)
				{
					pca9685I2CAddr = i2caddr;
					//PCA9685 Doesnt have a who am I, so we are going to hope this is it
					return fd;
				}
			}
		}
	}
	return -1;
}

// Sets pin without having to deal with on/off tick placement and properly handles
// a zero value as completely off.  Optional invert parameter supports inverting
// the pulse for sinking to ground.  Val should be a value from 0 to 4095 inclusive.
void PCA9685::pca9685SetPin(int pin, int value)
{
	if (value >= 4096)
		pca9685FullOn(pin, 1);
	else if (value > 0)
		pca9685PWMWrite(pin, 0, value);		// Deactivates full on and off byitself
	else
		pca9685FullOff(pin, 1);
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(PCA9685);