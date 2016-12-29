#pragma once
#include "stdio.h"
#include <cstdio>
#include <sstream>
#include <cstring>
#include <chrono>
#include <thread>
#include <cstdint>
#include <unistd.h>
#include <cerrno>
#include <string.h>
#include <errno.h>
#include "ArduCamDriver/arducamDriver.h"
#include "SensorBase.h"
#include "arducam_arch_raspberrypi.c"
#include "arducamDriver.c"
#include "../../RobotLib/DeviceRegistry.h"

#define OV2640_CHIPID_HIGH  0x0A
#define OV2640_CHIPID_LOW   0x0B
#define OV5642_CHIPID_HIGH 0x300a
#define OV5642_CHIPID_LOW 0x300b

class ArduCam : public SensorBase
{
	public:
		ArduCam(RobotLib *robotLib);
		ArduCam(RobotLib *robotLib, uint8_t i2caddress);
		ArduCam(RobotLib *robotLib, uint8_t i2caddress, sensor_model_t cameraSensor);
	
		~ArduCam()
		{
		}
		
		device_type_t getDeviceType() override
		{
			return device_type_t::DEVICETYPE_SENSOR;
		}
	
		std::string getDeviceName() override
		{
			return "ArduCam";
		}
	
		std::string getDeviceDescription() override
		{
			return "ArduCam";
		};
			
		sensors_type_t getSensorType() override
		{
			return sensors_type_t::SENSOR_TYPE_IMAGING;
		}
	
		static device_status_t getDeviceStatus(RobotLib *robotLib);	
		void setCameraSensor(sensor_model_t cameraSensor);
		void setImageFormat(image_format_t imageFormat);
		void setImageSize(jpeg_size_t imageSize);
		bool getEvent(sensors_event_t *event) override;
	
	private:
		void initialize(uint8_t i2caddress);
		bool initSensor();		
		static bool initI2C(uint8_t i2cAddr);		
		static bool initSPI();
		static struct CAM arduCam;
		static bool chipTest();
		
		static uint8_t sensorAddr;
		static uint8_t i2cfd, spifd, spiCS;	
		static sensor_model_t cameraSensor;
		jpeg_size_t imageSize;
		image_format_t imageFormat = image_format_t::fmtBMP;
		bool initialized = false;
};

