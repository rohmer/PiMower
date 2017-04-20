#include "ConfigTests.h"
#include "TestConfig.h"

ConfigTests::ConfigTests(RobotLib *robotLib, PiRobotTestLib *testLib)
{
	this->robotLib = robotLib;
	this->testLib = testLib;

	// Write our configuration test
	std::ofstream fs("/tmp/testConfig.xml");
	if (!fs)
	{
		testLib->AddTestResult("ConfigTests", "Initialize Tests", eTestResult::FAILED, "Failed to write test configuration");
		testSetup = false;
		return;
	}
	testLib->AddTestResult("ConfigTests",
		"Initialize Tests",
		eTestResult::SUCCESS);
	fs << testConfig;
	fs.close();
	testSetup = true;
}

void ConfigTests::loadConfig()
{
	bool result = robotLib->loadConfig("/tmp/testConfig.xml");
	if (!result)
	{
		testLib->AddTestResult("ConfigTests", "Load Config Test", eTestResult::FAILED, "Failed to load Configuration File");
		return;
	}
	testLib->AddTestResult("ConfigTests",
		"Load Config Test",
		eTestResult::SUCCESS);
}

PiRobotTestLib *ConfigTests::runTests()
{
	if (!testSetup)
		return testLib;
	loadConfig();
	return testLib;
}