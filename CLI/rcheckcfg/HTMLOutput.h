#pragma once
#include "../../RobotLib/Config.h"
#include "../../RobotLib/RobotLib.h"
#include <ctime>

class HTMLOutput
{
public:
	HTMLOutput(RobotLib *robotLib, Config &config);
	std::string generateReport();

private:
	RobotLib *robotLib;
	Config config;
};