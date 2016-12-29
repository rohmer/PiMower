#include "RobotLibTests.h"

TEST_GROUP(RobotLib)
{	
}
;

TEST(RobotLib, InitTest)
{
	robotLib = new RobotLib();
	if (!robotLib)
	{
		FAIL("RobotLib not initalized");
	}
	delete(robotLib);	
}

TEST(RobotLib, LoggerTests)
{
	robotLib = new RobotLib();
	robotLib->Log("Test");
	robotLib->LogWarn("TestWarn");
	robotLib->LogError("TestError");	
}