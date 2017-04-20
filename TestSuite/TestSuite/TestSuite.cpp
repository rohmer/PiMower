#include "AllTests.h"
#include <iostream>

int main(int argc, char *argv[])
{
	RobotLib *robotLib = &RobotLib::getInstance();
	PiRobotTestLib *testLib = new PiRobotTestLib();
	RobotLibTests *robotLibTests = new RobotLibTests(testLib);
	testLib = robotLibTests->runTests();
	delete(robotLibTests);
	MapTests *mapTests = new MapTests(robotLib, testLib);
	testLib = mapTests->runTests();
	delete(mapTests);
	ConfigTests *configTests = new ConfigTests(robotLib, testLib);
	testLib = configTests->runTests();
	testLib->DisplayResults();
}