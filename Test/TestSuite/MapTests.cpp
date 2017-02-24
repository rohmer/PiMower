#include "MapTests.h"

TEST_GROUP(MapTests)
{
	void setup()
	{
		robotLib = new RobotLib();
	}
	
	void teardown()
	{
		delete (robotLib);
	}
};

