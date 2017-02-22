#include "Config.h"
#include "../3rdParty/wiringPi/wiringPi/wiringPi.h"

Config::Config(RobotLib *robotLib)
{	
	this->robotLib = robotLib;
#ifdef DEBUG
	minimumLoggingLevel = min_log_level_t::Debug;
#else
	minimumLoggingLevel = min_log_level_t::Warn;
#endif
	validConfig = getConfig();
	if (errorLEDPin <= 0)
	{
		validConfig = false;
		robotLib->LogError("An error pin must be set for the \"InError\" LED");
		return;
	}
	pinMode(errorLEDPin, OUTPUT);
}

bool Config::getConfig()
{	
	return getConfig(CONFIG_FILE);
}

bool Config::getConfig(std::string cfgFile)
{
	bool writeConfig = false;
	if (!readConfigDB())	
	{		
		std::ifstream configFile(cfgFile);
		if (!configFile.good())
		{
			robotLib->LogError("Configuration file does not exist.");
			writeConfig = true;
		}
	
		rapidxml::xml_document<> doc;
		std::vector<char> buffer((std::istreambuf_iterator<char>(configFile)), std::istreambuf_iterator<char>());
		buffer.push_back('\0');
		doc.parse<0>(&buffer[0]);
	
		rapidxml::xml_node<> *rootNode = doc.first_node("PiMowerConfig", 0, false);
		if (!rootNode)
		{
			robotLib->LogError("Configuration file does not have a root node of PiMowerConfig");
			return false;
		}
		rootNode = doc.first_node("PiMowerConfig");
	
		if (rootNode->first_attribute("ErrorLEDPin", 0, false))
		{
			errorLEDPin = atoi(rootNode->first_attribute("ErrorLEDPin", 0, false)->value());
		}
		
		if (rootNode->first_attribute("DBLogRetentionHours", 0, false))
		{
			messagesToKeepInDB = atoi(rootNode->first_attribute("DBLogRetentionHours", 0, false)->value());
		}
		
		// Now go thru and parse each of the sub-nodes
		rapidxml::xml_node<> *sensorNode = rootNode->first_node("Sensors", 0, false);
	
		if (!sensorNode)
		{
			robotLib->LogError("Configuration missing Sensor node, which is required");
			return false;
		}
	
		if (!readSensors(sensorNode))
		{
			robotLib->Log("Fatal error in sensor node, exiting");
			return false;
		}	
	
		rapidxml::xml_node<> *speedNode = rootNode->first_node("Speed", 0, false);
		if (!speedNode)
		{
			robotLib->LogWarn("Speed Node missing, will recreate");
			rootNode = createSpeedNode(rootNode, doc);
			writeConfiguration(rootNode, doc, cfgFile);
		}
		if (!readSpeed(speedNode))
		{
			robotLib->LogError("Fatal error in speed node, exiting");
			return false;
		}
	
		rapidxml::xml_node<> *encoder = rootNode->first_node("MotorEncoder", 0, false);
		if (!encoder)
		{
			robotLib->LogError("Fatal error, MotorEncoder node not set in config, exiting");
			return false;
		}
	
		if (!readEncoder(encoder))
		{
			robotLib->Log("Fatal error in MotorEncoder node, exiting");
			return false;
		}
	
		rapidxml::xml_node<> *physical = rootNode->first_node("Physical", 0, false);
		if (!physical)
		{
			robotLib->LogError("Fatal error, Physical node not set in config, exiting");
			return false;
		}
	
		if (!readPhysical(physical))
		{
			robotLib->Log("Fatal error in Physical node, exiting");
			return false;
		}
	
		rapidxml::xml_node<> *logNode = rootNode->first_node("Logging", 0, false);
		if (!logNode)
		{
			minimumLoggingLevel = min_log_level_t::Critical;
			#ifdef DEBUG
			minimumLoggingLevel = Debug;
			#endif		
		}
		else
		{
			readLogLevel(logNode);	
		}
		writeConfigDB();
	}
	return true;
}

bool Config::readPhysical(rapidxml::xml_node<> *physicalNode)
{
	if (physicalNode->first_attribute("DriveWheelDiameter", 0, false))
	{
		driveWheelDiameter = std::atof(physicalNode->first_attribute("DriveWheelDiameter", 0, false)->value());
	}
	else
	{
		robotLib->LogError("Physical node missing required DriveWheelDiameter setting");
		return false;
	}
	if (physicalNode->first_attribute("DriveGearRatio", 0, false))
	{
		driveGearRatio = std::atof(physicalNode->first_attribute("DriveGearRatio", 0, false)->value());
	}
	else
	{
		robotLib->LogError("Physical node missing required DriveGearRatio setting");
		return false;
	}
	if (physicalNode->first_attribute("DriveMotorMaxRPM", 0, false))
	{
		driveMotorMaxRPM = std::atoi(physicalNode->first_attribute("DriveMotorMaxRPM", 0, false)->value());
	}
	else
	{
		robotLib->LogError("Physical node missing required DriveMotorMaxRPM setting");
		return false;
	}		
	if (physicalNode->first_attribute("BatteryChargePercentage", 0, false))
	{
		batteryChargePercentage = std::atof(physicalNode->first_attribute("BatteryChargePercentage", 0, false)->value());
	}
	else
	{
		robotLib->LogError("Physical node missing required BatteryChargePercentage setting");
		return false;
	}
	if (physicalNode->first_attribute("MapScale", 0, false))
	{
		mapScale = std::atoi(physicalNode->first_attribute("MapScale", 0, false)->value());
	}
	
	return true;
}

bool Config::readEncoder(rapidxml::xml_node<> *encoderNode)
{
	leftEncoderPin = -1;
	rightEncoderPin = -1;	
	if (encoderNode->first_attribute("leftPin", 0, false))
	{
		leftEncoderPin = std::atoi(encoderNode->first_attribute("leftPin", 0, false)->value());
	}
	else
	{
		robotLib->LogError("MotorEncoder missing required leftPin setting");
		return false;
	}
	if (encoderNode->first_attribute("rightPin", 0, false))
	{
		rightEncoderPin = std::atoi(encoderNode->first_attribute("rightPin", 0, false)->value());
	}
	else
	{
		robotLib->LogError("MotorEncoder missing required rightPin setting");
		return false;
	}
	if (leftEncoderPin <= 0 || leftEncoderPin >= 52)
	{
		robotLib->LogError("leftPin has an invalid value, must be 0<x<=52");
		return false;
	}
	if (rightEncoderPin <= 0 || rightEncoderPin >= 52)
	{
		robotLib->LogError("rightPin has an invalid value, must be 0<x<=52");
		return false;
	}
	
	if (encoderNode->first_attribute("TicksPerRevolution", 0, false))
	{
		encoderTicksPerRevolution = std::atoi(encoderNode->first_attribute("TicksPerRevolution", 0, false)->value());
	}
	else
	{
		robotLib->LogError("MotorEncoder missing required TicksPerRevolution setting");
		return false;
	}
	
	return true;
}

void Config::readLogLevel(rapidxml::xml_node<> *logNode)
{
	if (logNode->first_attribute("Level", 0, false))
	{
		std::string levStr = logNode->first_attribute("Level", 0, false)->value();
		std::transform(levStr.begin(), levStr.end(), levStr.begin(),::toupper);				
		if (levStr == "DEBUG")
			minimumLoggingLevel = Debug;
		else
		if (levStr == "WARN")
			minimumLoggingLevel = Warn;
		else
		if (levStr == "CRITICAL")
			minimumLoggingLevel = Critical;
		else
		if (levStr == "EXCEPTION")
			minimumLoggingLevel = Exception;
		else
		{
			std::stringstream ss;
			ss << "Unknown logging level set in Logging: " << logNode->first_attribute("Level", 0, false)->value() << ".  Defaulting to WARN";
			robotLib->LogWarn(ss.str());
			minimumLoggingLevel = Warn;			
		}
	}
	else
	{
		minimumLoggingLevel = min_log_level_t::Critical;
#ifdef DEBUG
		minimumLoggingLevel = Debug;
#endif	
		std::stringstream ss;
		ss << "Unknown logging level unset in Logging Defaulting to " << std::to_string(minimumLoggingLevel);
		robotLib->LogWarn(ss.str());				
	}
}

bool Config::readSpeed(rapidxml::xml_node<> *speedNode)
{
	if (speedNode->first_node("NormalOperation", 0, false))
	{
		rapidxml::xml_node<> *norm = speedNode->first_node("NormalOperation", 0, false);
		sSpeedConfig sConfig;
		if (norm->first_attribute("ForwardRPM", 0, false))
		{
			sConfig.forwardRPM = std::atoi(norm->first_attribute("ForwardRPM", 0, false)->value());
		}
		else
		{
			robotLib->LogError("Speed node, NormalOperation missing ForwardRPM");
			return false;
		}
		if (norm->first_attribute("ReverseRPM", 0, false))
		{
			sConfig.reverseRPM = std::atoi(norm->first_attribute("ReverseRPM", 0, false)->value());
		}
		else
		{
			robotLib->LogError("Speed node, NormalOperation missing ReverseRPM");
			return false;
		}
		if (norm->first_attribute("RotationRPM", 0, false))
		{
			sConfig.rotationRPM = std::atoi(norm->first_attribute("RotationRPM", 0, false)->value());
		}
		else
		{
			robotLib->LogError("Speed node, NormalOperation missing RotationRPM");
			return false;
		}
		normalOperationSpeed = sConfig;
	}	
	else
	{
		robotLib->LogError("Speed Node missing required NormalOperation node");
		return false;
	}
	if (speedNode->first_node("ObjectDetection", 0, false))
	{
		rapidxml::xml_node<> *norm = speedNode->first_node("ObjectDetection", 0, false);
		sSpeedConfig sConfig;
		if (norm->first_attribute("ForwardRPM", 0, false))
		{
			sConfig.forwardRPM = std::atoi(norm->first_attribute("ForwardRPM", 0, false)->value());
		}
		else
		{
			robotLib->LogError("Speed node, ObjectDetection missing ForwardRPM");
			return false;
		}
		if (norm->first_attribute("ReverseRPM", 0, false))
		{
			sConfig.reverseRPM = std::atoi(norm->first_attribute("ReverseRPM", 0, false)->value());
		}
		else
		{
			robotLib->LogError("Speed node, ObjectDetection missing ReverseRPM");
			return false;
		}
		if (norm->first_attribute("RotationRPM", 0, false))
		{
			sConfig.rotationRPM = std::atoi(norm->first_attribute("RotationRPM", 0, false)->value());
		}
		else
		{
			robotLib->LogWarn("Speed node, ObjectDetection missing RotationRPM, setting to default: 15");
			sConfig.rotationRPM = 15;
		}
		objectDetectionSpeed = sConfig;
	}
	else
	{
		robotLib->LogError("Speed Node missing required NormalOperation node");
		return false;
	}
	
	// Now Acceleration
	if (speedNode->first_node("Acceleration", 0, false))
	{
		rapidxml::xml_node<> *acc = speedNode->first_node("Acceleration", 0, false);
		if (acc->first_attribute("Normal", 0, false))
		{
			normalAcceleration = std::atoi(acc->first_attribute("Normal", 0, false)->value());		
		}
		else
		{
			robotLib->LogWarn("Acceleration node missing Normal attribute, setting to default: 2");
			normalAcceleration = 2;
		}
		if (acc->first_attribute("Rotational", 0, false))
		{
			rotationalAcceleration = std::atoi(acc->first_attribute("Rotational", 0, false)->value());		
		}
		else
		{
			robotLib->LogWarn("Acceleration node missing Rotational attribute, setting to default: 1");
			rotationalAcceleration = 1;
		}
	}
	else
	{
		robotLib->LogWarn("Speed node missing Accleration node, setting defaults.  Normal(2), Rotational(1)");
		rotationalAcceleration = 1;
		normalAcceleration = 2;
	}
	return true;
}

void Config::writeConfiguration(rapidxml::xml_node<> *rootNode, 
	rapidxml::xml_document<> &doc,
	std::string cfgFile)
{
	std::string xmlString;
	
	rapidxml::print(std::back_inserter(xmlString), doc);
	std::ofstream fs(cfgFile);
	if (!fs)
	{
		robotLib->LogError("Could not rewrite configuration, changes lost!");
		return;
	}
	fs << xmlString;
	fs.close();	
}

bool Config::readConfigDB()
{
	// First get sensors
		
	SQLite::Statement query(*Database::getInstance().getDBHandle(), "SELECT * FROM sensors");
	bumperSensors.clear();
	std::vector<sProximitySensors> pSensors;
	while (query.executeStep())
	{
		int sensorType = query.getColumn(0).getInt();
		if (sensorType == 0)
		{
			// Bumper
			sBumperSensor bSensor;
			bSensor.gpioPin = query.getColumn(1).getInt();
			std::string loc = query.getColumn(3).getString();
			std::transform(loc.begin(), loc.end(), loc.begin(), ::toupper);
			if (loc == "FRONT")
			{
				bSensor.location = eSensorLocation::FRONT;
			}
			if (loc == "BACK")
			{
				bSensor.location = eSensorLocation::BACK;
			}
			if (loc == "LEFT")
			{
				bSensor.location = eSensorLocation::LEFT;
			}
			if (loc == "RIGHT")
			{
				bSensor.location = eSensorLocation::RIGHT;
			}
			bumperSensors.push_back(bSensor);
		}
		else
		if (sensorType == 1)
		{
			//Proximity
			sProximitySensors pSensor; 
			pSensor.triggerPin = query.getColumn(1).getInt();
			pSensor.echoPin = query.getColumn(2).getInt();
			std::string loc = query.getColumn(3).getString();
			std::transform(loc.begin(), loc.end(), loc.begin(),::toupper);
			if (loc == "FRONT")
			{
				pSensor.location = eSensorLocation::FRONT;
			}
			if (loc == "BACK")
			{
				pSensor.location = eSensorLocation::BACK;
			}
			if (loc == "LEFT")
			{
				pSensor.location = eSensorLocation::LEFT;
			}
			if (loc == "RIGHT")
			{
				pSensor.location = eSensorLocation::RIGHT;
			}
			pSensor.name = query.getColumn(4).getString();
			pSensors.push_back(pSensor);
		}
	}
	SQLite::Statement cQuery(*Database::getInstance().getDBHandle(), "SELECT * FROM config");
	bool readConfig = false;
	while (cQuery.executeStep())
	{
		readConfig = true;
		int ll = cQuery.getColumn(0).getInt();
		if (ll == 0)			
			minimumLoggingLevel = min_log_level_t::Debug;
		else
		if (ll == 1)
			minimumLoggingLevel = min_log_level_t::Warn;
		else
		if (ll == 2)
			minimumLoggingLevel = min_log_level_t::Critical;
		else
		if (ll == 3)
			minimumLoggingLevel = min_log_level_t::Exception;
		else
		{
			std::stringstream ss;
			ss << "Unknown logging level: " << ll << ", defaulting to Critical";
			robotLib->Log(ss.str());
			minimumLoggingLevel = min_log_level_t::Critical;
		}
		driveWheelDiameter = cQuery.getColumn(1).getDouble();
		driveGearRatio = cQuery.getColumn(2).getDouble();
		driveMotorMaxRPM = cQuery.getColumn(3).getInt();
		sPWMController pwmController;
		pwmController.i2cChannel = cQuery.getColumn(4).getInt();
		pwmController.leftDriveChannel = cQuery.getColumn(5).getInt();
		pwmController.rightDriveChannel = cQuery.getColumn(6).getInt();
		pwmController.bladeChannel = cQuery.getColumn(7).getInt();
		this->pwmController = pwmController;
		sArduinoHost aHost;
		aHost.i2caddr = cQuery.getColumn(8).getInt();
		aHost.proximitySensors = pSensors;
		aHost.proximityTollerance = cQuery.getColumn(9).getDouble();
		sSpeedConfig sConfig;
		sConfig.forwardRPM = cQuery.getColumn(10).getInt();
		sConfig.reverseRPM = cQuery.getColumn(11).getInt();
		sConfig.rotationRPM = cQuery.getColumn(12).getInt();
		normalOperationSpeed = sConfig;
		sConfig.forwardRPM = cQuery.getColumn(13).getInt();
		sConfig.reverseRPM = cQuery.getColumn(14).getInt();
		objectDetectionSpeed = sConfig;
		normalAcceleration = cQuery.getColumn(15).getInt();
		rotationalAcceleration = cQuery.getColumn(16).getInt();
		leftEncoderPin = cQuery.getColumn(17).getInt();
		rightEncoderPin = cQuery.getColumn(18).getInt();		
		batteryChargePercentage = cQuery.getColumn(19).getInt();		
		mapScale = cQuery.getColumn(20).getInt();		
		encoderTicksPerRevolution = cQuery.getColumn(21).getInt();
		errorLEDPin = cQuery.getColumn(22).getInt();
	}	
	return readConfig;
}

void Config::writeConfigDB()
{
	// First clear tables
	Database::getInstance().execSql("DELETE FROM sensors");
	Database::getInstance().execSql("DELETE FROM config");
	
	// Add the sensors
	for (int a = 0; a < bumperSensors.size(); a++)
	{
		std::stringstream ss;
		ss << "INSERT INTO sensors VALUES(0," << bumperSensors[a].gpioPin << ",0,\"" << bumperSensors[a].location << "\",\"\")";
		if (!Database::getInstance().execSql(ss.str()))
			robotLib->LogError("Error inserting bumperSensor into database");		
	}
	for (int a = 0; a < arduinoHost.proximitySensors.size(); a++)
	{
		std::stringstream ss;
		ss << "INSERT INTO sensors VALUES(1," << arduinoHost.proximitySensors[a].triggerPin << "," << arduinoHost.proximitySensors[a].echoPin << ", \"" << arduinoHost.proximitySensors[a].location << "\",\"" << arduinoHost.proximitySensors[a].name<<"\")";
		if (!Database::getInstance().execSql(ss.str()))
			robotLib->LogError("Error inserting bumperSensor into database");			
	}
	
	std::stringstream ss;
	int intLogLevel;
	switch (minimumLoggingLevel)
	{
	case Debug:
		intLogLevel = 0;
		break;
	case Warn:
		intLogLevel = 1;
		break;
	case Critical:
		intLogLevel = 2;
		break;
	case Exception:
		intLogLevel = 3;
		break;
	}	
	SQLite::Statement s(*Database::getInstance().getDBHandle(), "INSERT INTO Config VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
	s.bind(1, intLogLevel);
	s.bind(2, driveWheelDiameter);
	s.bind(3, driveGearRatio);
	s.bind(4, driveMotorMaxRPM);
	s.bind(5, pwmController.i2cChannel);
	s.bind(6, pwmController.leftDriveChannel);
	s.bind(7, pwmController.rightDriveChannel);
	s.bind(8, pwmController.bladeChannel);
	s.bind(9, arduinoHost.i2caddr);
	s.bind(10, arduinoHost.proximityTollerance);
	s.bind(11, normalOperationSpeed.forwardRPM);
	s.bind(12, normalOperationSpeed.reverseRPM);
	s.bind(13, normalOperationSpeed.rotationRPM);
	s.bind(14, objectDetectionSpeed.forwardRPM);
	s.bind(15, objectDetectionSpeed.reverseRPM);
	s.bind(16, normalAcceleration);
	s.bind(17, rotationalAcceleration);
	s.bind(18, leftEncoderPin);
	s.bind(19,rightEncoderPin);
	s.bind(20, batteryChargePercentage);
	s.bind(21, mapScale);
	s.bind(22, encoderTicksPerRevolution);
	s.bind(23, errorLEDPin);
	s.exec();
}

rapidxml::xml_node<> *Config::createSpeedNode(rapidxml::xml_node<> *rootNode, rapidxml::xml_document<> &doc)
{
	rapidxml::xml_node<> *speedNode = doc.allocate_node(rapidxml::node_element, "Speed");
	rapidxml::xml_node<> *normalNode = doc.allocate_node(rapidxml::node_element, "NormalOperation");
	normalNode->append_attribute(doc.allocate_attribute("ForwardRPM", "100"));
	normalNode->append_attribute(doc.allocate_attribute("ReverseRPM", "50"));
	normalNode->append_attribute(doc.allocate_attribute("RotationRPM", "25"));
	speedNode->append_node(normalNode);
	rapidxml::xml_node<> *obj = doc.allocate_node(rapidxml::node_element, "ObjectDetection");
	obj->append_attribute(doc.allocate_attribute("ForwardRPM", "50"));
	obj->append_attribute(doc.allocate_attribute("ReverseRPM", "25"));
	obj->append_attribute(doc.allocate_attribute("RotationRPM", "25"));
	speedNode->append_node(obj);
	rapidxml::xml_node<> *acc = doc.allocate_node(rapidxml::node_element, "Acceleration");
	acc->append_attribute(doc.allocate_attribute("Normal", "2"));
	acc->append_attribute(doc.allocate_attribute("Rotational", "1"));
	speedNode->append_node(acc);
	rootNode->append_node(speedNode);
	return rootNode;
}

bool Config::readPWMController(rapidxml::xml_node<> *pwmNode)
{	
	if (pwmNode->first_attribute("i2caddr", 0, false))
	{
		pwmController.i2cChannel = std::atoi(pwmNode->first_attribute("i2caddr", 0, false)->value());		
		std::stringstream ss;
		ss << "PWM Controller I2C Address==" << (int)pwmController.i2cChannel;
		robotLib->Log(ss.str());
	}
	else
	{
		robotLib->LogError("PWMController node missing attribute i2caddr, and is required");
		return false;
	}
	rapidxml::xml_node<> *channels = pwmNode->first_node("ControlChannels", 0, false);
	if (channels)
	{
		robotLib->Log("Readding ControlChannels node");
		if (channels->first_attribute("leftDriveChannel", 0, false))
		{
			pwmController.leftDriveChannel = std::atoi(channels->first_attribute("leftDriveChannel", 0, false)->value());			
			std::stringstream ss;
			ss << "Left Drive Channel==" << (int)pwmController.leftDriveChannel;
			robotLib->Log(ss.str());
		}
		else
		{
			robotLib->LogError("Channels under PWMController missing leftDriveChannel");
			return false;
		}
		if (channels->first_attribute("rightDriveChannel", 0, false))
		{
			pwmController.rightDriveChannel = std::atoi(channels->first_attribute("rightDriveChannel", 0, false)->value());			
			std::stringstream ss;
			ss << "Right Drive Channel==" << (int)pwmController.rightDriveChannel;
			robotLib->Log(ss.str());
		}
		else
		{
			robotLib->LogError("Channels under PWMController missing rightDriveChannel");
			return false;
		}
		if (channels->first_attribute("bladeChannel", 0, false))
		{
			pwmController.bladeChannel = std::atoi(channels->first_attribute("bladeChannel", 0, false)->value());			
			std::stringstream ss;
			ss << "Blade Channel==" << (int)pwmController.bladeChannel;
			robotLib->Log(ss.str());
		}
		else
		{
			robotLib->LogError("Channels under PWMController missing bladeChannel");
			return false;
		}		
	}
	return true;
}

bool Config::readBumperSensor(rapidxml::xml_node<> *bumper)
{
	sBumperSensor bs;
	bs.gpioPin = 0;

	rapidxml::xml_attribute<> *attr = bumper->first_attribute("GPIOPin", 0, false);
	if (!attr)
	{
		robotLib->LogError("Bumper Sensor does not have required attribute GPIOPin");
		return false;
	}
	std::string attribute = attr->name();
	std::transform(attribute.begin(), attribute.end(), attribute.begin(),::toupper);				
	robotLib->Log("Attribute: " + attribute);
	if (attribute == "GPIOPIN")
	{		
		int val = std::atoi(attr->value());
		bs.gpioPin = val;			
	}
	attr = bumper->first_attribute("Location", 0, false);
	attribute = attr->name();
	std::transform(attribute.begin(), attribute.end(), attribute.begin(), ::toupper);				
	robotLib->Log("Attribute: " + attribute);
	
	if (attribute == "LOCATION")
	{
		std::string locStr = attr->value();
		std::transform(locStr.begin(), locStr.end(), locStr.begin(),::toupper);				
		if (locStr == "FRONT")
			bs.location = eSensorLocation::FRONT;
		else
			if (locStr == "BACK")
			bs.location = eSensorLocation::BACK;
		else
			if (locStr == "LEFT")
			bs.location = eSensorLocation::LEFT;
		else
			if (locStr == "RIGHT")
			bs.location = eSensorLocation::RIGHT;
		else
		{
			std::stringstream ss;
			ss << "Unknown location for Bumper Location: " << locStr;
			robotLib->LogWarn(ss.str());			
		}
		robotLib->Log("Bumper Location: " + std::to_string(bs.location));
	}
	if (bs.gpioPin == 0)
	{
		robotLib->Log("Bumper Sensor requires a GPIO Pin definition");
		return false;
	}
	std::stringstream ss;
	ss << "Adding Bumper Sensor: GPIOPin(" << bs.gpioPin << ") Location(" << bs.location << ")";
	robotLib->Log(ss.str());
	bool exists = false;
	for (int a = 0; a < bumperSensors.size(); a++)
	{
		if (bumperSensors[a].gpioPin == bs.gpioPin)
			exists = true;
	}
	if(!exists)
		this->bumperSensors.push_back(bs);
	return true;
}

bool Config::readArduinoHost(rapidxml::xml_node<> *arduinoHost)
{
	// First get attributes
	sArduinoHost aHost;
	if (!arduinoHost->first_attribute("i2caddress", 0, false))
	{
		robotLib->LogError("ArduinoHost node does not contain required attribute: i2caddress");
		return false;
	}
	aHost.i2caddr = std::atoi(arduinoHost->first_attribute("i2caddress", 0, false)->value());
	if (aHost.i2caddr <= 0 || aHost.i2caddr > 127)
	{
		robotLib->LogError("ArduinoHost/I2CAddress out of range");
		return false;		
	}
	if (arduinoHost->first_attribute("proximitytollerance", 0, false))
	{		
		aHost.proximityTollerance = std::atof(arduinoHost->first_attribute("proximitytollerance", 0, false)->value());
	}
	for (rapidxml::xml_node<> *pSensor = arduinoHost->first_node("Proximity", 0, false); pSensor; pSensor= pSensor->next_sibling())
	{
		sProximitySensors prox;
		if (pSensor->first_attribute("triggerPin", 0, false))
		{
			prox.triggerPin = atoi(pSensor->first_attribute("triggerPin", 0, false)->value());
		}
		if (pSensor->first_attribute("echoPin", 0, false))
		{
			prox.echoPin = atoi(pSensor->first_attribute("echoPin", 0, false)->value());
		}
		if (pSensor->first_attribute("name", 0, false))
		{
			prox.name = pSensor->first_attribute("name", 0, false)->value();
		}
		if (pSensor->first_attribute("location", 0, false))
		{
			std::string locStr = pSensor->first_attribute("location",0,false)->value();
			std::transform(locStr.begin(), locStr.end(), locStr.begin(), ::toupper);				
			if (locStr == "FRONT")
				prox.location = eSensorLocation::FRONT;
			else
				if (locStr == "BACK")
				prox.location = eSensorLocation::BACK;
			else
				if (locStr == "LEFT")
				prox.location = eSensorLocation::LEFT;
			else
				if (locStr == "RIGHT")
				prox.location = eSensorLocation::RIGHT;
			else
				robotLib->LogWarn("Proximity Sensor has unrecognized location");
		}
		if (prox.triggerPin > 0 && prox.triggerPin <= 56 && prox.echoPin > 0 && prox.echoPin <= 56)
		{
			aHost.proximitySensors.push_back(prox);
			std::stringstream ss;
			ss << "Proximity Sensor added.  Trigger[" << prox.triggerPin << "], Echo[" << prox.echoPin << "], Name: " << prox.name << ", Location[" << prox.location << "]";
			robotLib->Log(ss.str());
		}
	}	
	return true;
}

bool Config::readSensors(rapidxml::xml_node<> *sensorNode)
{
	rapidxml::xml_node<> *pwmController = sensorNode->first_node("PWMController", 0, false);
	if (!pwmController)
	{
		robotLib->LogError("PWMController node missing, and is required");
		return false;
	}
	robotLib->Log("Reading PWMNode");
	if (!readPWMController(pwmController))
	{
		robotLib->Log("Exiting readSensors, FALSE");
		return false;
	}
	
	for (rapidxml::xml_node<> *bumperSensors = sensorNode->first_node("BumperSensor", 0, false); bumperSensors; bumperSensors = bumperSensors->next_sibling())
	{
		if (strcmp(bumperSensors->name(),"BumperSensor")==0)
		{			
			if (!readBumperSensor(bumperSensors))
			{
				robotLib->Log("Exiting readSensors, FALSE");
				return false;
			}
		}
	}
	robotLib->Log("Reading ArduinoHost");
	rapidxml::xml_node<> *arduinoHost = sensorNode->first_node("ArduinoHost", 0, false);
	if (!arduinoHost)
	{
		robotLib->LogError("ArduinoHost not found, and is required");
		return false;
	}
	
	if (!readArduinoHost(arduinoHost))
	{
		robotLib->Log("Error reading ArduinoHost Node.  Exiting readSensors, FALSE");
		return false;
	}		
	
	robotLib->Log("Exiting readSensors, TRUE");
	return true;
}