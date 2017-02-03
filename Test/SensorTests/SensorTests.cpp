#include <iostream>
#include "../../RobotLib/RobotLib.h"
#include "../../RobotController/SensorLib/ArduinoSensorHost.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPi.h"

int main(int argc, char *argv[])
{
	RobotLib *robotLib = new RobotLib();
	ArduinoSensorHost *sh = new ArduinoSensorHost(robotLib);
	//sh->addProximitySensor(12,13);	
	//sh->addSwitchSensor(14);
	//sh->addSwitchSensor(15);
	//sh->addProximitySensor(14, 15);
	std::vector <ArduinoSensorHost::sSensorReturn> r=sh->getSensorValues();
	delay(1000);
	r=sh->getSensorValues();
	/*
	wiringPiSetup();
	int i2cfd = wiringPiI2CSetup(0x44);
	std::vector<int>sensorPins;
	int triggerPin = 12;
	sensorPins.push_back(13);
	std::stringstream ss;
	ss << "P|" << triggerPin;
	for (int a = 0; a < sensorPins.size(); a++)
		ss << "," << sensorPins[a];
	robotLib->Log(ss.str());
	ss << "\0";
	write(i2cfd, ss.str().c_str(), ss.str().length());
	*/	
	
}
