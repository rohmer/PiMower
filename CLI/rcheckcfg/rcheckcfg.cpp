#include "Args.h"
#include "HTMLOutput.h"
#include "../../RobotLib/Config.h"

using namespace std;

int main(int argc, char *argv[])
{
	Args args(argc, argv);
	if (args.argError())
	{
		cout << "Error!";
		return -1;
	}

	RobotLib *robotLib = new RobotLib();
	if (args.getVerbose())
	{
		robotLib->setLogLevel(0);
	}

	Config config(robotLib);
	std::string cfgFile = args.getConfigFile();
	if (!config.getConfig(cfgFile))
	{
		robotLib->LogError("Failed to parse the configuration file, see previous errors");
		return 1;
	}
	else
	{
		robotLib->Log("Parsed config!");
	}
	HTMLOutput htmlOut(robotLib, config);
	std::string html = htmlOut.generateReport();

	if (args.getWriteHTML())
	{
		HTMLOutput htmlOut(robotLib, config);
		std::string html = htmlOut.generateReport();
		std::ofstream fs(args.getHtmlFile());
		if (!fs)
		{
			robotLib->LogError("Could not write report file");
		}
		else
		{
			fs << html;
			fs.close();
		}
	}
	return 0;
}