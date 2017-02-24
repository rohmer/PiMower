#include "MapTests.h"

TEST_GROUP(MapTests)
{
	void setup()
	{
		mapTestRobotLib = new RobotLib();
	}
	
	void teardown()
	{
		delete(mapTestRobotLib);
	}
};

TEST(MapTests,InitMapLib)
{
	LawnMap *lawnMap=new LawnMap(mapTestRobotLib);
	if (lawnMap == NULL)
	{
		FAIL("Failed to init LawnMap");
	}
	delete(lawnMap);
}