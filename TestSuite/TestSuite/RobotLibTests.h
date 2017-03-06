#pragma once
#pragma once
#include <Poco/UUIDGenerator.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/Statement.h>
#include "../../RobotLib/RobotLib.h"
#include "TestCommon.h"
#include <iostream>
#include <fstream>

class RobotLibTests
{
public:
	RobotLibTests(PiRobotTestLib *testLib);
	PiRobotTestLib *runTests();
	~RobotLibTests();
	
private:
	PiRobotTestLib *testLib;
	RobotLib *robotLib;
	void initTest();
	void deviceManagerInit();
	void loggingTestDebug();
	void loggingTestWarn();
	void loggingTestError();
	void loggingTestException();
	std::string genUUID();
};