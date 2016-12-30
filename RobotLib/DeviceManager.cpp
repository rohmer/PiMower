#include "DeviceManager.h"
#include "DeviceRegistry.h"
#include "../3rdParty/wiringPi/wiringPi/wiringSerial.h"
#include "../3rdParty/wiringPi/wiringPi/wiringPiI2C.h"
#include "../3rdParty/wiringPi/wiringPi/wiringPiSPI.h"

std::map <std::string, uint8_t> DeviceManager::serialfd;
std::map<uint8_t, uint8_t> DeviceManager::i2cfd, DeviceManager::spifd;

DeviceManager::DeviceManager(RobotLib &rl)
{
	this->robotLib = &rl;	
	robotLib->Log("DeviceManager initalized");
	initialize();
}

DeviceManager::~DeviceManager()
{
	std::vector<DeviceEntry*>::iterator it;
	for (it = devices.begin(); it != devices.end(); it++)
	{
		DeviceEntry *de = *it;
		delete(de);
	}
	std::map<std::string, uint8_t>::iterator iter;
	for (iter = serialfd.begin(); iter != serialfd.end(); iter++)
		serialClose(iter->second);
	std::map<uint8_t, uint8_t>::iterator i;
	for (i = i2cfd.begin(); i != i2cfd.end(); i++)
		close(i->second);
	for (i = spifd.begin(); i != spifd.end(); i++)
		close(i->second);
	
}

uint8_t DeviceManager::getSerialFD(std::string dev,int baud)
{
	std::map<std::string, uint8_t>::iterator it = serialfd.find(dev);
	if (it != serialfd.end())
		return serialfd[dev];
	int fd = serialOpen(dev.c_str(),baud);
	if (fd > 0)
	{
		serialfd[dev] = fd;
		return fd;
	}
	
	return -1;
}

uint8_t DeviceManager::getI2CFD(uint8_t dev)
{
	std::map<uint8_t, uint8_t>::iterator it = i2cfd.find(dev);
	if (it != i2cfd.end())
		return i2cfd[dev];
	int fd = wiringPiI2CSetup(dev);
	if (fd > 0)
	{
		i2cfd[dev] = fd;
		return fd;
	}
	
	return -1;
}

uint8_t DeviceManager::getSPIFD(uint8_t dev, int speed)
{
	std::map<uint8_t, uint8_t>::iterator it = spifd.find(dev);
	if (it != spifd.end())
		return spifd[dev];
	int fd = wiringPiSPISetup(dev,speed);
	if (fd > 0)
	{
		spifd[dev] = fd;
		return fd;
	}
	
	return -1;
}

// Iterate through all of the devices we have drivers for
// and add them to the registry
void DeviceManager::initialize()
{
	DeviceRegistry& registry(DeviceRegistry::get());
	for (DeviceRegistry::it it = registry.begin(); it != registry.end(); it++)
	{
		device_creator func = *it;
		DeviceBase* _ptr = func(robotLib);		
		DeviceEntry *de = new DeviceEntry(robotLib, _ptr);
		devices.push_back(de);
	}
}

std::vector<DeviceEntry*> DeviceManager::getByType(device_type_t deviceType)
{
	std::vector<DeviceEntry*> returnVal;
	for (int i = 0; i < devices.size(); i++)
	{
		if (devices[i]->getDeviceType() == deviceType)
		{
			returnVal.insert(returnVal.end(),devices[i]);
		}
	}
	return returnVal;
}

std::vector<DeviceEntry*> DeviceManager::getByCap(sensors_type_t capability)
{
	std::vector<DeviceEntry*> returnVal;
	for (int i = 0; i < devices.size(); i++)
	{
		DeviceBase* db = devices[i]->getDevice();
		SensorBase *sb = dynamic_cast<SensorBase*>(db);
		if (sb)
		{
			if (sb->getSensorType() == capability)
			{
				returnVal.insert(returnVal.end(), devices[i]);
			}
		}
	}	
	return returnVal;
}

DeviceEntry* DeviceManager::getByName(std::string name)
{
	for (int i = 0; i < devices.size(); i++)
	{
		DeviceBase* db=devices[i]->getDevice();
		SensorBase *sb = dynamic_cast<SensorBase*>(db);
		if (sb)
		{
			if (sb->getSensorName() == name)
			{
				return devices[i];
			}
		}
		else
		{
			if (db->getDeviceName() == name)
				return devices[i];
		}
	}
	return NULL;
}