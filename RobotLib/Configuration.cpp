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

//TODO: Set all node names and attribute names to Case Insensitive
//TODO: The current returning of false is flawed, it wont work right
//		if some things are set and others are not

/* Config Format 
<PiMowerConfig>
	<Logging Level="DEBUG|WARN|CRITICAL|EXCEPTION"/>
	<Physical DriveWheelDiameter=NumberInches DriveGearRatio=FLOAT DriveMotorMaxRPM=uint/>		
	<Sensors>
		<PWMController i2cAddr="someNumber">
			<ControlChannels leftDriveChannel="someNumber" rightDriveChannel="someNumber" bladeChannel="someNumber"/>
		<PWMController>		
		<BumperSensor GPIOPin=number Location=FRONT|BACK/>
		<ArduinoHost i2caddress="addressnum" ProximityTollerance="float">
			<Proximity triggerPin="num" echoPin="num" name="FrontSensor"/>
		</ArduinoHost>
	</Sensors>
	<Speed>
		<NormalOperation ForwardRPM=number ReverseRPM=number RotationRPM=number/>
		<ObjectDetection ForwardRPM=number ReverseRPM=number/>
		<Acceleration Normal=INT(Seconds to full speed) Rotational=INT(Seconds to full speed)/>			
	</Speed>
	<MotorEncoder leftPin=number rightPin=number/>
		
</PiMowerConfig>
*/

bool Configuration::getConfig()
{
	return getConfig(CONFIG_FILE);
}

bool Configuration::getConfig(std::string cfgFile)
{
	bool writeConfig = false;
	
	std::ifstream configFile(cfgFile);
	if (!configFile.good())
	{
		robotLib->LogError("Configuration file does not exist.");
		writeConfig = true;
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

	if (!readSensors(rootNode))
	{
		writeConfig = true;
	}
	// If we fail somewhere to read something, we will rewrite the config
	if (!readSpeed(rootNode))
	{
		writeConfig = true;
	}
	
	if (!readLogLevel(rootNode))
	{
		writeConfig = true;
	}
	
	if (!readPhysical(rootNode))
	{
		writeConfig = true;
	}
	if (writeConfig)
	{
		writeConfiguration();
		return false;
	}
	
	return true;
}

bool Configuration::readPhysical(rapidxml::xml_node<> *rootNode)
{
	rapidxml::xml_node<> *pNode = rootNode->first_node("Physical");
	if (!pNode)
	{
		robotLib->LogError("A physical node is required!");
		return false;
	}
	if (!pNode->first_attribute("DriveWheelDiameter"))
	{
		robotLib->LogError("DriveWheelDiameter under Physical node is required");
		return false;
	}
	if (!pNode->first_attribute("DriveGearRatio"))
	{
		robotLib->LogError("DriveGearRatio under Physical node is required");
		return false;
	}
	driveGearRatio = std::atof(pNode->first_attribute("DriveGearRatio")->value());
	if (!pNode->first_attribute("DriveMotorMaxRPM"))
	{
		robotLib->LogError("DriveMotorMaxRPM under Physical node is required");
		return false;
	}
	driveMotorMaxRPM = std::atoi(pNode->first_attribute("DriveMotorMaxRPM")->value());
}

bool Configuration::readLogLevel(rapidxml::xml_node<> *rootNode)
{
	rapidxml::xml_node<> *logNode = rootNode->first_node("Logging");
	if (!logNode)
	{
		robotLib->LogWarn("No Logging Node, setting defaults");		
		return false;
	}
	if (!logNode->first_attribute("Level"))
	{
		robotLib->LogWarn("No Level attribute under Logging Node, setting defaults");		
		return false;
	}
	std::string level(logNode->first_attribute("Level")->value());
	std::transform(level.begin(), level.end(),level.begin(),::toupper);
	if (level == "DEBUG")
		minimumLoggingLevel = min_log_level_t::Debug;
	else
		if (level == "WARN")
		minimumLoggingLevel = min_log_level_t::Warn;
	else
		if (level == "CRITICAL")
		minimumLoggingLevel = min_log_level_t::Critical;
	else
		if (level == "EXCEPTION")
		minimumLoggingLevel = min_log_level_t::Exception;
	else
	{
		std::stringstream ss;
		ss << "Unrecognized logging level (" << level << "), must be one of DEBUG|WARN|CRITICAL|EXCEPTION";
		robotLib->LogWarn(ss.str());
		robotLib->Log("Setting to default: WARN");
		minimumLoggingLevel = min_log_level_t::Warn;
	}
	return true;
}

bool Configuration::readSpeed(rapidxml::xml_node<> *rootNode)
{
	rapidxml::xml_node<> *speedNode = rootNode->first_node("Speed");
	if (!speedNode)
	{
		robotLib->LogWarn("No Speed Node, setting defaults");
		setDefaultSpeed();
		return false;
	}
	rapidxml::xml_node<> *normalNode = speedNode->first_node("NormalOperation");
	if (!normalNode)
	{
		robotLib->LogWarn("No NormalOperaiton speed node, setting defaults");		
		setDefaultSpeed();
		return false;
	}
	if (normalNode->first_attribute("ForwardRPM"))
	{
		normalOperationSpeed.forwardRPM = setPctValue(std::stoi(normalNode->first_attribute("ForwardRPM")->value()));
	}
	else
	{
		robotLib->LogWarn("No NormalOperaiton, forwardRPM speed node, setting defaults");		
		setDefaultSpeed();
		return false;
	}
	if (normalNode->first_attribute("ReverseRPM"))
	{
		normalOperationSpeed.reverseRPM = setPctValue(std::stoi(normalNode->first_attribute("ReverseRPM")->value()));
	}
	else
	{
		robotLib->LogWarn("No NormalOperaiton, reverseRPM speed node, setting defaults");		
		setDefaultSpeed();
		return false;
	}
	if (normalNode->first_attribute("RotationRPM"))
	{
		normalOperationSpeed.rotationRPM = setPctValue(std::stoi(normalNode->first_attribute("rotationRPM")->value()));
	}
	else
	{
		robotLib->LogWarn("No NormalOperaiton, rotationRPM speed node, setting defaults");		
		setDefaultSpeed();
		return false;
	}
	
	rapidxml::xml_node<> *objectNode = speedNode->first_node("ObjectDetection");
	if (!objectNode)
	{
		robotLib->LogWarn("No ObjectDetection speed node, setting defaults");		
		setDefaultSpeed();
		return false;
	}
	if (objectNode->first_attribute("ForwardRPM"))
	{
		objectDetectionSpeed.forwardRPM = setPctValue(std::stoi(normalNode->first_attribute("ForwardRPM")->value()));
	}
	else
	{
		robotLib->LogWarn("No ObjectDetection, forwardRPM speed node, setting defaults");		
		setDefaultSpeed();
		return false;
	}
	if (objectNode->first_attribute("ReverseRPM"))
	{
		objectDetectionSpeed.reverseRPM = setPctValue(std::stoi(normalNode->first_attribute("ReverseRPM")->value()));
	}
	else
	{
		robotLib->LogWarn("No ObjectDetection, reverseRPM speed node, setting defaults");		
		setDefaultSpeed();
		return false;
	}	
	
	//<Acceleration Normal=INT(Seconds to full speed) Rotational=INT(Seconds to full speed)/>			
	rapidxml::xml_node<> *accNode = speedNode->first_node("Acceleration");
	if (!accNode)
	{
		robotLib->Log("No Acceleration node under Speed, setting defaults");
		return false;
	}
	if (accNode->first_attribute("Normal",0,false))
	{
		normalAcceleration = std::atoi(accNode->first_attribute("Normal", 0, false)->value());		
	}
	else
	{
		robotLib->Log("No Normal Acceleration attribute, setting to defaults");
		return false;
	}
	if (accNode->first_attribute("Rotational", 0, false))
	{
		rotationalAcceleration = std::atoi(accNode->first_attribute("Rotational", 0, false)->value());		
	}
	else
	{
		robotLib->Log("No Normal Acceleration attribute, setting to defaults");
		return false;
	}
	return true;
}

bool Configuration::readSensors(rapidxml::xml_node<> *rootNode)
{
	rapidxml::xml_node<> *sensorsNode = rootNode->first_node("Sensors");
	if (!sensorsNode)
	{
		robotLib->LogError("No Sensors Node, configuration needs to be set");		
		return false;
	}
	
	rapidxml::xml_node<> *pwmNode = sensorsNode->first_node("PWMController");
	if (!pwmNode)
	{
		robotLib->LogError("No PWMController node, needs to be set in configuration");
		return false;
	}
	
	if (!pwmNode->first_attribute("i2cAddr"))	
	{
		robotLib->LogError("PWMController does not have attribute i2cAddr set");
		return false;
	}
	
	int i2caddr = std::atoi(pwmNode->first_attribute("i2cAddr")->value());
	if (i2caddr<0 || i2caddr>127)
	{
		std::stringstream ss;
		ss << "Address for PWMController (" << i2caddr << ") out of range 0<<x<127";
		robotLib->LogError(ss.str());
		return false;
	}
	pwmController.i2cChannel = i2caddr;
	rapidxml::xml_node<> *controlNode = pwmNode->first_node("ControlChannels");
	if (!controlNode)
	{
		robotLib->LogError("ControlChannels node not defined in PWMController");
		return false;
	}
	//<ControlChannels leftDriveChannel="someNumber" rightDriveChannel="someNumber" bladeChannel="someNumber"/>
	if (!controlNode->first_attribute("leftDriveChannel"))
	{
		robotLib->LogError("leftDriveChannel not defined in PWMController");
		return false;
	}
	int val = std::atoi(controlNode->first_attribute("leftDriveChannel")->value());
	if(val<0 || val > 15)
	{
		std::stringstream ss;
		ss << "Left drive channel out of range: " << val << ", range is 0<=x<=15";
		robotLib->LogError(ss.str());
		return false;
	}
	pwmController.leftDriveChannel = val;
	if (!controlNode->first_attribute("rightDriveChannel"))
	{
		robotLib->LogError("rightDriveChannel not defined in PWMController");
		return false;
	}
	val = std::atoi(controlNode->first_attribute("rightDriveChannel")->value());
	if (val<0 || val > 15)
	{
		std::stringstream ss;
		ss << "Right drive channel out of range: " << val << ", range is 0<=x<=15";
		robotLib->LogError(ss.str());
		return false;
	}
	pwmController.rightDriveChannel = val;
	
	if (!controlNode->first_attribute("bladeChannel"))
	{
		robotLib->LogError("bladeChannel not defined in PWMController");
		return false;
	}
	val = std::atoi(controlNode->first_attribute("bladeChannel")->value());
	if (val<0 || val > 15)
	{
		std::stringstream ss;
		ss << "blade channel out of range: " << val << ", range is 0<=x<=15";
		robotLib->LogError(ss.str());
		return false;
	}
	pwmController.bladeChannel = val;
	
	// BumperSensors
	// 		<BumperSensor GPIOPin=number Location=FRONT|BACK/>
	rapidxml::xml_node<> *bumperNode = sensorsNode->first_node("BumperSensor");
	if (!bumperNode)
	{
		robotLib->LogError("No bumper sensors defined, this is unsafe operation and will not run");
		return false;
	}
	bool foundNode = false;
	for (rapidxml::xml_node<> *bumperDef = bumperNode->first_node("BumperSensor"); bumperDef; bumperDef = bumperDef->next_sibling())
	{
		if (bumperDef->first_attribute("GPIOPin") && bumperDef->first_attribute("Location"))	
		{
			bumperSensor_s bs;
			bs.gpioPin = std::atoi(bumperDef->first_attribute("GPIOPin")->value());
			if (strcmp(bumperDef->first_attribute("Location")->value(), "FRONT") == 0)
			{
				bs.location = eSensorLocation::FRONT;
				foundNode = true;
				bumperSensors.push_back(bs);
			}
			else				
			{
				if (strcmp(bumperDef->first_attribute("Location")->value(), "BACK") == 0)
				{
					bs.location = eSensorLocation::BACK;
					foundNode = true;
					bumperSensors.push_back(bs);
				}			
			}
		}
	}
	//<MotorEncoder leftPin = number rightPin = number / >
	rapidxml::xml_node<> *encoderNode= pwmNode->first_node("MotorEncoder");
	if (!encoderNode)
	{
		robotLib->LogError("EncoderNode node not defined");
		return false;
	}
	if (!encoderNode->first_attribute("leftPin"))
	{
		robotLib->LogError("Encoder node doesnt have left drive motor pin defined");
		return false;
	}
	if (!encoderNode->first_attribute("rightPin"))
	{
		robotLib->LogError("Encoder node doesnt have right drive motor pin defined");
		return false;
	}
	leftEncoderPin = std::atoi(encoderNode->first_attribute("leftPin")->value());
	rightEncoderPin = std::atoi(encoderNode->first_attribute("rightPin")->value());
	
	//<ArduinoHost i2caddress = "addressnum">
	//	<Proximity triggerPin = "num" echoPin = "num" name="NameOfSensor" location="FRONT|BACK|LEFT|RIGHT"/>
	//</ArduinoHost>
	rapidxml::xml_node<> *arduinoNode = sensorsNode->first_node("ArduinoHost");
	if (arduinoNode)
	{
		if (arduinoNode->first_attribute("i2caddress", 0, false))
		{
			arduinoHost.i2caddr = std::atoi(arduinoNode->first_attribute("i2caddress",0,false)->value());			
		}
		if (arduinoNode->first_attribute("ProximityTollerance", 0, false))
		{
			arduinoHost.proximityTollerance = std::atoi(arduinoNode->first_attribute("ProximityTollerance", 0, false)->value());			
		}
		
		for (rapidxml::xml_node<> *prox = arduinoNode->first_node("Proximity",0,false); prox; prox = prox->next_sibling())
		{
			sProximitySensors pSens;
			if (prox->first_attribute("triggerPin", 0, false))
			{
				pSens.triggerPin = std::atoi(prox->first_attribute("triggerPin", 0, false)->value());				
			}
			if (prox->first_attribute("echoPin", 0, false))
			{
				pSens.echoPin = std::atoi(prox->first_attribute("echoPin", 0, false)->value());				
			}
			if (prox->first_attribute("name", 0, false))
			{
				pSens.name = prox->first_attribute("name", 0, false)->value();
			}
			if (prox->first_attribute("location", 0, false)->value())
			{
				std::string location = prox->first_attribute("location", 0, false)->value();
				std::transform(location.begin(), location.end(), location.begin(), ::toupper);
				if (location == "FRONT")
				{
					pSens.location = eSensorLocation::FRONT;
				}
				else
				{
					if (location == "BACK")
						pSens.location = eSensorLocation::BACK;
					else if (location == "LEFT")
						pSens.location = eSensorLocation::LEFT;
					else if (location == "RIGHT")
						pSens.location = eSensorLocation::RIGHT;
					else
						robotLib->LogError("Proximity Sensor has an invalid or missing location");
				}					
			}
			
			if ((pSens.triggerPin > 0 && pSens.triggerPin < 54) && (pSens.echoPin > 0 && pSens.echoPin < 54))
			{
				arduinoHost.proximitySensors.push_back(pSens);
			}
			else
			{
				robotLib->LogWarn("Proximity Sensor: " + pSens.name + " has pins defined where 0<PinNum<54 which is illegial");
			}			
		}	
	}
}

int Configuration::setPctValue(int val)
{
	if (val <= 0)
	{
		std::stringstream ss;
		ss << "Percentage value <=0 (" << val << "), setting to 1";
		robotLib->Log(ss.str());
		return 1;
	}
	if (val > 100)
	{
		std::stringstream ss;
		ss << "Percentage value >100 (" << val << "), setting to 100";
		robotLib->Log(ss.str());
		return 100;
	}
	return val;
}

void Configuration::setDefaultSpeed()
{
	normalOperationSpeed.forwardRPM = 100;
	normalOperationSpeed.reverseRPM = 50;
	normalOperationSpeed.rotationRPM = 10;
	objectDetectionSpeed.forwardRPM = 25;
	objectDetectionSpeed.reverseRPM = 25;
	objectDetectionSpeed.rotationRPM = 10;
}

void Configuration::writeConfiguration()
{
	rapidxml::xml_document<> doc;
	std::ofstream configFile;
	rapidxml::xml_node<> *rootNode = doc.allocate_node(rapidxml::node_element, "PiMowerConfig");
	doc.append_node(rootNode);
	rapidxml::xml_node<> *logNode = doc.allocate_node(rapidxml::node_element, "Logging");
	std::string logLevel;
	switch (minimumLoggingLevel)
	{
		case(min_log_level_t::Debug):
			logLevel="DEBUG";
			break;
		case(min_log_level_t::Warn):
			logLevel = "WARN";
			break;
		case(min_log_level_t::Critical):
			logLevel = "CRITICAL";
			break;
		case(min_log_level_t::Exception):
			logLevel = "EXCEPTION";
			break;
	}
	logNode->append_attribute(doc.allocate_attribute("Level", logLevel.c_str()));
	rootNode->append_node(logNode);
	rapidxml::xml_node<> *speedNode = doc.allocate_node(rapidxml::node_element, "Speed");
	rapidxml::xml_node<> *normSpeedNode = doc.allocate_node(rapidxml::node_element, "NormalOperation");
	normSpeedNode->append_attribute(doc.allocate_attribute("ForwardRPM",std::to_string(normalOperationSpeed.forwardRPM).c_str()));
	normSpeedNode->append_attribute(doc.allocate_attribute("ReverseRPM", std::to_string(normalOperationSpeed.reverseRPM).c_str()));
	normSpeedNode->append_attribute(doc.allocate_attribute("RotationRPM", std::to_string(normalOperationSpeed.rotationRPM).c_str()));
	speedNode->append_node(normSpeedNode);
	rapidxml::xml_node<> *objSpeedNode = doc.allocate_node(rapidxml::node_element, "ObjectDetection");
	normSpeedNode->append_attribute(doc.allocate_attribute("ForwardRPM", std::to_string(objectDetectionSpeed.forwardRPM).c_str()));
	normSpeedNode->append_attribute(doc.allocate_attribute("ReverseRPM", std::to_string(objectDetectionSpeed.reverseRPM).c_str()));
	speedNode->append_node(objSpeedNode);
	rootNode->append_node(speedNode);

	//TODO: Add sensors to writing this, maybe just pass in the original node?
	
	std::string configXML;
	rapidxml::print(std::back_inserter(configXML), doc, 0);
	
	try
	{
		configFile.open(CONFIG_FILE);
		configFile << configXML;
		configFile.close();
	}
	catch (std::exception &e)
	{
		robotLib->LogException(e);
	}	
}