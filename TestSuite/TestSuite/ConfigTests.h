#pragma once
#include <fstream>
#include <iostream>
#include "../../RobotLib/RobotLib.h"
#include "TestCommon.h"

class ConfigTests
{
public:
	ConfigTests(RobotLib *robotLib, PiRobotTestLib *testLib);
	PiRobotTestLib *runTests();
	~ConfigTests();

private:
	void loadConfig();
	bool testSetup;
	RobotLib *robotLib;
	PiRobotTestLib *testLib;
};
