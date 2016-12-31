#include "LSM303_Accelerometer.h"

static float _lsm303Accel_MG_LSB     = 0.001F;   // 1, 2, 4 or 12 mg per lsb
bool LSM303_Accelerometer::accelInit = false;
bool LSM303_Accelerometer::accelAttached = false;
int LSM303_Accelerometer::i2cfd_Accel=0;

LSM303_Accelerometer::LSM303_Accelerometer(RobotLib* rl) :
	SensorBase(rl)
{
	if (rl->getEmulator())
		return;
	i2cfd_Accel = -1;
	accelInit = false;	
	
	try
	{
		i2cfd_Accel = DeviceManager::getI2CFD(LSM303_ADDRESS_ACCEL);
	}
	catch (...)
	{
		accelInit = false;
		accelAttached = false;
		robotLib->LogError("Could not initalize Accelerometer (Device not attached?)");
	}

	if (i2cfd_Accel == -1)
	{
		accelInit = false;
		accelAttached = false;
		robotLib->LogError("Could not initalize Accelerometer (Device not attached?)");
		return;
	}
	else
	{
		accelInit = true;
		robotLib->Log("Accelerometer initalized");
	}

	// Enable the accelerometer (100mhz)
	wiringPiI2CWriteReg16(i2cfd_Accel, LSM303_REGISTER_ACCEL_CTRL_REG1_A, 0x57);
	
	// LSM303DLHC has no WHOAMI register so read CTRL_REG1_A back to check
	// if we are connected or not
	uint8_t reg1_a = wiringPiI2CReadReg8(i2cfd_Accel, LSM303_REGISTER_ACCEL_CTRL_REG1_A);
	if (reg1_a != 0x57)
	{
		accelInit = false;
		robotLib->LogError("Failed to communicate with Accelerometer");
		return;
	}
	
	robotLib->Log("Communicating with accelerometer");
	accelInit = true;
	raw.x = 0;
	raw.y = 0;
	raw.z = 0;
}

void LSM303_Accelerometer::getSensor(sensor_t *sensor)
{
	memset(sensor, 0, sizeof(sensor_t));
	strncpy(sensor->name, "LSM303_Accelerometer", sizeof(sensor->name)-1);
	sensor->name[sizeof(sensor->name) - 1] = 0;
	sensor->version = 1;
	sensor->sensor_id = LSM303_ADDRESS_ACCEL;
	sensor->type = SENSOR_TYPE_ACCELEROMETER;
	sensor->min_delay = 0;
	sensor->max_value = 0.0F;		// TBD;
	sensor->min_value = 0.0F;		// TBD;
	sensor->resolution = 0.0F;		// TBD;	
}

bool LSM303_Accelerometer::getEvent(sensors_event_t* event)
{
	memset(event, 0, sizeof(sensors_event_t));
	
	/* Read new data */
	read();
	
	event->version = sizeof(sensors_event_t);
	event->sensor_id = LSM303_ADDRESS_ACCEL;
	event->type = SENSOR_TYPE_ACCELEROMETER;
	event->timestamp = getTimestamp();
	event->acceleration.x = static_cast<float>(raw.x)* _lsm303Accel_MG_LSB * SENSORS_GRAVITY_STANDARD;
	event->acceleration.y = static_cast<float>(raw.y)* _lsm303Accel_MG_LSB * SENSORS_GRAVITY_STANDARD;
	event->acceleration.z = static_cast<float>(raw.z)* _lsm303Accel_MG_LSB * SENSORS_GRAVITY_STANDARD;
	
	return true;
}

void LSM303_Accelerometer::read()
{
	wiringPiI2CWrite(i2cfd_Accel, LSM303_REGISTER_ACCEL_OUT_X_L_A | 0x80);
	int a = 0;
	uint8_t xlo, xhi, ylo, yhi, zlo, zhi;
		
	while (a < 6)
	{			
		int data = 0;
		data = wiringPiI2CReadReg8(i2cfd_Accel, LSM303_ADDRESS_ACCEL);
		if (data < 0)
		{
			robotLib->LogWarn("Error reading from accelerometer: %d" + data);
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
	
	raw.x = (int16_t)(xlo | (xhi << 8)) >> 4;
	raw.y = (int16_t)(ylo | (yhi << 8)) >> 4;
	raw.z = (int16_t)(zlo | (zhi << 8)) >> 4;
}

sensors_type_t LSM303_Accelerometer::getSensorType()
{
	return SENSOR_TYPE_ACCELEROMETER;
}

std::string  LSM303_Accelerometer::getDeviceName()
{
	return "LSM303 Accelerometer";
}

void LSM303_Accelerometer::calibrate()
{
	sensors_event_t* event = new sensors_event_t();
	int a = 0;
	float AccelMinX, AccelMaxX;
	float AccelMinY, AccelMaxY;
	float AccelMinZ, AccelMaxZ;
	
	while (a < 30)
	{		
		getEvent(event);
		if (event->acceleration.x < AccelMinX)
		{
			AccelMinX = event->acceleration.x;			
		}
		if (event->acceleration.x > AccelMaxX)
		{
			AccelMaxX = event->acceleration.x;			
		}
		if (event->acceleration.y < AccelMinY) 
		{
			AccelMinY = event->acceleration.y;
		}
		if (event->acceleration.y > AccelMaxY)
		{
			AccelMaxY = event->acceleration.y;
		}
		if (event->acceleration.z < AccelMinZ) 
		{
			AccelMinZ = event->acceleration.z;
		}
		if (event->acceleration.z > AccelMaxZ) 
		{
			AccelMaxZ = event->acceleration.z;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		a++;
	}
	delete(event);
}

// All devices require a static getDeviceStatus function
// Logic for detection:
//	  Interrogation is done by:
//		1. If we are previously init, return DEVICE_AVAILABLE
//		2. If we are previously attached, return DEVICE_CONNECTED
//		3. Otherwise try and init
device_status_t LSM303_Accelerometer::getDeviceStatus(RobotLib *robotLib)
{
	if (accelInit)
		return device_status_t::DEVICE_AVAILABLE;
	if (accelAttached)
		return device_status_t::DEVICE_CONNECTED;
	int i2cfd = i2cfd_Accel;
	if (i2cfd <= 0)
	{
		i2cfd = DeviceManager::getI2CFD(LSM303_ADDRESS_ACCEL);		
	} 
	if (i2cfd < 0)
	{
		return device_status_t::DEVICE_UNAVAILBLE;		
	}
	return device_status_t::DEVICE_CONNECTED;
}

std::string LSM303_Accelerometer::getDeviceDescription()
{
	return "LSM303 based Accelerometer";
}

LSM303_Accelerometer::~LSM303_Accelerometer()
{	
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(LSM303_Accelerometer);