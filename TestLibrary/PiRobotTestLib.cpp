#include "PIRobotTestLib.h"

PiRobotTestLib::PiRobotTestLib()
{
	
}

std::string PiRobotTestLib::black()
{
	return "\033[22;30m";
}

std::string PiRobotTestLib::red()
{
	return "\033[22;31m";
}
std::string PiRobotTestLib::green()
{
	return "\033[22;32m";
}
std::string PiRobotTestLib::brown()
{
	return "\033[22;33m";
}
std::string PiRobotTestLib::blue()
{
	return "\033[22;34m";
}
std::string PiRobotTestLib::magenta()
{
	return "\033[22;35m";
}
std::string PiRobotTestLib::cyan()
{
	return "\033[22;36m";
}
std::string PiRobotTestLib::gray()
{
	return "\033[22;37m";
}
std::string PiRobotTestLib::darkgray()
{
	return "\033[01;30m";
}
std::string PiRobotTestLib::lightred()
{
	return "\033[01;31m";
}

std::string PiRobotTestLib::lightgreen()
{
	return "\033[01;32m";
}
std::string PiRobotTestLib::yellow()
{
	return "\033[01;33m";
}
std::string PiRobotTestLib::lightblue()
{
	return "\033[01;34m";
}
std::string PiRobotTestLib::lightmagenta()
{
	return "\033[01;35m";
}
std::string PiRobotTestLib::lightcyan()
{
	return "\033[01;36m";
}
std::string PiRobotTestLib::white()
{
	return "\033[01;37m";
}
	
void PiRobotTestLib::AddTestResult(std::string libName, std::string testName, eTestResult testResult)
{
	std::map<std::string, std::vector<sTestContainer> >::iterator it = results.find(libName);
	std::vector<sTestContainer> libResults;
	if (it == results.end())
	{
		results[libName] = libResults;
	}
	sTestResult testResults;
	testResults.testName = testName;
	testResults.testResult = testResult;
	time(&testResults.testTime);
	results[libName].push_back(testResults);
}

void PiRobotTestLib::AddTestResult(std::string libName, std::string testName, eTestResult testResult, std::string failReason)
{
	std::map<std::string, std::vector<sTestContainer> >::iterator it = results.find(libName);
	std::vector<sTestContainer> libResults;
	if (it == results.end())
	{
		results[libName] = libResults;
	}
	sTestResult testResults;
	testResults.testName = testName;
	testResults.testResult = testResult;
	testResults.failReason = failReason;
	time(&testResults.testTime);
	results[libName].push_back(testResults);
}


void PiRobotTestLib::DisplayResults()
{
	std::clog << "\n\n";
	std::map<std::string, std::vector<sTestContainer> >::iterator it;
	int passed = 0;
	int failed = 0; 
	int notrun = 0;
	std::cout << white() << "-------------------------------------------------------------------------------\n";
	std::cout << lightcyan() << "Test Results\n";
	std::cout << white() << "-------------------------------------------------------------------------------\n";
	for (it = results.begin(); it != results.end(); it++)
	{
		std::vector<sTestContainer>::iterator tlIt;
		eTestResult lowestResult = eTestResult::SUCCESS;
		for (tlIt = it->second.begin(); tlIt != it->second.end(); tlIt++)
		{
			if (tlIt->testResult < lowestResult)
				lowestResult = tlIt->testResult;
		}
		
		std::string color = "";
		switch(lowestResult)
		{
		case eTestResult::SUCCESS:
			color = lightgreen();
			break;
		case eTestResult::NOTRUN:
			color = gray();
			break;
		case eTestResult::FAILED:
			color = lightred();
			break;
		}
		std::cout << color << it->first << "\n";
		for (tlIt = it->second.begin(); tlIt != it->second.end(); tlIt++)
		{
			switch (tlIt->testResult)
			{
			case eTestResult::SUCCESS:
				color = lightgreen();;
				passed++;
					break;
			case eTestResult::NOTRUN:
				color = gray();
				notrun++;
					break;
			case eTestResult::FAILED:
				color = lightred();
				failed++;
					break;
			}
			struct tm *timeStruct = localtime(&tlIt->testTime);			
			std::string timeStr = asctime(timeStruct);
			timeStr.erase(timeStr.find_last_not_of(" \n\r\t") + 1);
			std::cout << "	" << color << timeStr << "	" << tlIt->testName;
			if (tlIt->testResult == FAILED)
			{
				std::cout << "	" << lightred()<< tlIt->failReason;
			}
			
			std::cout << "\n";
		}
	}
	std::cout << white()<< "-------------------------------------------------------------------------------\n";
	std::cout << "Summary: " << lightgreen()<< "Passed :" << passed << "," << lightred()<< " Failed: " << failed << ", " << gray()<< "Not Run: " << notrun << "\n";	
}