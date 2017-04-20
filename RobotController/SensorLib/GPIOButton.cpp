#include "GPIOButton.h"

GPIOButton::GPIOButton(RobotLib *robotLib)
	: DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	if (robotLib->getEmulator())
		return;
}

void GPIOButton::addButton(uint8_t pinNumber, std::string buttonName)
{
	if (buttons.find(pinNumber) != buttons.end())
	{
		std::stringstream ss;
		ss << "Redefining pin #" << pinNumber << ", was defined for: " << buttons.find(pinNumber)->second;
		robotLib->LogError(ss.str());
	}

	buttons.emplace(pinNumber, buttonName);
	pinMode(pinNumber, INPUT);
}

std::vector<std::string> GPIOButton::getButtonsPressed()
{
	std::vector<std::string> ret;
	std::map<uint8_t, std::string>::iterator it;
	for (it = buttons.begin(); it != buttons.end(); it++)
	{
		if (digitalRead(it->first) == 1)
			ret.push_back(it->second);
	}

	return ret;
}