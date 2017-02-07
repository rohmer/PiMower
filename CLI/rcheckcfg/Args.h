#pragma once
#include "../../3rdParty/argtable2-13/src/argtable2.h"
#include "../../RobotLib/Config.h"
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
	bool getWriteHTML()
	{
		return writeHtml;
	}
	std::string getHtmlFile()
	{
		return htmlReport;
	}
	
private:
	bool error = false;
	bool writeHtml = false;
	bool parseArgs(int argc, char *argv[]);
	std::string cfgFile = "/usr/local/Robot/config.xml";
	std::string htmlReport = "config.html";
	bool verboseMode = false;
};