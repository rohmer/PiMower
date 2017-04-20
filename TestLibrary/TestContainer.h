#pragma once

#include <string>
#include <time.h>

enum eTestResult
{
	FAILED = 0,
	NOTRUN = 1,
	SUCCESS = 2
};

typedef struct sTestContainer
{
	time_t testTime;
	enum eTestResult testResult;
	std::string testName;
	std::string failReason;
} sTestResult;