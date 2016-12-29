#include "DeviceRegistry.h"

DeviceRegistry& DeviceRegistry::get()
{
	static DeviceRegistry instance;
	return instance;
}

void DeviceRegistry::add(device_creator creator)
{
	m_devices.push_back(creator);
}

DeviceRegistry::it DeviceRegistry::begin()
{
	return m_devices.begin();
}

DeviceRegistry::it DeviceRegistry::end()
{
	return m_devices.end();
}

DeviceRegistration::DeviceRegistration(device_creator creator)
{
	DeviceRegistry::get().add(creator);
}