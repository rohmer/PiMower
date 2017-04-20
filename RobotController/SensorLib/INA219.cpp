#include "INA219.h"

INA219::INA219(RobotLib *robotLib)
	: SensorBase(robotLib)
{
	initialized = false;
	if (robotLib->getEmulator())
	{
		initialized = true;
		return;
	}

	i2cfd = -1;
	i2cfd = DeviceManager::getI2CFD(0x40);
	if (i2cfd < 0)
	{
		initialized = false;
		return;
	}
	initialized = setCalibration_32V_2A();
}

INA219::INA219(RobotLib *robotLib, uint8_t i2cAddress)
	: SensorBase(robotLib)
{
	initialized = false;
	if (robotLib->getEmulator())
	{
		initialized = true;
		return;
	}

	i2cfd = -1;
	i2cfd = DeviceManager::getI2CFD(i2cAddress);
	if (i2cfd < 0)
	{
		initialized = false;
		return;
	}
	setCalibration_32V_2A();
}

bool INA219::setCalibration_32V_2A()
{
	ina219_calValue = 4096;
	ina219_currentDivider_mA = 10;  // Current LSB = 100uA per bit (1000/100 = 10)
	ina219_powerDivider_mW = 2;     // Power LSB = 1mW per bit (2/1)
	if (wiringPiI2CWriteReg16(i2cfd, INA219_REG_CALIBRATION, ina219_calValue) < 0)
		return false;
	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V |
                    INA219_CONFIG_GAIN_8_320MV |
                    INA219_CONFIG_BADCRES_12BIT |
                    INA219_CONFIG_SADCRES_12BIT_1S_532US |
                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
	if (wiringPiI2CWriteReg16(i2cfd, INA219_REG_CONFIG, config) < 0)
		return false;
	return true;
}

bool INA219::setCalibration_32V_1A()
{
	ina219_calValue = 10240;
	ina219_currentDivider_mA = 25;
	ina219_powerDivider_mW = 1;
	if (wiringPiI2CWriteReg16(i2cfd, INA219_REG_CALIBRATION, ina219_calValue) < 0)
		return false;
	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V |
                    INA219_CONFIG_GAIN_8_320MV |
                    INA219_CONFIG_BADCRES_12BIT |
                    INA219_CONFIG_SADCRES_12BIT_1S_532US |
                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
	if (wiringPiI2CWriteReg16(i2cfd, INA219_REG_CONFIG, config) < 0)
		return false;
	return true;
}

bool INA219::setCalibration_16V_400mA()
{
	ina219_calValue = 8192;
	ina219_currentDivider_mA = 20;
	ina219_powerDivider_mW = 1;
	if (wiringPiI2CWriteReg16(i2cfd, INA219_REG_CALIBRATION, ina219_calValue) < 0)
		return false;
	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V |
                    INA219_CONFIG_GAIN_8_320MV |
                    INA219_CONFIG_BADCRES_12BIT |
                    INA219_CONFIG_SADCRES_12BIT_1S_532US |
                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
	if (wiringPiI2CWriteReg16(i2cfd, INA219_REG_CONFIG, config) < 0)
		return false;
	return true;
}

std::string INA219::getDeviceName()
{
	return "INA219";
}

sensors_type_t INA219::getSensorType()
{
	return sensors_type_t::SENSOR_TYPE_CURRENT;
}

std::string INA219::getDeviceDescription()
{
	return "INA219 i2c current sensor";
}

device_status_t INA219::getDeviceStatus(RobotLib *robotLib)
{
	return device_status_t::DEVICE_UNKNOWN;
}

int16_t INA219::getBusVoltage_raw()
{
	uint16_t value = wiringPiI2CReadReg16(i2cfd, INA219_REG_BUSVOLTAGE);
	return (int16_t)((value >> 3) * 4);
}

int16_t INA219::getShuntVoltage_raw()
{
	uint16_t value = wiringPiI2CReadReg16(i2cfd, INA219_REG_SHUNTVOLTAGE);
	return (int16_t)value;
}

int16_t INA219::getCurrent_raw()
{
	wiringPiI2CWriteReg16(i2cfd, INA219_REG_CALIBRATION, ina219_calValue);
	uint16_t value = wiringPiI2CReadReg16(i2cfd, INA219_REG_CURRENT);
	return (int16_t)value;
}

float INA219::getShuntVoltage_mV()
{
	int16_t value = getShuntVoltage_raw();
	return value * 0.01;
}

float INA219::getBusVoltage_V()
{
	int16_t value = getBusVoltage_raw();
	return value * 0.001;
}

float INA219::getCurrent_mA()
{
	float valueDec = getCurrent_raw();
	valueDec /= ina219_currentDivider_mA;
	return valueDec;
}

bool INA219::getEvent(sensors_event_t *event)
{
	if (!event)
	{
		event = new sensors_event_t();
	}

	if (!initialized)
		return false;
	event->voltage = getBusVoltage_V();
	event->current = getCurrent_mA();
	return true;
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(INA219);