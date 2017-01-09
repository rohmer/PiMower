#include "RobotDaemon.h"

int RobotDaemon::main(int argc, char *argv[])
{
	if (!processCLI(argc, argv))
		return 0;
	robotLib = new RobotLib();
	switch (minLogLevel)
	{
		case Debug:
		robotLib->setLogLevel(0);
		break;
		case Warn:
			robotLib->setLogLevel(1);
			break;
		case(Critical):
			robotLib->setLogLevel(2);
			break;
		case(Exception):
			robotLib->setLogLevel(3);
			break;		
	}
}

bool RobotDaemon::processCLI(int argc, char *argv[])
{
	struct arg_lit *debug = arg_lit0("d", "debug,verbose", "Verbose logging messages");
	struct arg_lit *warn = arg_lit0("w", "warn", "Warning logging messages");
	struct arg_lit *crit = arg_lit0("c", "crit", "Critical logging messages");
	struct arg_lit *except = arg_lit0("e", "exception", "Only exception logging messages");
	struct arg_file *configFile = arg_file0("c", "config", "<file>", "Configuration file");
	struct arg_end *end = arg_end(20);
	
	void *argtable[] = { debug, warn, crit, except, configFile, end };
	if (arg_nullcheck(argtable) != 0)
	{
		printf("Error: insufficent memory\n");	
		return false;
	}
	int nerrors = arg_parse(argc, argv, argtable);
	if(nerrors==0)
	{
		if (configFile->count > 0)
			config = std::string(configFile->filename[0]);
		if (except->count > 0)
			minLogLevel = Exception;
		if (crit->count > 0)
			minLogLevel = Critical;
		if (warn->count > 0)
			minLogLevel = Warn;
		if (debug->count > 0)
			minLogLevel = Debug;
		return true;
	}
	
	arg_print_errors(stdout, end, "RobotDaemon");
	return false;
}