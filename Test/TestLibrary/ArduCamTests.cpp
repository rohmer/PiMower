#include "ArduCamTests.h"
#include "../../3rdParty/cpputest-3.8/include/CppUTest/TestHarness.h"
#include "../../3rdParty/cpputest-3.8/include/CppUTest/UtestMacros.h"

TEST_GROUP(ArduCamTests)
{
	void setup()
	{
		acRobotLib = new RobotLib();
	}
	
	void teardown()
	{
		delete(acRobotLib);
	}	
}
;

TEST(ArduCamTests, InitTrainingSet)
{
}