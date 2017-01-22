#pragma once
#include <vector>
#include <sstream>
#include <errno.h>
#include <string.h>
#include <cmath>
#include <thread>
#include "SensorBase.h"
#include "../../RobotLib/DeviceRegistry.h"
#include "SensorBase.h"
#include <vector>
#include "wiringPi.h"

/* Driver for HC-SR04 Ultrasonic Range Finder */
class HCSR04 : public SensorBase
{
	public:
		HCSR04(RobotLib *robotLib);
		HCSR04(RobotLib *robotLib, uint8_t triggerPin, uint8_t inputPin);
		HCSR04(RobotLib *robotLib, uint8_t triggerPin, uint8_t inputPin, 
			bool backgroundPoling, uint16_t pollingInterval);
		~HCSR04();	
		device_type_t getDeviceType() override
		{
			return device_type_t::DEVICETYPE_SENSOR;
		}
		std::string getDeviceName() override
		{
			return "HC-SR04";
		}
		std::string getDeviceDescription() override
		{
			return "HC-SR04 ultrasonic range finder";
		}
		static device_status_t getDeviceStatus(RobotLib *robotLib) 
		{
			// We cant really autodetect this
			return device_status_t::DEVICE_UNKNOWN;
		}		
		sensors_type_t getSensorType() override
		{
			return SENSOR_TYPE_PROXIMITY;
		}
		bool getEvent(sensors_event_t *event) override;		// Gets the result of the first sensor
		bool getEvent(int sensorNum, sensors_event_t *event);
		void setTriggerPin(uint8_t triggerPin);
		uint8_t getTriggerPin();
		void addSensor(uint8_t inputPin);					// Adds a sensor to background polling
		uint8_t getInputPin();
		void setMaxDistanceCM(uint16_t centimeters);
		void setMaxDistanceInches(uint16_t inches);
		void setBackgroundPolling(bool enabled);			// Turns on or off background polling
	
	private:
		void bgPollingThread();
		static void startPollingThread(HCSR04 *hcsr04);
	
		void pollDevice();
	
		uint8_t triggerPin, inputPin;
		bool initialized;
		bool backgroundPolling, shutdown;
		uint16_t pollingInterval;
		std::thread pollingThread;
		uint16_t maxDistance;
		uint16_t distanceIN, distanceCM;
		std::vector<long> sensorResult;		
};