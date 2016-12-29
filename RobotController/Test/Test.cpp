#include "../3rdParty/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"

#define NOMEMCHECK 1

int main(int ac, char** av)
{
#ifdef NOMEMCHECK
	MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
#endif

	return CommandLineTestRunner::RunAllTests(ac, av);
}