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
	Database &db = Database::getInstance();
	validConfig = loadConfig();
	if (errorLEDPin <= 0)
	{
		validConfig = false;
		robotLib->LogError("An error pin must be set for the \"InError\" LED");
		return;
	}
	pinMode(errorLEDPin, OUTPUT);
}

bool Config::loadConfig()
{
	if (!readConfigDB())
	{
		return getConfig(CONFIG_FILE);		
	}
	return true;
}

bool Config::getConfig()
{	
	return getConfig(CONFIG_FILE);
}

bool Config::getConfig(std::string cfgFile)
{
	bool writeConfig = false;
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
	}
	if (!readPhysical(physical))
	{
		robotLib->Log("Fatal error in Physical node, exiting");			
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
	Poco::Data::Session session("SQLite", DB_LOCATION);	
	Poco::Data::Statement stmt(session);
	int sensorType,gpioPin,echoPin;
	std::string loc,name;	
	stmt << "SELECT * FROM sensors",
		Poco::Data::Keywords::range(0, 1),
		Poco::Data::Keywords::into(sensorType),
		Poco::Data::Keywords::into(gpioPin),
		Poco::Data::Keywords::into(echoPin),
		Poco::Data::Keywords::into(loc),
		Poco::Data::Keywords::into(name);
	bumperSensors.clear();
	std::vector<sProximitySensors> pSensors;
	while (!stmt.done())
	{
		stmt.execute();
		if (sensorType == 0)
		{
			// Bumper
			sBumperSensor bSensor;
			bSensor.gpioPin = gpioPin;
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
			pSensor.triggerPin = gpioPin;
			pSensor.echoPin = echoPin;
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
			pSensor.name = name;
			pSensors.push_back(pSensor);
		}
	}
	Poco::Data::Statement cQuery(session);
	int ll;
	sPWMController pwmController;
	sArduinoHost aHost;
	sSpeedConfig nsConfig, osConfig;
	cQuery << "SELECT * FROM config",
		Poco::Data::Keywords::into(ll),
		Poco::Data::Keywords::into(driveWheelDiameter),
		Poco::Data::Keywords::into(driveGearRatio),
		Poco::Data::Keywords::into(driveMotorMaxRPM),
		Poco::Data::Keywords::into(pwmController.i2cChannel),
		Poco::Data::Keywords::into(pwmController.leftDriveChannel),
		Poco::Data::Keywords::into(pwmController.rightDriveChannel),
		Poco::Data::Keywords::into(pwmController.bladeChannel),
		Poco::Data::Keywords::into(aHost.i2caddr),		
		Poco::Data::Keywords::into(aHost.proximityTollerance),
		Poco::Data::Keywords::into(nsConfig.forwardRPM),
		Poco::Data::Keywords::into(nsConfig.reverseRPM),
		Poco::Data::Keywords::into(nsConfig.rotationRPM),
		Poco::Data::Keywords::into(osConfig.forwardRPM),
		Poco::Data::Keywords::into(osConfig.reverseRPM),
		Poco::Data::Keywords::into(normalAcceleration);
		Poco::Data::Keywords::into(rotationalAcceleration);
		Poco::Data::Keywords::into(leftEncoderPin);
		Poco::Data::Keywords::into(rightEncoderPin);		
		Poco::Data::Keywords::into(batteryChargePercentage);		
		Poco::Data::Keywords::into(mapScale);		
		Poco::Data::Keywords::into(encoderTicksPerRevolution);
		Poco::Data::Keywords::into(errorLEDPin),
		Poco::Data::Keywords::range(0, 1);
		
	bool readConfig = false;
	while (!cQuery.done())
	{		
		if (cQuery.execute() > 0)
		{			
			readConfig = true;
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
			this->pwmController = pwmController;
			this->arduinoHost = aHost;
			this->normalOperationSpeed = nsConfig;
			this->objectDetectionSpeed = osConfig;
		}
	}	
	return readConfig;
}

void Config::writeConfigDB()
{	
	Poco::Data::Session session("SQLite", DB_LOCATION);		
	// First clear tables
	session << "DELETE FROM sensors", Poco::Data::Keywords::now;	
	
	session << "DELETE FROM config", Poco::Data::Keywords::now;
	std::clog << "Writing Sensors";
	// Add the sensors
	for (int a = 0; a < bumperSensors.size(); a++)
	{
		Poco::Data::Statement stmt(session);
		int triggerPin = bumperSensors[a].gpioPin;
		int location = bumperSensors[a].location;
		
		stmt << "INSERT INTO sensors VALUES(0,?,0,?,?)",
			Poco::Data::Keywords::bind(triggerPin),
			Poco::Data::Keywords::bind(location),
			Poco::Data::Keywords::bind("");
		if (stmt.execute()!=1)
			robotLib->LogError("Error inserting bumperSensor into database");		
	}
	for (int a = 0; a < arduinoHost.proximitySensors.size(); a++)
	{
		Poco::Data::Statement stmt(session);
		int triggerPin = arduinoHost.proximitySensors[a].triggerPin;
		int echoPin = arduinoHost.proximitySensors[a].echoPin;
		int location = arduinoHost.proximitySensors[a].location;
		std::string name = arduinoHost.proximitySensors[a].name;
		stmt << "INSERT INTO sensors VALUES(1,?,?,?,?)",
			Poco::Data::Keywords::bind(triggerPin),
			Poco::Data::Keywords::bind(echoPin),
			Poco::Data::Keywords::bind(location),
			Poco::Data::Keywords::bind(name);
		if (stmt.execute() != 1)
			robotLib->LogError("Error inserting proximity sensor into database");				
	}
	std::clog << "Writing Config";
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
	Poco::Data::Statement stmt(session);
	stmt << "INSERT INTO Config VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)",
		Poco::Data::Keywords::bind(intLogLevel),
	Poco::Data::Keywords::bind(driveWheelDiameter),
	Poco::Data::Keywords::bind(driveGearRatio),
	Poco::Data::Keywords::bind(driveMotorMaxRPM),
	Poco::Data::Keywords::bind(pwmController.i2cChannel),
	Poco::Data::Keywords::bind(pwmController.leftDriveChannel),
	Poco::Data::Keywords::bind(pwmController.rightDriveChannel),
	Poco::Data::Keywords::bind(pwmController.bladeChannel),
	Poco::Data::Keywords::bind(arduinoHost.i2caddr),
	Poco::Data::Keywords::bind(arduinoHost.proximityTollerance),
	Poco::Data::Keywords::bind(normalOperationSpeed.forwardRPM),
	Poco::Data::Keywords::bind(normalOperationSpeed.reverseRPM),
	Poco::Data::Keywords::bind(normalOperationSpeed.rotationRPM),
	Poco::Data::Keywords::bind(objectDetectionSpeed.forwardRPM),
	Poco::Data::Keywords::bind(objectDetectionSpeed.reverseRPM),
	Poco::Data::Keywords::bind(normalAcceleration),
	Poco::Data::Keywords::bind(rotationalAcceleration),
	Poco::Data::Keywords::bind(leftEncoderPin),
	Poco::Data::Keywords::bind(rightEncoderPin),
	Poco::Data::Keywords::bind(batteryChargePercentage),
	Poco::Data::Keywords::bind(mapScale),
	Poco::Data::Keywords::bind(encoderTicksPerRevolution),
	Poco::Data::Keywords::bind(errorLEDPin);
	stmt.execute();
	std::clog << "Done DB";
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