#include "LSM303_Magnetometer.h"

static float _lsm303Mag_Gauss_LSB_XY = 1100.0F;  // Varies with gain
static float _lsm303Mag_Gauss_LSB_Z  = 980.0F;   // Varies with gain
bool LSM303_Magnetometer::magInit  = false;
bool LSM303_Magnetometer::magAttached = false;
int LSM303_Magnetometer::i2cfd_Mag = 0;

LSM303_Magnetometer::LSM303_Magnetometer(RobotLib* rl) :
	SensorBase(rl)
{
	if (rl->getEmulator())
	{
		return;
	}
	i2cfd_Mag = -1;	
	magInit = false;
	
	try
	{
		i2cfd_Mag = DeviceManager::getI2CFD(LSM303_ADDRESS_MAG);
	}
	catch (...)
	{
		magInit = false;
		magAttached = false;
		robotLib->LogError("Could not initalize Magnetometer (Device not attached?)");
	}
	
	if (i2cfd_Mag == -1)
	{
		magInit = false;
		magAttached = false;
		robotLib->LogError("Could not initalize Magnetometer");
		return;
	}
	else
	{
		magInit = true;
		robotLib->Log("Magnetometer initalized");
	}
	uint8_t reg1_a;
	
	// Enable the Magnetometer
	int val;
	val=wiringPiI2CWriteReg16(i2cfd_Mag, LSM303_REGISTER_MAG_MR_REG_M, 0x00);
	// LSM303DLHC has no WHOAMI register so read CRA_REG_M to check
	// the default value (0b00010000/0x10)
	reg1_a = wiringPiI2CReadReg8(i2cfd_Mag, LSM303_REGISTER_MAG_CRA_REG_M);
	if (reg1_a != 0x10)
	{
		magInit = false;
		robotLib->LogError("Failed to communicate with magnetometer");
	}
	else
	{
		robotLib->Log("Communicated with magnetometer successfully");
	}
	// Set the gain to a known level
	setMagGain(LSM303_MAGGAIN_1_3);
	autoRange = false;
}

void LSM303_Magnetometer::getSensor(sensor_t *sensor)
{
	//memset(sensor, 0, sizeof(sensor_t));
	strncpy(sensor->name, "LSM303_Magnetometer", sizeof(sensor->name) - 1);
	sensor->name[sizeof(sensor->name) - 1] = 0;
	sensor->version = 1;
	sensor->sensor_id = LSM303_ADDRESS_MAG;
	sensor->type = SENSOR_TYPE_MAGNETIC_FIELD;
	sensor->min_delay = 0;
	sensor->max_value = 0.0F;		// TBD;
	sensor->min_value = 0.0F;		// TBD;
	sensor->resolution = 0.0F;		// TBD;	
}

void LSM303_Magnetometer::setMagGain(lsm303MagGain gain)
{
	if (magInit == false)
	{
		robotLib->LogError("Magnetometer is not initalized");
		return;
	}
	
	wiringPiI2CWriteReg16(i2cfd_Mag, LSM303_REGISTER_MAG_CRB_REG_M,static_cast<uint8_t>(gain));
	magGain = gain;
	switch (gain)
	{		
		case LSM303_MAGGAIN_1_3:
			_lsm303Mag_Gauss_LSB_XY = 1100;
			_lsm303Mag_Gauss_LSB_Z  = 980;
			break;
		case LSM303_MAGGAIN_1_9:
			_lsm303Mag_Gauss_LSB_XY = 855;
			_lsm303Mag_Gauss_LSB_Z  = 760;
			break;
		case LSM303_MAGGAIN_2_5:
			_lsm303Mag_Gauss_LSB_XY = 670;
			_lsm303Mag_Gauss_LSB_Z  = 600;
			break;
		case LSM303_MAGGAIN_4_0:
			_lsm303Mag_Gauss_LSB_XY = 450;
			_lsm303Mag_Gauss_LSB_Z  = 400;
			break;
		case LSM303_MAGGAIN_4_7:
			_lsm303Mag_Gauss_LSB_XY = 400;
			_lsm303Mag_Gauss_LSB_Z  = 355;
			break;
		case LSM303_MAGGAIN_5_6:
			_lsm303Mag_Gauss_LSB_XY = 330;
			_lsm303Mag_Gauss_LSB_Z  = 295;
			break;
		case LSM303_MAGGAIN_8_1:
			_lsm303Mag_Gauss_LSB_XY = 230;
			_lsm303Mag_Gauss_LSB_Z  = 205;
			break;
	}
}

void LSM303_Magnetometer::enableAutoRange(bool enabled)
{
	autoRange = enabled;
}

void LSM303_Magnetometer::setMagRate(lsm303MagRate rate)
{
	uint8_t reg_m = ((uint8_t)rate & 0x07) << 2;
	wiringPiI2CWriteReg16(i2cfd_Mag, LSM303_REGISTER_MAG_CRA_REG_M, reg_m);	
}

std::string LSM303_Magnetometer::getDeviceName()
{
	return "LSM303_Magnetometer";
}

bool LSM303_Magnetometer::getEvent(sensors_event_t *event)
{
	if (!magInit)
	{
		robotLib->LogError("Magnetometer is not intialized");
		return (false);
	}	
	bool readingValid = false;
	//memset(event, 0, sizeof(sensors_event_t));
	while (!readingValid)
	{
		uint8_t reg_mg = wiringPiI2CReadReg8(i2cfd_Mag, LSM303_REGISTER_MAG_SR_REG_Mg);
		if (!(reg_mg & 0x1))
		{
			robotLib->LogWarn("Failed to read SR_REG");
			return false;		
		}
		
		/* Read new data */
		read();
		
		/* Make sure the sensor isn't saturating if auto-ranging is enabled */
		if (!autoRange)
		{
			readingValid = true;
		}
		else
		{
#if DEBUG
			std::stringstream ss;
			ss << raw.x;		
			robotLib->Log(ss.str());
			ss.clear();
			ss << raw.y;
			robotLib->Log(ss.str());
			ss.clear();
			ss << raw.z;
			robotLib->Log(ss.str());
#endif
			if ((raw.x > 2040) | (raw.x <= -2040) |
				(raw.y >= 2040) | (raw.y <= -2040) |
				(raw.z >= 2040) | (raw.z <= -2040))
			{
			
				/* Saturating, increase the range if we can */
				switch (magGain)
				{			
				case LSM303_MAGGAIN_5_6:
					setMagGain(LSM303_MAGGAIN_8_1);
					readingValid = false;
#ifdef DEBUG
					robotLib->Log("Changing range to +/- 8.1");
#endif
					break;
				case LSM303_MAGGAIN_4_7:
					setMagGain(LSM303_MAGGAIN_5_6);
					readingValid = false;
#ifdef DEBUG
					robotLib->Log("Changing range to +/- 5.6");
#endif
					break;
				case LSM303_MAGGAIN_4_0:
					setMagGain(LSM303_MAGGAIN_4_7);
					readingValid = false;
#ifdef DEBUG
					robotLib->Log("Changing range to +/- 4.7");
#endif
					break;
				case LSM303_MAGGAIN_2_5:
					setMagGain(LSM303_MAGGAIN_4_0);
					readingValid = false;
#ifdef DEBUG
					robotLib->Log("Changing range to +/- 4.0");
#endif
					break;
				case LSM303_MAGGAIN_1_9:
					setMagGain(LSM303_MAGGAIN_2_5);
					readingValid = false;
#ifdef DEBUG
					robotLib->Log("Changing range to +/- 2.5");
#endif
					break;
				case LSM303_MAGGAIN_1_3:
					setMagGain(LSM303_MAGGAIN_1_9);
					readingValid = false;
#ifdef DEBUG
					robotLib->Log("Changing range to +/- 1.9");
#endif
					break;
				default:
					readingValid = true;
					break;
				}
			}
			else
			{
				/* Values are within range */
				readingValid = true;
			}			
		}	 
	}
	event->version   = sizeof(sensors_event_t);
	event->sensor_id = LSM303_ADDRESS_MAG;
	event->type = SENSOR_TYPE_MAGNETIC_FIELD;
	event->timestamp = getTimestamp();
	event->magnetic.x = (float)raw.x / _lsm303Mag_Gauss_LSB_XY*SENSORS_GAUSS_TO_MICROTESLA;
	event->magnetic.y = (float)raw.y / _lsm303Mag_Gauss_LSB_XY*SENSORS_GAUSS_TO_MICROTESLA;
	event->magnetic.z = (float)raw.z / _lsm303Mag_Gauss_LSB_Z*SENSORS_GAUSS_TO_MICROTESLA;
	event->gyro.x = (float)raw.x / _lsm303Mag_Gauss_LSB_XY*SENSORS_GAUSS_TO_MICROTESLA;
	event->gyro.y = (float)raw.y / _lsm303Mag_Gauss_LSB_XY*SENSORS_GAUSS_TO_MICROTESLA;
	event->gyro.z = (float)raw.z / _lsm303Mag_Gauss_LSB_Z*SENSORS_GAUSS_TO_MICROTESLA;
	event->gyro.heading = (atan2(event->magnetic.y, event->magnetic.x) * 180) / 3.14159;
	event->gyro.roll = (atan2(-1*event->magnetic.y, event->magnetic.z) * 180) / 3.14159;
	event->gyro.pitch = (atan2(event->magnetic.x, sqrt(event->magnetic.y*event->magnetic.y + event->magnetic.z*event->magnetic.z)) * 180) / 3.14159;
	return true;
}

void LSM303_Magnetometer::read()
{
	wiringPiI2CWrite(i2cfd_Mag, LSM303_REGISTER_MAG_OUT_X_H_M);		
	int a = 0;
	uint8_t xlo, xhi, ylo, yhi, zlo, zhi;
		
	while (a < 6)
	{			
		int data=0;
		data = wiringPiI2CReadReg8(i2cfd_Mag, LSM303_ADDRESS_MAG);
		if (data < 0)
		{
			robotLib->LogWarn("Error reading from magnetometer: %d" + data);
			return;
		}
		switch (a)
		{
		case 0:
			xlo = data;
			break;
		case 1:
			xhi = data;
			break;
		case 2:
			ylo = data;
			break;
		case 3:
			yhi = data;
			break;
		case 4:
			zlo = data;
			break;
		case 5:
			zhi = data;
			break;
		}
		a++;
	}
	raw.x = (int16_t)((uint16_t)xlo || ((uint16_t)xhi << 8));
	raw.y = (int16_t)((uint16_t)ylo || ((uint16_t)yhi << 8));
	raw.z = (int16_t)((uint16_t)zlo || ((uint16_t)zhi << 8));	
}

sensors_type_t LSM303_Magnetometer::getSensorType()
{
	return SENSOR_TYPE_MAGNETIC_FIELD;
}

void LSM303_Magnetometer::calibrate()
{
	sensors_event_t* event = new sensors_event_t();
	int a = 0;
	float MagMinX, MagMaxX;
	float MagMinY, MagMaxY;
	float MagMinZ, MagMaxZ;
	
	while (a < 30)
	{		
		getEvent(event);
		if (event->magnetic.x < MagMinX)
		{
			MagMinX = event->magnetic.x;			
		}
		if (event->magnetic.x > MagMaxX)
		{
			MagMaxX = event->magnetic.x;			
		}
		if (event->magnetic.y < MagMinY) 
		{
			MagMinY = event->magnetic.y;
		}
		if (event->magnetic.y > MagMaxY)
		{
			MagMaxY = event->magnetic.y;
		}
		if (event->magnetic.z < MagMinZ) 
		{
			MagMinZ = event->magnetic.z;
		}
		if (event->magnetic.z > MagMaxZ) 
		{
			MagMaxZ = event->magnetic.z;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		a++;
	}
}

// All devices require a static getDeviceStatus function
// Logic for detection:
//	  Interrogation is done by:
//		1. If we are previously init, return DEVICE_AVAILABLE
//		2. If we are previously attached, return DEVICE_CONNECTED
//		3. Otherwise try and init
device_status_t LSM303_Magnetometer::getDeviceStatus(RobotLib *robotLib)
{
	if (magInit)
		return device_status_t::DEVICE_AVAILABLE;
	if (magAttached)
		return device_status_t::DEVICE_CONNECTED;
	int i2cfd = i2cfd_Mag;
	if (i2cfd <= 0)
	{
		i2cfd = DeviceManager::getI2CFD(LSM303_ADDRESS_MAG);		
	} 
	if (i2cfd < 0)
	{
		return device_status_t::DEVICE_UNAVAILBLE;		
	}	
	return device_status_t::DEVICE_CONNECTED;
}

std::string LSM303_Magnetometer::getDeviceDescription()
{
	return "LSM303 based Magnetometer";
}

LSM303_Magnetometer::~LSM303_Magnetometer()
{
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(LSM303_Magnetometer);