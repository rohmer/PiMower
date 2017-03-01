#include "AllTests.h"
#include "CppUTest/CommandLineTestRunner.h"
#include <iostream>

int main(int argc, char *argv[])
{	
	try
	{
		CommandLineTestRunner::RunAllTests(argc, argv);
	}
	catch (std::exception &e)
	{
		std::clog << "Error;";
	}
	return 0;
}