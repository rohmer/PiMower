#include "HTMLOutput.h"

HTMLOutput::HTMLOutput(RobotLib *robotLib, Config &config)
{
	this->robotLib = robotLib;
	this->config = config;
}

std::string HTMLOutput::generateReport()
{
	std::stringstream html;
	html << "<html><head><title>PiMower configuration at: ";
	time_t now = time(0);
	char *lt = ctime(&now);
	std::string datetime(lt);
	html << datetime;
	html << "</title></head>\n<body>\n";
	html <<"<table>\n";
	html <<"<h2>General Configuration</h2>\n";
	html <<"<ul>";
	html <<"<li><b>Logging Level</b>: ";
	switch (config.getLogLevel())
	{
	case(min_log_level_t::Debug):
		html <<"Debug</li>\n";
		break;
	case(min_log_level_t::Warn):
		html <<"Warn</li>\n";
		break;
	case(min_log_level_t::Critical):
		html <<"Critical</li>\n";
		break;
	case(min_log_level_t::Exception):
		html <<"Exception</li>\n";
		break;
	}
	html <<"</ul>";
	html <<"</table>\n<br>\n";
	html <<"<table>\n";
	html <<"<h2>Physical Configuration</h2>";
	html <<"<ul>";
	html <<"<li><b>Drive Wheel Diameter</b>: ";
	html <<(int)config.getDriveWheelDiameter();
	html <<"</li>\n";
	html <<"<li><b>Drive Gear Ratio</b>: ";
	html <<(float)config.getDriveGearRatio();
	html <<"</li>\n";
	html <<"<li><b>Drive Motor Max RPM</b>: ";
	html <<(int)config.getMaxDriveRPM();
	html <<"</li>\n";
	html <<"<li><b>Motor Encoder</b>";
	html <<"<ul>";
	html <<"<li><b>Left Drive Channel</b>:";
	std::pair<uint8_t, uint8_t> drivePins = config.getMotorEncoderPins();
	html <<(int)drivePins.first;
	html <<"</li>\n";	
	html <<"<li><b>Right Drive Channel</b>:";
	html <<(int)drivePins.second;
	html <<"</li>\n";			
	html <<"</ul></ul>";
	html <<"</table>\n<br>\n";
	html <<"<table>\n";
	html <<"<h2>Sensors</h2>\n";
	html <<"<ul><li><b>Motor Controller (PWM Controller)</b></li>\n";
	html <<"<ul><li><b>I2C Address</b>:";
	sPWMController pwmconfig=config.getPWMControllerConfig();
	html <<(int)pwmconfig.i2cChannel;
	html <<"</li>\n";
	html <<"<li><b>Left Drive Channel</b>:";
	html <<(int)pwmconfig.leftDriveChannel;
	html <<"</li>\n";
	html <<"<li><b>Right Drive Channel</b>:";
	html <<(int)pwmconfig.rightDriveChannel;
	html <<"</li>\n";
	html <<"<li><b>Blade Drive Channel</b>:";
	html <<(int)pwmconfig.bladeChannel;
	html <<"</li></ul></ul>\n";
	html << "<ul><li><b>Bumper Sensors</b></li>\n";	
	std::vector<sBumperSensor>bumperSensors=config.getBumperSensors();	
	for (int a = 0; a < bumperSensors.size(); a++)
	{	
		html << "<ul><li><b>Bumper Sensor #" << a;
		html << "</b>:</li>\n";		
		html << "<ul><li><b>GPIO Pin</b>: " << bumperSensors[a].gpioPin;
		html << "</li>\n";
		html << "<li><b>Location</b>: " << std::to_string(bumperSensors[a].location);
		html << "</li></ul></ul>\n";
	}
	html << "</ul>";
	html << "</table>\n";
	html << "</body></html>";							
	return html.str();
}