#pragma once
#include <vector>
#include <sstream>
#include <errno.h>
#include <string.h>
#include <cmath>
#include "DeviceBase.h"
#include "SensorBase.h"
#include "../../RobotLib/DeviceRegistry.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPiI2C.h"

// Driver for an arduino sensor host

class ArduinoSensorHost : DeviceBase
{
public:
	enum eReturnType
	{
		PROXIMITY,
		SWITCH
	};

	struct sProximityReturn
	{
		uint8_t echoPin;
		unsigned long rawRange;
		long long pingTime;
		int distanceInches, distanceCentimeters;
	};
	struct sSwitchReturn
	{
		uint8_t echoPin;
		bool value;
	};

	struct sSensorReturn
	{
		eReturnType returnType;
		sProximityReturn proximityValue;
		sSwitchReturn switchValue;
	};

	ArduinoSensorHost(RobotLib *robotLib);
	ArduinoSensorHost(RobotLib *robotLib, uint8_t i2caddress);
	device_type_t getDeviceType() override
	{
		return device_type_t::DEVICETYPE_IO;
	}
	std::string getDeviceName() override
	{
		return "ArduinoSensorHost";
	}
	std::string getDeviceDescription() override
	{
		return "Arduino Sensor Aggrigator";
	}
	static device_status_t getDeviceStatus(RobotLib *robotLib)
	{
		// We cant really autodetect this
		return device_status_t::DEVICE_UNKNOWN;
	}

	void addProximitySensor(uint8_t triggerPin, uint8_t echoPin);
	void addSwitchSensor(uint8_t triggerPin);

	void clearProximitySensors()
	{
		proximitySensors.clear();
		initialized = false;
	}
	std::vector<sSensorReturn> getSensorValues();

private:
	// V1 I am only supporting sonar proximity sensors and switches
	uint8_t i2caddr;
	uint8_t i2cfd;
	std::vector <std::pair<uint8_t, uint8_t> > proximitySensors;		// First is trigger, second is echo
	bool initialized = false;
	std::vector<uint8_t> switchSensors;

	std::vector<std::string> split(const std::string &s, char delim);
};