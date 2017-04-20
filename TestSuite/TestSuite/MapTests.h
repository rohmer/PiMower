#pragma once
#include "../../RobotLib/RobotLib.h"
#include "TestCommon.h"

class MapTests
{
public:
	MapTests(RobotLib *robotLib, PiRobotTestLib *testLib);
	PiRobotTestLib *runTests();
	~MapTests();

private:
	void loadYardMap();
	void initMapTest();
	void loadMapsTest();
	void closestGrassTest();
	RobotLib *robotLib;
	PiRobotTestLib *testLib;
};
