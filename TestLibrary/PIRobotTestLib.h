#pragma once
#include <map>
#include <vector>
#include "TestContainer.h"
#include <time.h>
#include <sstream>
#include <iostream>

class PiRobotTestLib
{
public:
	PiRobotTestLib();
	void AddTestResult(std::string libName, std::string testName, eTestResult testResult);
	void AddTestResult(std::string libName, std::string testName, eTestResult testResult, std::string failReason);
	void DisplayResults();
	std::string black();
	std::string red();
	std::string green();
	std::string brown();
	std::string blue();
	std::string magenta();
	std::string cyan();
	std::string gray();
	std::string darkgray();
	std::string lightred();
	std::string lightgreen();
	std::string yellow();
	std::string lightblue();
	std::string lightmagenta();
	std::string lightcyan();
	std::string white();

private:
	std::map<std::string, std::vector<sTestContainer> > results;
	std::map<std::string, std::string> colors;
};