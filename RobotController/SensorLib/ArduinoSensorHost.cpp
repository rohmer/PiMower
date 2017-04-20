#include "ArduinoSensorHost.h"

ArduinoSensorHost::ArduinoSensorHost(RobotLib *robotLib)
	: DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	this->initialized = false;
	i2caddr = 0x44;
	i2cfd = wiringPiI2CSetup(i2caddr);
	if (i2cfd <= 0)
	{
		std::stringstream ss;
		ss << "Failed to open I2C Bus on address: " << i2caddr;
		robotLib->LogError(ss.str());
	}
}

ArduinoSensorHost::ArduinoSensorHost(RobotLib *robotLib, uint8_t i2caddress)
	: DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	this->initialized = false;
	i2caddr = i2caddress;
	i2cfd = wiringPiI2CSetup(i2caddr);
	if (i2cfd <= 0)
	{
		std::stringstream ss;
		ss << "Failed to open I2C Bus on address: " << i2caddr;
		robotLib->LogError(ss.str());
	}
}
std::vector<std::string> ArduinoSensorHost::split(const std::string &s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector <std::string> tokens;
	while (getline(ss, item, delim))
	{
		tokens.push_back(item);
	}
	return tokens;
}

std::vector<ArduinoSensorHost::sSensorReturn> ArduinoSensorHost::getSensorValues()
{
	std::vector<ArduinoSensorHost::sSensorReturn> ret;
	ret.clear();

	// Ok, now everything is setup
	// Read a line from I2C
	char buf[255];
	read(i2cfd, buf, 255);
	std::string sensorLine(buf);
	sensorLine = sensorLine.substr(0, sensorLine.find('\n'));
	robotLib->Log(sensorLine);
	std::vector<std::string> tokens = split(sensorLine, '~');
	std::stringstream s;
	for (int a = 0; a < tokens.size(); a++)
	{
		robotLib->Log("Tokens: " + tokens[a]);
		if (tokens[a][0] == 'B')
		{
			//Button
			std::vector<std::string> buttons = split(tokens[a].substr(1), '|');
			for (int b = 0; b < buttons.size(); b++)
			{
				std::vector<std::string> numbers = split(buttons[b], ',');
				if (numbers.size() == 2)
				{
					sSensorReturn r;
					sSwitchReturn s;
					s.echoPin = std::atoi(numbers[0].c_str());
					if (numbers[1] == "1")
						s.value = true;
					else
						s.value = false;
					r.returnType = SWITCH;
					r.switchValue = s;
					ret.push_back(r);
				}
			}
		}
		if (tokens[a][0] == 'P')
		{
			robotLib->Log("Proximity: " + tokens[a]);
			std::vector<std::string> sensors = split(tokens[a].substr(1), '|');
			for (int b = 0; b < sensors.size(); b++)
			{
				std::string t = sensors[b];
				robotLib->Log(t);
				// Proximity sensor
				sSensorReturn r;
				sProximityReturn prox;
				r.returnType = PROXIMITY;
				std::vector<std::string> val = split(t, ',');
				if (val.size() == 3)
				{
					robotLib->Log(val[2]);
					prox.echoPin = std::atoi(val[0].c_str());
					prox.rawRange = std::atoi(val[1].c_str());
					prox.pingTime = std::atoll(val[2].c_str());
					if (prox.echoPin > 0)
					{
						prox.distanceCentimeters = round(prox.rawRange / 29.0 / 2);
						prox.distanceInches = round(prox.distanceCentimeters * 0.39370079);
						r.proximityValue = prox;
						ret.push_back(r);
					}
				}
			}
		}
	}
	robotLib->Log(sensorLine);

	return ret;
}

void ArduinoSensorHost::addSwitchSensor(uint8_t triggerPin)
{
	switchSensors.push_back(triggerPin);

	std::stringstream ss;
	ss << "S";
	for (int a = 0; a < switchSensors.size(); a++)
	{
		if (a > 0)
		{
			ss << ",";
		}
		ss << (int)switchSensors[a];
	}
#ifdef DEBUG
	robotLib->Log(ss.str());
#endif
	ss << "\0";
	int w = write(i2cfd, ss.str().c_str(), ss.str().length());
	if (w != ss.str().length())
	{
		std::stringstream eStr;
		eStr << i2cfd << " - Error writing to I2C, expected to write: " << ss.str().length() << ", actually wrote: " << w;
		robotLib->LogError(eStr.str());
	}
	delay(500);
}

void ArduinoSensorHost::addProximitySensor(uint8_t triggerPin, uint8_t echoPin)
{
	proximitySensors.push_back(std::make_pair(triggerPin, echoPin));
	if (this->proximitySensors.size() > 0)
	{
		std::stringstream ss;
		ss << "P";
		for (int a = 0; a < proximitySensors.size(); a++)
		{
			if (a != 0)
			{
				ss << "|";
			}
			ss << (int)proximitySensors[a].first << "," << (int)proximitySensors[a].second;
		}
#ifdef DEBUG
		robotLib->Log(ss.str());
#endif
		ss << "\0";
		int w = write(i2cfd, ss.str().c_str(), ss.str().length());
		if (w != ss.str().length())
		{
			std::stringstream eStr;
			eStr << i2cfd << " - Error writing to I2C, expected to write: " << ss.str().length() << ", actually wrote: " << w;
			robotLib->LogError(eStr.str());
		}
		initialized = true;
	}
	delay(500);
}