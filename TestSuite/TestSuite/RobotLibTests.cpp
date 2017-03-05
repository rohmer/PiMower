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
	// A little hacky, but it *SHOULD* have gotten there within 5 seconds.
	std::this_thread::sleep_for(std::chrono::seconds(5));
	try
	{
		Poco::Data::Session sess = Database::getDBSession();
		Poco::Data::Statement stmt(sess);
		stmt << "SELECT * FROM Log WHERE message=?",
			Poco::Data::Keywords::bind(uuid),
			Poco::Data::Keywords::range(0, 1);
		while (!stmt.done())
		{
			if (stmt.execute() > 0)
			{
				testLib->AddTestResult("RobotLib Tests", "Logging Debug Test", SUCCESS);
				return;
			}
		}
		std::stringstream ss;
		ss << "Failed to find log entry with \"" << uuid << "\" as the message";
		testLib->AddTestResult("RobotLib Tests", "Logging Debug Test", FAILED, ss.str());
		return;
	}
	catch (std::exception &e)
	{
		testLib->AddTestResult("RobotLib Tests", "Logging Debug Test", FAILED, e.what());
	}
}

void RobotLibTests::loggingTestWarn()
{
	robotLib->setLogLevel(1);
	// Create a random UUID
	std::string uuid = genUUID();
	// Log it
	robotLib->Log(uuid);
	// A little hacky, but it *SHOULD* have gotten there within 5 seconds.
	std::this_thread::sleep_for(std::chrono::seconds(5));
	try
	{
		Poco::Data::Session sess = Database::getDBSession();
		Poco::Data::Statement stmt(sess);
		stmt << "SELECT * FROM Log WHERE message=?",
			Poco::Data::Keywords::use(uuid),
			Poco::Data::Keywords::range(0, 1);
		while (!stmt.done())
		{
			if (stmt.execute() > 0)
			{
				testLib->AddTestResult("RobotLib Tests", "Logging Warn Test", SUCCESS);
				return;
			}
		}
		std::stringstream ss;
		ss << "Failed to find log entry with \"" << uuid << "\" as the message";
		testLib->AddTestResult("RobotLib Tests", "Logging Warn Test", FAILED, ss.str());
		return;
	}
	catch (std::exception &e)
	{
		testLib->AddTestResult("RobotLib Tests", "Logging Warn Test", FAILED, e.what());
	}
}

void RobotLibTests::loggingTestError()
{
	robotLib->setLogLevel(2);
	// Create a random UUID
	std::string uuid = genUUID();
	// Log it
	robotLib->Log(uuid);
	// A little hacky, but it *SHOULD* have gotten there within 5 seconds.
	std::this_thread::sleep_for(std::chrono::seconds(5));
	try
	{
		Poco::Data::Session sess = Database::getDBSession();
		Poco::Data::Statement stmt(sess);
		stmt << "SELECT * FROM Log WHERE message=?",
			Poco::Data::Keywords::use(uuid),
			Poco::Data::Keywords::range(0, 1);
		while (!stmt.done())
		{
			if (stmt.execute() > 0)
			{
				testLib->AddTestResult("RobotLib Tests", "Logging Error Test", SUCCESS);
				return;
			}
		}
		std::stringstream ss;
		ss << "Failed to find log entry with \"" << uuid << "\" as the message";
		testLib->AddTestResult("RobotLib Tests", "Logging Error Test", FAILED, ss.str());
		return;
	}
	catch (std::exception &e)
	{
		testLib->AddTestResult("RobotLib Tests", "Logging Error Test", FAILED, e.what());
	}
}

void RobotLibTests::loggingTestException()
{
	robotLib->setLogLevel(0);
	// Create a random UUID
	std::string uuid = genUUID();
	// Log it
	robotLib->Log(uuid);
	
	// A little hacky, but it *SHOULD* have gotten there within 5 seconds.
	std::this_thread::sleep_for(std::chrono::seconds(5));
	try
	{
		Poco::Data::Session sess = Database::getDBSession();
		Poco::Data::Statement stmt(sess);
		stmt << "SELECT * FROM Log WHERE message=?",
			Poco::Data::Keywords::use(uuid),
			Poco::Data::Keywords::range(0, 1);
		while (!stmt.done())
		{
			if (stmt.execute() > 0)
			{
				testLib->AddTestResult("RobotLib Tests", "Logging Exception Test", SUCCESS);
				return;
			}
		}
		std::stringstream ss;
		ss << "Failed to find log entry with \"" << uuid << "\" as the message";
		testLib->AddTestResult("RobotLib Tests", "Logging Exception Test", FAILED, ss.str());
		return;
	}
	catch (std::exception &e)
	{
		testLib->AddTestResult("RobotLib Tests", "Logging Exception Test", FAILED, e.what());
	}
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