#include "Args.h"

using namespace std;

int main(int argc, char *argv[])
{
	Args args(argc, argv);
	if (args.argError())
	{
		return -1;
	}
	
	RobotLib *robotLib = new RobotLib();
	if (args.getVerbose())
	{
		robotLib->setLogLevel(0);
	}
	
	Configuration *config = new Configuration(robotLib);	
	std::string cfgFile = args.getConfigFile();
	if (!config->getConfig(cfgFile))
	{
		robotLib->LogError("Failed to parse the configuration file, see previous errors");
		return -1;
	}
		
	return 0;
}