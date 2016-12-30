#include "AdafruitGPS.h"

int AdafruitGPS::serialFD;
bool AdafruitGPS::successfulParse;

// we double buffer: read one line in and leave one for the main program
volatile char line1[MAXLINELENGTH];
volatile char line2[MAXLINELENGTH];

// our index into filling the current line
volatile uint8_t lineidx = 0;
// pointers to the double buffers
volatile char *currentline;
volatile char *lastline;
volatile bool recvdflag;
volatile bool inStandbyMode;

AdafruitGPS::AdafruitGPS(RobotLib *rl) :
	SensorBase(rl)
{
	nmeaParser = new NMEAParser(robotLib);

	if (rl->getEmulator())
	{
		return;
	}
	
	initialize(9600,gps_conn_t::rpi3UART);
}

AdafruitGPS::AdafruitGPS(RobotLib *rl, uint32_t baudRate) :
	SensorBase(rl)
{
	nmeaParser = new NMEAParser(robotLib);
	if (rl->getEmulator())
	{
		return;
	}
	
	initialize(baudRate, gps_conn_t::rpi3UART);	
}

AdafruitGPS::AdafruitGPS(RobotLib *rl, uint32_t baudRate, gps_conn_t conType) :
	SensorBase(rl)
{
	nmeaParser = new NMEAParser(robotLib);
	if (rl->getEmulator())
	{
		return;
	}
	initialize(baudRate,conType);
}

void AdafruitGPS::initialize(uint32_t baudRate, gps_conn_t conType)
{	
	successfulParse = false;
	baud = baudRate;
	connectionType = conType;
	
	paused = false;
	currentline = line1;
	lastline = line2;
	receivedFlag = false;
	paused = false;
	serialFD = initSerial();
			
	// Turn on RMC (Recommended minimum) and GGA (fix data) including altitude
	setRMCGGA();
	sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate	
}

std::string AdafruitGPS::getDeviceDescription()
{
	return "Adafruit Ultimate GPS Breakout Board V3";
}

void AdafruitGPS::setRMCOnly()
{
	sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);	
	enabledStreams.clear();	
	enabledStreams.push_back(nmea_msg_t::NMEA_GPRMC);
}

void AdafruitGPS::setAllData()
{
	sendCommand(PMTK_SET_NMEA_OUTPUT_ALLDATA);
	enabledStreams.push_back(nmea_msg_t::NMEA_GPGGA);
	enabledStreams.push_back(nmea_msg_t::NMEA_GPRMC);
	//TODO: Add any other streams we get
}

void AdafruitGPS::setRMCGGA()
{
	sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	enabledStreams.clear();
	enabledStreams.push_back(nmea_msg_t::NMEA_GPGGA);
	enabledStreams.push_back(nmea_msg_t::NMEA_GPRMC);
}

bool AdafruitGPS::inStandby()
{
	return inStandbyMode;
}

// Gets the next full message
void AdafruitGPS::read(void)
{
	char c = 0;
	if (paused)
	{
		return;
	}
	int counter = 0;
	int sda = serialDataAvail(serialFD);
	while (sda==0 && counter < 10)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		sda = serialDataAvail(serialFD);
		counter++;
	}
	if (sda == -1)
	{
		robotLib->LogError("Error checking serialDataAvailable: errno==" + errno);
	}
	
	while (c != '$')
	{
		c = serialGetchar(serialFD);		
	}
	int a = 0;
	while (a<MAXLINELENGTH && c != '\n')
	{		
		lastline[a] = c;
		c = serialGetchar(serialFD);
		a++;
	}
	lastline[a] = c;
	
	return;
}

int AdafruitGPS::initSerial(){
		std::string dev;
		switch (connectionType)
		{		
		case(gps_conn_t::usbUART):
			//TODO: Set this correctly
			dev = "/dev/ttyAMA0";			
			break;
		case(gps_conn_t::rpi3UART)			:
			dev = "/dev/ttyS0";
			break;
		default:
			dev = "/dev/ttyAMA0";
			break;
		}
		int serialFD = DeviceManager::getSerialFD(dev, baud);				
		if (serialFD == -1)
		{
			robotLib->LogError("Could not open serial device: " + dev);
		}
		else
		{
			robotLib->Log("Opened serial device: " + dev);
		}
	return serialFD;
}

void AdafruitGPS::pause(bool p)
{
	paused = p;
}

char *AdafruitGPS::lastNMEA(void) 
{
	recvdflag = false;
	return const_cast<char *>(lastline);
}

uint8_t AdafruitGPS::parseHex(char c)
{
	if (c < '0')
		return 0;
	if (c <= '9')
		return c - '0';
	if (c < 'A')
		return 0;
	if (c <= 'F')
		return (c - 'A') + 10;
	return 0;
}

void AdafruitGPS::sendCommand(const char *str)
{	
	std::string cmd(str);
	cmd += "\n";
	serialPrintf(serialFD, cmd.c_str());	
}

bool AdafruitGPS::newNMEAreceived(void)
{
	return receivedFlag;
}

void AdafruitGPS::standby()
{
	if (inStandbyMode)
	{
		return;		
	}
	
	inStandbyMode = true;
	sendCommand(PMTK_STANDBY);
	robotLib->Log("GPS put in standby mode");	
}

bool AdafruitGPS::waitForSentence(const char *wait4me, uint8_t max)
{
	char str[20];
	uint8_t i = 0;
	while (i < max)
	{
		if (newNMEAreceived())
		{
			char *nmea = lastNMEA();
			strncpy(str, nmea, 20);
			str[19] = 0;
			i++;
			if (strstr(str, wait4me))
			{
				return true;
			}
		}
	}
	return false;
}

bool AdafruitGPS::wakeup()
{
	if (inStandbyMode)
	{
		inStandbyMode = false;
		sendCommand("");		// Send a byte to wake up GPS
		return waitForSentence(PMTK_AWAKE);
	}
	
	return false;			// Not in standby mode, nothing to wakeup	
}

sensors_gps_t *AdafruitGPS::parse(char *nmea)
{
	if (!nmeaParser->ValidSentence(nmea))
	{
		std::stringstream ss;
		ss << "Invalid NMEA Sentence: " << nmea;
		robotLib->LogWarn(ss.str());
		return NULL;
	}
	
	// We have gotten a valid NMEA sentence so set successfulParse=true
	successfulParse = true;

	return nmeaParser->Parse(nmea);	
}

std::string AdafruitGPS::getSensorName()
{
	return "Adafruit GPS";
}

bool AdafruitGPS::getEvent(sensors_event_t *event)
{
	memset(event, 0, sizeof(sensors_event_t));
	
	std::vector<sensors_gps_t *> eventList;
	bool eventComplete = false;
	sensors_gps_t *e;
	int eventCount=0;
	event->version = sizeof(sensors_event_t);
	event->sensor_id = GPS_SENSOR_ID;
	event->type = SENSOR_TYPE_GPS;
	event->timestamp = getTimestamp();
		
	// Dont go further than 15 events to find what we need
	while (!eventComplete && eventCount<15)
	{
		read();
	
#if DEBUG
		robotLib->Log(lastNMEA());
#else
		robotLib->Log("Received NMEA sentance");
#endif
		
		e = parse(lastNMEA());
		
		try
		{
			if (e != NULL)
			{
				bool streamEnabled = false;
				for (int i = 0; i < enabledStreams.size(); i++)
				{				
					if (enabledStreams[i] == e->messageType[0])
					{
						streamEnabled = true;					
					}
				}
				bool haveEvent = false;
				
		// Now, if this stream is enabled
				if (streamEnabled)
				{				
					for (int i = 0; i < eventList.size(); i++)
					{
						if (eventList[i]->messageType[0] == e->messageType[0])
							haveEvent = true;
					}
				}
				// If we dont have the event and the stream is enabled
				if (streamEnabled && !haveEvent)
				{
					eventList.emplace_back(e);
					if (eventList.size() == enabledStreams.size())
						eventComplete = true;
				}
			}
		}
		catch (std::exception &e)
		{
		}
		eventCount++;
	}
			
	// Ok, we have our event list lets merge them
	if (eventList.size() == 0)
		return false;
	e = mergeGPSEvents(eventList,e);
	
	// Now add it to our sensor event
	event->gps.altitude = e->altitude;
	event->gps.course = e->course;
	event->gps.dataQuality = e->dataQuality;
	event->gps.fix = e->fix;
	event->gps.fixquality = e->fixquality;
	event->gps.geoIDHeight = e->geoIDHeight;
	event->gps.HDOP = e->HDOP;
	event->gps.latitude = e->latitude;
	event->gps.longitude = e->longitude;
	event->gps.magvariation = e->magvariation;
	event->gps.messageType = e->messageType;
	event->gps.satellites = e->satellites;
	event->gps.speedKTS = e->speedKTS;
	event->gps.speedKPH = e->speedKPH;
	event->gps.time.tm_gmtoff = e->time.tm_gmtoff;
	event->gps.time.tm_hour = e->time.tm_hour;
	event->gps.time.tm_isdst = e->time.tm_isdst;
	event->gps.time.tm_mday = e->time.tm_mday;
	event->gps.time.tm_min = e->time.tm_min;
	event->gps.time.tm_mon = e->time.tm_mon;
	event->gps.time.tm_sec = e->time.tm_sec;
	event->gps.time.tm_wday = e->time.tm_wday;
	event->gps.time.tm_yday = e->time.tm_yday;
	event->gps.time.tm_year = e->time.tm_year;
	event->gps.time.tm_zone = e->time.tm_zone;
			
	return true;
}

//TODO: Maybe average height and location info?
sensors_gps_t *AdafruitGPS::mergeGPSEvents(std::vector<sensors_gps_t *> eventList, sensors_gps_t *e)
{
	if (eventList.size() == 0)
	{
		robotLib->LogWarn("No events in the event list, this will be an empty event");
		return NULL;
	}
	
	e = eventList[0];
	for (int i = 1; i < eventList.size(); i++)
	{
		if (eventList[i]->messageType[0] == nmea_msg_t::NMEA_GPGGA)
		{
			e->messageType.emplace_back(nmea_msg_t::NMEA_GPGGA);
			
			// Copy GPGGA specific messages 
			// Time
			e->time.tm_gmtoff = eventList[i]->time.tm_gmtoff;
			e->time.tm_hour = eventList[i]->time.tm_hour;
			e->time.tm_isdst = eventList[i]->time.tm_isdst;
			e->time.tm_mday = eventList[i]->time.tm_mday;
			e->time.tm_min = eventList[i]->time.tm_min;
			e->time.tm_mon = eventList[i]->time.tm_mon;
			e->time.tm_sec = eventList[i]->time.tm_sec;
			e->time.tm_wday = eventList[i]->time.tm_wday;
			e->time.tm_yday = eventList[i]->time.tm_yday;
			e->time.tm_year = eventList[i]->time.tm_year;
			e->time.tm_zone = eventList[i]->time.tm_zone;
			// Fix Quality
			e->fixquality = eventList[i]->fixquality;
			// Satelite Number
			e->satellites = eventList[i]->satellites;
			// HDOP
			e->HDOP = eventList[i]->HDOP;
			// Altitude
			e->altitude = eventList[i]->altitude;
			// GEOID
			e->geoIDHeight = eventList[i]->geoIDHeight;
		}	
		if (eventList[i]->messageType[0] == nmea_msg_t::NMEA_GPRMC)
		{
			// Copy GPRMC specific messages 
			// Add this message type
			e->messageType.emplace_back(nmea_msg_t::NMEA_GPRMC);
			// Time
			e->time.tm_gmtoff = eventList[i]->time.tm_gmtoff;
			e->time.tm_hour = eventList[i]->time.tm_hour;
			e->time.tm_isdst = eventList[i]->time.tm_isdst;
			e->time.tm_mday = eventList[i]->time.tm_mday;
			e->time.tm_min = eventList[i]->time.tm_min;
			e->time.tm_mon = eventList[i]->time.tm_mon;
			e->time.tm_sec = eventList[i]->time.tm_sec;
			e->time.tm_wday = eventList[i]->time.tm_wday;
			e->time.tm_yday = eventList[i]->time.tm_yday;
			e->time.tm_year = eventList[i]->time.tm_year;
			e->time.tm_zone = eventList[i]->time.tm_zone;
			// Data Quality
			e->dataQuality = eventList[i]->dataQuality;
			// Ground Speed
			e->speedKPH = eventList[i]->speedKPH;
			e->speedKTS = eventList[i]->speedKTS;
			// True Course
			e->course = eventList[i]->course;
		}	
		if (eventList[i]->messageType[0] == nmea_msg_t::NMEA_GPGLL)
		{
			e->messageType.emplace_back(nmea_msg_t::NMEA_GPGLL);
			// Everything else is a super set of this
			// So this is a no op
		}		
	}
	return e;
}

// All devices require a static getDeviceStatus function
// Logic for detection:
//	  Interrogation is done by:
//		1. Sending a request for the release and version
//	    2. Seeing that we got a reasonable response

device_status_t AdafruitGPS::getDeviceStatus(RobotLib *robotLib)
{
	if (successfulParse)
		return device_status_t::DEVICE_AVAILABLE;
	std::string serialPorts[] = { "/dev/ttyS0", "/dev/ttyAMA0" };
	std::stringstream ss;
	bool serialPrevOpen = false;
	for (int i = 0; i < serialPorts->length(); i++)
	{
		ss << ""; 
		ss << "Trying to connect to GPS on: " << serialPorts[i];
		robotLib->Log(ss.str());
		if (serialFD <= 0)
		{
			serialFD = serialOpen(serialPorts[i].c_str(), 9600);
		}
		else			
		{
			serialPrevOpen = true;
		}
			
		if (serialFD > 0)
		{
			ss << ""; 
			ss << "Connected to Serial: " << serialPorts[i];			
			robotLib->Log(ss.str());
			ss << PMTK_Q_RELEASE << "\n";
			serialPrintf(serialFD, ss.str().c_str());
			std::string line;
			char c = serialGetchar(serialFD);
			while(c != '$' && c!=0)
			{
				c = serialGetchar(serialFD) ;		
			}
			if (c == 0)
			{
				continue;
			}
			line += c;
			int a = 0;
			while (a < MAXLINELENGTH && c != '\n')
			{	
				if(c!='$')
					line+=c;
				c = serialGetchar(serialFD);
				a++;				
			}
			if (line.substr(0, 3) == "$GP")
			{
				if (!serialPrevOpen)
				{
					// We opened serial port for this test, close it
					serialClose(serialFD);					
				}
				ss << "";
				ss << "Detected GPS on " << serialPorts[i];
				robotLib->Log(ss.str());
				return device_status_t::DEVICE_CONNECTED;
			}			
		}		
	}
	// We tried all the serial ports and got nothing, return unavailable
	robotLib->Log("Could not detect GPS");
	return device_status_t::DEVICE_UNAVAILBLE;
}

AdafruitGPS::~AdafruitGPS()
{
	delete(nmeaParser);
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(AdafruitGPS);