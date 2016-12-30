#include "DeviceManager.h"

TEST_GROUP(DeviceManagerTests)
{
	void setup()
	{
		dmRobotLib = new RobotLib();
	}
	
	void teardown()
	{
		delete(dmRobotLib);
	}	
};

TEST(DeviceManagerTests, Initialization)
{
	if (!dmRobotLib)
	{
		FAIL("RobotLib is not initialized");
	}
	if (!dmRobotLib->getDeviceManager())
	{
		FAIL("DeviceManager is not initialized");
	}
}
;

TEST(DeviceManagerTests, EmulatedMode)
{
	if (!dmRobotLib->getEmulator())
	{
		FAIL("Not running in emulated mode, expected if running on a Pi");
	}
}


TEST_GROUP(DeviceManagerEnumerationTests)
{
	void setup()
	{
		dmRobotLib = new RobotLib();
	}
	
	void teardown()
	{
		delete(dmRobotLib);
	}	
}
;


TEST(DeviceManagerEnumerationTests, AdafruitGPS)
{
	DeviceEntry *de;
	de = dmRobotLib->getDeviceManager()->getByName("Adafruit GPS");
	if (de == NULL)
	{
		FAIL("Failed to enumerate Adafruit GPS in Device Manager");
	}
}


TEST(DeviceManagerEnumerationTests, ArduCam)
{
	DeviceEntry *de;
	de = dmRobotLib->getDeviceManager()->getByName("ArduCam");
	if (de == NULL)
	{
		FAIL("Failed to enumerate ArduCam in Device Manager");
	}
}


TEST(DeviceManagerEnumerationTests, HCSR04)
{
	DeviceEntry *de;
	de = dmRobotLib->getDeviceManager()->getByName("HCSR04");
	if (de == NULL)
	{
		FAIL("Failed to enumerate HCSR04 in Device Manager");
	}
}

TEST(DeviceManagerEnumerationTests, LSM303Accel)
{
	DeviceEntry *de;
	de = dmRobotLib->getDeviceManager()->getByName("LSM303 Accelerometer");
	if (de == NULL)
	{
		FAIL("Failed to enumerate LSM303 Accelerometer in Device Manager");
	}
}

TEST(DeviceManagerEnumerationTests, LSM303Magnetom)
{
	DeviceEntry *de;
	de = dmRobotLib->getDeviceManager()->getByName("LSM303 Magnetometer");
	if (de == NULL)
	{
		FAIL("Failed to enumerate LSM303 Magnetometer in Device Manager");
	}
}