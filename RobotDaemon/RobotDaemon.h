#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>

#include "../RobotLib/RobotLib.h"
#include "../RobotLib/Config.h"

class RobotDaemon : public Poco::Util::ServerApplication
{
public:
	RobotDaemon();
	~RobotDaemon();
	
protected:
	void initialize(Poco::Util::Application &self);
	void uninitialize();
	void defineOptions(Poco::Util::OptionSet &options);
	void handleHelp(const std::string& name, const std::string& value);
	void displayHelp();
	int main(const Poco::Util::Application::ArgVec &args);
	void handleSim(const std::string &name, const std::string &value);
	
private:
	RobotLib* robotLib;
	min_log_level_t minLogLevel;
	std::string config;
	bool helpRequested;
};

POCO_SERVER_MAIN(RobotDaemon)

