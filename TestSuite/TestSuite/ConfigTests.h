#pragma once
#include "../../RobotLib/RobotLib.h"
#include "TestCommon.h"

class ConfigTests
{
public:
	ConfigTests(RobotLib *robotLib, PiRobotTestLib *testLib);
	PiRobotTestLib *runTests();	
	~ConfigTests();										
	
private:
	
};
