#pragma once
#include "SensorLib.h"
#include "SensorBase.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPiI2C.h"
#include <stdio.h>
#include <sstream>
#include <cstring>
#include <chrono>
#include <thread>
#include <stdint.h>
#include "../../RobotLib/DeviceRegistry.h"

// Driver for PCA9685 I2C to PWM Servo Driver
#define PCA9685_MODE1 0x00		// location for Mode1 register address
#define PCA9685_MODE2 0x01		// location for Mode2 reigster address
#define PCA9685_PRESCALE 0xFE
#define PCA9685_LED0 0x06		// location for start of LED0 registers
#define PCA9685_LEDALL_ON 0xFA	

#define PCA9685_I2C_MIN 0x40		// I2C Address Minimum for PCA9685
#define PCA9685_I2C_MAX 0x40+0x02	// I2C Address Maximum for PCA9685
#define PIN_ALL 16

class PCA9685 : public DeviceBase
{
	public:
		PCA9685(RobotLib *robotLib);
		PCA9685(RobotLib *robotLib, uint8_t i2caddress);
		
		~PCA9685();
		device_type_t getDeviceType() override
		{
			return device_type_t::DEVICETYPE_OUTPUT;
		}
	
		std::string getDeviceName() override
		{
			return "PCA9685";
		};
	
		std::string getDeviceDescription() override
		{
			return "PCA9685 I2C to PWM Driver";
		}
		
		static device_status_t getDeviceStatus(RobotLib *robotLib);		
		void pca9685PWMFreq(float frequency);
		static void pca9685FullOn(int fd, int pin, int tf);
		static void pca9685FullOff(int fd, int pin, int tf);
		static void pca9685PWMRead(int fd, int pin, int *on, int *off);
		static void pca9685PWMWrite(int fd, int pin, int on, int off);
		void pca9685PWMReset(int fd);
		static uint8_t scanForPCA9685();
	
	private:
		int i2cfd;
		static uint8_t pca9685I2CAddr;
		bool pca9685Avail;		
		void initialize();		
		static int baseReg(int pin);
		static bool initialized;
	
		// wiringPi functions
		static void pPwmWrite(struct wiringPiNodeStruct *node, int pin, int value);
		static int pOffRead(struct wiringPiNodeStruct *node, int pin);
		static int pOnRead(struct wiringPiNodeStruct *node, int pin);
		static void pOnOffWrite(struct wiringPiNodeStruct *node, int pin, int value);

};