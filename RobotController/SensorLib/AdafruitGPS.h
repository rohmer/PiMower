#pragma once	
#include "SensorLib.h"
#include "SensorBase.h"
#include "AdafruitGPSConstants.h"
#include "NMEAParser.h"
#include "../../RobotLib/DeviceRegistry.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringSerial.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <wiringSerial.h>
#include <tgmath.h>
#include <time.h>
#include <stdlib.h>
#include <thread>

class AdafruitGPS : public SensorBase
{
	public:
		AdafruitGPS(RobotLib *rl);
		AdafruitGPS(RobotLib *rl, uint32_t baudRate);
		AdafruitGPS(RobotLib *rl, uint32_t baudRate, gps_conn_t con_type);
		static device_status_t getDeviceStatus(RobotLib *robotLib);
		std::string getSensorName() override;; 
		bool getEvent(sensors_event_t*) override;		
		bool inStandby();
		~AdafruitGPS();
		sensors_type_t getSensorType() override
		{
			return SENSOR_TYPE_GPS;
		};
		void standby();
		bool wakeup();
		void setAllData();
		void setRMCGGA();
		void setRMCOnly();
		std::string getDeviceDescription() override;
		device_type_t getDeviceType() override
		{
			return device_type_t::DEVICETYPE_SENSOR;
		}
	
	private:
		gps_conn_t connectionType;
		void read();
		void initialize(uint32_t baudRate, gps_conn_t conType);
		sensors_gps_t *parse(char *nmea);
		NMEAParser *nmeaParser;
		void pause(bool p);
		int initSerial();
		char *lastNMEA(void); 
		uint8_t parseHex(char c);
		bool newNMEAreceived(void);
		void sendCommand(const char *str);
		bool waitForSentence(const char *wait4me, uint8_t max = MAXWAITSENTENCE);
		sensors_gps_t *mergeGPSEvents(std::vector<sensors_gps_t *> eventList, sensors_gps_t *e);
	
		static int serialFD;
		uint32_t baud;		
		RobotLib *robotLib;
		bool available, attached, inStandbyMode;
		sensors_gps_t currentReading;
		uint16_t LOCUS_serial, LOCUS_records;
		uint8_t LOCUS_type, LOCUS_mode, LOCUS_config, LOCUS_interval, LOCUS_distance, LOCUS_speed, LOCUS_status, LOCUS_percent;
		bool paused;
		bool receivedFlag;
		int lineidx;
		std::vector<nmea_msg_t> enabledStreams;		
		static bool successfulParse;
};
