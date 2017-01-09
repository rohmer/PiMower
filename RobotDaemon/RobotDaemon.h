#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include "../RobotLib/RobotLib.h"
#include "../3rdParty/argtable2-13/src/argtable2.h"

typedef enum
{
	Debug,
	Warn,
	Critical,
	Exception		
} min_log_level_t;
	
class RobotDaemon
{
	public:
		int main(int argc, char *argv[]);
	
	private:
		RobotLib* robotLib;
		min_log_level_t minLogLevel;
		std::string config;
		bool processCLI(int argc, char *argv[]);
		
};
