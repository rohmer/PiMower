#include "BQ34Z100G1.h"

BQ34Z100G1::BQ34Z100G1(RobotLib *robotLib) 
	: SensorBase(robotLib)
{
}

BQ34Z100G1::BQ34Z100G1(RobotLib *robotLib, uint8_t i2caddress)
	: SensorBase(robotLib)
{
}

std::string BQ34Z100G1::getDeviceName()
{
	return "BQ34Z100-G1";
}

bool BQ34Z100G1::getEvent(sensors_event_t *event)
{
	return event;
}

sensors_type_t BQ34Z100G1::getSensorType()
{
	return sensors_type_t::SENSOR_TYPE_VOLTAGE;
}

std::string BQ34Z100G1::getDeviceDescription()
{
	return "BQ34Z100-G1 Battery Gauge";
}

device_status_t BQ34Z100G1::getDeviceStatus(RobotLib *robotLib)
{
	return device_status_t::DEVICE_UNKNOWN;
}

// TODO: Actually get the pct
uint8_t BQ34Z100G1::getPctRemaining()
{
	return 100;
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(BQ34Z100G1);