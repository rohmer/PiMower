#include "Args.h"

Args::Args(int argc, char *argv[])
{
	error=parseArgs(argc, argv);	
}

bool Args::parseArgs(int argc, char *argv[])
{
	struct arg_lit *verbose = arg_lit0("v", "verbose", "Verbose parsing (A lot of diagnostic messages)");
	struct arg_file *configFile = arg_filen("c", "config", NULL, 1, 1, "Configuration file to parse, default is /usr/local/Robot/config.xml");
	struct arg_lit  *help    = arg_lit0(NULL, "help", "print this help and exit");
	struct arg_end *end = arg_end(20);
	
	void* argtable[] = { verbose, configFile, help, end };
	if (arg_nullcheck(argtable) != 0)
	{
		printf("rcheckcfg: insufficient memory");
		arg_print_glossary(stdout, argtable, "  %-25s %s\n");
		arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));		
		return false;
	}
	
	if (verbose->count > 0)
	{
		verboseMode = true;
	}
	if (configFile->count > 0)
	{
		std::string c(configFile->filename[0]);
		cfgFile = c;
		std::ifstream f(cfgFile.c_str());
		if (!f.good())
		{
			printf("File: %s does not exist or is not readable\n\n\n", configFile->filename[0]);
			arg_print_glossary(stdout, argtable, "  %-25s %s\n");
			arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));				
			return false;
		}		
	}
	if (help->count > 0)
	{
		arg_print_glossary(stdout, argtable, "  %-25s %s\n");
		arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));		
		return false;				
	}
	
	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));		
	return true;		
}