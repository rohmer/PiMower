#include "Configuration.h"
#include "../RobotController/SensorLib/HCSR04.h"

Configuration::Configuration(RobotLib *robotLib)
{
	this->robotLib = robotLib;
#ifdef DEBUG
	minimumLoggingLevel = min_log_level_t::Debug;
#else
	minimumLoggingLevel = min_log_level_t::Warn;
#endif
	validConfig = getConfig();
}

/* Config Format 
<PiMowerConfig>
	<Sensors>
		<Sensor name="SomeSensor" ID=Number type=number>
			<Pin type=number pinNumber=number shared=bool/>
		</Sensor>
	</Sensors>
</PiMowerConfig>
*/

bool Configuration::getConfig()
{
	std::ifstream configFile(CONFIG_FILE);
	if (!configFile.good())
	{
		robotLib->LogError("Configuration file does not exist.");
		return false;
	}
	
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> *rootNode;
	
	std::vector<char> buffer((std::istreambuf_iterator<char>(configFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	
	rootNode = doc.first_node("PiMowerConfig");
	if (!rootNode)
	{
		robotLib->LogError("Configuration file does not have a root node of PiMowerConfig");
		return false;
	}
	
	std::stringstream ss;
	rapidxml::xml_node<> *sensorsNode = rootNode->first_node("Sensors");
	if (!sensorsNode)
	{
		robotLib->LogError("Configuration file does not have a Sensors Node");
		return false;		
	}
	
	for (rapidxml::xml_node<> *sensorNode = sensorsNode->first_node("Sensor"); sensorNode; sensorNode = sensorNode->next_sibling())
	{
		sensor_struct sensor;
#ifdef DEBUG
		ss << "Sensor Node: " << sensorNode->first_attribute("type")->value();
		robotLib->Log(ss.str());
		ss.clear();
#endif
		int sensorT = (std::stoi(sensorNode->first_attribute("type")->value()));
		switch (sensorT)
		{
			case 1:
				sensor.sensorType = sensor_type_t::SonorProximityGPIO;
				break;
			case 2:
				sensor.sensorType = sensor_type_t::Color;
				break;
			case 3:
				sensor.sensorType = sensor_type_t::Gyroscope;
				break;
			case 4:
				sensor.sensorType = sensor_type_t::Gyroscope;
				break;
			case 5:
				sensor.sensorType = sensor_type_t::GPS;
				break;
			case 6:
				sensor.sensorType = sensor_type_t::Switch;
				break;
			case 7:
				sensor.sensorType = sensor_type_t::Accelerometer;
				break;
			case 8:
				sensor.sensorType = sensor_type_t::Moisture;
				break;
			default:
				ss << "Unknown sensor type: " << sensorT;
				robotLib->LogError(ss.str());
				sensor.sensorType = sensor_type_t::Unknown;
				break;
		}
		sensor.id = (std::stoi(sensorNode->first_attribute("ID")->value()));
		sensor.name = sensorNode->first_attribute("name")->value();
		for (rapidxml::xml_node<> *pinNode = sensorNode->first_node("Pin"); pinNode; pinNode = pinNode->next_sibling())
		{
			pin_struct pin;
			int pint = std::stoi(pinNode->first_attribute("type")->value());
			switch (pint)
			{
				case 1:
					pin.pinType = pin_type_t::triggerPin;
					break;
				case 2:
					pin.pinType = pin_type_t::analogInputPin;
					break;
				case 3:
					pin.pinType = pin_type_t::digitalInputPin;
					break;
				default:
					pin.pinType = pin_type_t::unknown;
					break;
			}
			pin.pinNumber = std::stoi(pinNode->first_attribute("pinNumber")->value());
			if (pinNode->first_attribute("shared"))
				pin.sharedPin = true;
			else
				pin.sharedPin = false;
			sensor.pins.emplace_back(pin);
			sensors.push_back(sensor);
		}				
	}
}

void Configuration::initSensors()
{
	HCSR04 *gpioSonor = NULL;		
	for (int a = 0; a < sensors.size(); a++)
	{
#if DEBUG
		std::stringstream ss;
		ss << "Trying to init: " << sensors[a].name;
		robotLib->Log(ss.str());
#endif				
		switch (sensors[a].sensorType)
		{
			case(sensor_type_t::SonorProximityGPIO):
			{
				int triggerPin=-1, inputPin=-1;
				for (int b = 0; b < sensors[a].pins.size(); b++)
				{
					if (sensors[a].pins[b].pinType == pin_type_t::triggerPin)
						triggerPin = sensors[a].pins[b].pinNumber;
					if (sensors[a].pins[b].pinType == pin_type_t::digitalInputPin)
						inputPin = sensors[a].pins[b].pinNumber;
				}
				if (inputPin == -1 || triggerPin == -1)
				{					
					if (inputPin == -1)
					{
						robotLib->LogError("Sonor Proximity Sensor defined without a digital input pin, will not be used");
					}
					else
					{					
						robotLib->LogError("Sonor Proximity Sensor defined without a trigger pin, will not be used");
					}
				}
				else
				{
					// Add the pin to polling
					if (gpioSonor == NULL)
					{						
						gpioSonor = reinterpret_cast<HCSR04*>(robotLib->getDeviceManager()->getByName("HC-SR04"));
						gpioSonor->setTriggerPin(triggerPin);
						gpioSonor->addSensor(inputPin);
					}
				}
			}
		}
	}
	if (gpioSonor)
	{
		// We defined gpio Sonor, so lets start background polling
		gpioSonor->setBackgroundPolling(true);
	}
}