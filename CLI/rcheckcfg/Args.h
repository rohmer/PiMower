#pragma once
#include "../../3rdParty/argtable2-13/src/argtable2.h"
#include "../../RobotLib/Configuration.h"
#include <string>
#include <stdio.h>

class Args
{
public:
	Args(int argc, char *argv[]);
	std::string getConfigFile()
	{
		return cfgFile;
	}
	bool getVerbose()
	{
		return verboseMode;
	}
	bool argError()
	{
		return error;
	}
		
private:
	bool error = false;
	bool parseArgs(int argc, char *argv[]);
	std::string cfgFile = "/usr/local/Robot/config.xml";
	bool verboseMode = false;
};