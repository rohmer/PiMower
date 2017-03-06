#include "RobotLibTests.h"

RobotLibTests::RobotLibTests(PiRobotTestLib *testLib)
{	
	this->testLib = testLib;
}

RobotLibTests::~RobotLibTests()
{
	try
	{		
		testLib->AddTestResult("RobotLib Tests",
			"Destructor Test", 
			SUCCESS);
	}
	catch (std::exception &e)
	{
		testLib->AddTestResult("RobotLib Tests",
			"Destructor Test", 
			FAILED,
			e.what());
	}
}

void RobotLibTests::initTest()
{
	try
	{
		robotLib = &RobotLib::getInstance();
		if (!robotLib)
		{
			testLib->AddTestResult("RobotLib Tests", "Init Test", FAILED, "Failed to initialize robotLib");
		}
		else
		{
			testLib->AddTestResult("RobotLib Tests", "Init Test", SUCCESS);
		}
	}
	catch (std::exception &e)
	{
		testLib->AddTestResult("RobotLib Tests", "Init Test", FAILED, e.what());
	}
}

void RobotLibTests::deviceManagerInit()
{
	try
	{	
		if (!robotLib)
			robotLib = &RobotLib::getInstance();
		if (!robotLib->getDeviceManager())
			testLib->AddTestResult("RobotLib Tests", "DeviceManager Init Test", FAILED, "Failed to initialize DeviceManager");
		else
			testLib->AddTestResult("RobotLib Tests", "DeviceManager Init Test", SUCCESS);
	}
	catch (std::exception &e)
	{
		testLib->AddTestResult("RobotLib Tests", "DeviceManager Init Test", FAILED, e.what());
	}
}

std::string RobotLibTests::genUUID()
{
	Poco::UUID uuid;
	uuid = Poco::UUIDGenerator::defaultGenerator().createRandom();
	return uuid.toString();
}

void RobotLibTests::loggingTestDebug()
{
	robotLib->setLogLevel(0);
	// Create a random UUID
	std::string uuid = genUUID();
	// Log it
	robotLib->Log(uuid);
	std::string sev = "Trace";
	std::ifstream inputFile;
	inputFile.open("Robot.log");
	std::string line;
	int offset;
	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			std::getline(inputFile, line);
			if ((offset = line.find(uuid, 0)) != std::string::npos)
			{
				if ((offset = line.find(sev, 0)) != std::string::npos)
				{
					testLib->AddTestResult("RobotLib Tests", "Log Trace", SUCCESS);
					inputFile.close();
					return;
				}
			}
		}			
	}
	testLib->AddTestResult("RobotLib Tests", "Log Trace", FAILED, "Did not find message in log file");
	inputFile.close();	
}

void RobotLibTests::loggingTestWarn()
{
	robotLib->setLogLevel(1);
	// Create a random UUID
	std::string uuid = genUUID();
	// Log it
	robotLib->LogWarn(uuid);	
	std::string sev = "Warning";
	std::ifstream inputFile;
	inputFile.open("Robot.log");
	std::string line;
	int offset;
	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			std::getline(inputFile, line);
			if ((offset = line.find(uuid, 0)) != std::string::npos)
			{
				if ((offset = line.find(sev, 0)) != std::string::npos)
				{
					testLib->AddTestResult("RobotLib Tests", "Log Warning", SUCCESS);
					inputFile.close();
					return;
				}
			}
		}			
	}
	testLib->AddTestResult("RobotLib Tests", "Log Warning", FAILED, "Did not find message in log file");
	inputFile.close();
}

void RobotLibTests::loggingTestError()
{
	robotLib->setLogLevel(2);
	// Create a random UUID
	std::string uuid = genUUID();
	// Log it
	robotLib->LogError(uuid);
	std::string sev = "Critical";
	std::ifstream inputFile;
	inputFile.open("Robot.log");
	std::string line;
	int offset;
	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			std::getline(inputFile, line);
			if ((offset = line.find(uuid, 0)) != std::string::npos)
			{
				if ((offset = line.find(sev, 0)) != std::string::npos)
				{
					testLib->AddTestResult("RobotLib Tests", "Log Critical", SUCCESS);
					inputFile.close();
					return;
				}
			}
		}			
	}
	testLib->AddTestResult("RobotLib Tests", "Log Critical", FAILED, "Did not find message in log file");
	inputFile.close();
}

void RobotLibTests::loggingTestException()
{
	robotLib->setLogLevel(0);
	// Create a random UUID
	std::string uuid = genUUID();
	struct testException : std::exception
	{
	public:
		std::string val;
		const char* what() const noexcept
		{ 
			return val.c_str();
		}
	};
	
	try
	{
		throw testException();
	}
	catch (testException &ex)
	{
		ex.val = uuid;
		robotLib->LogException(ex);
	}
	std::string sev = "Exception";
	std::ifstream inputFile;
	inputFile.open("Robot.log");
	std::string line;
	int offset;
	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			std::getline(inputFile, line);
			if ((offset = line.find(uuid, 0)) != std::string::npos)
			{
				if ((offset = line.find(sev, 0)) != std::string::npos)
				{
					testLib->AddTestResult("RobotLib Tests", "Log Exception", SUCCESS);
					inputFile.close();
					return;
				}
			}
		}			
	}
	testLib->AddTestResult("RobotLib Tests", "Log Exception", FAILED, "Did not find message in log file");
	inputFile.close();
	
}

PiRobotTestLib *RobotLibTests::runTests()
{
	initTest();
	deviceManagerInit();
	loggingTestDebug();
	loggingTestWarn();
	loggingTestError();
	loggingTestException();
	return testLib;
}