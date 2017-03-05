#include "MapTests.h"
#include "Maps.h"

MapTests::MapTests(RobotLib *robotLib, PiRobotTestLib *testLib)
{
	this->robotLib = robotLib;
	this->testLib = testLib;
}

MapTests::~MapTests()
{
	try
	{		
		testLib->AddTestResult("Map Tests",
			"Destructor Test", 
			SUCCESS);
	}
	catch (std::exception &e)
	{
		testLib->AddTestResult("Map Tests",
			"Destructor Test", 
			FAILED,
			e.what());
	}
}

void MapTests::loadYardMap()
{
	robotLib->getMap()->clear();
	int x = 0; 
	int y = 0;
	for (int a = 0; a < testYardMap.size(); a++)
	{
		for (int b = 0; b < testYardMap[a].length(); b++)
		{
			switch (testYardMap[a][b])
			{
			case('s'):
				robotLib->getMap()-> setNode(x, y, map_node_t::BLOCK_BASE_STATION, std::make_pair<double, double>(x, y));
				break;
			case('x'):
				robotLib->getMap()->setNode(x, y, map_node_t::BLOCK_BUMP, std::make_pair<double, double>(x, y));
				break;
			case('c'):
				robotLib->getMap()->setNode(x, y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			case('g'):
				robotLib->getMap()->setNode(x, y, map_node_t::BLOCK_GRASS, std::make_pair<double, double>(x, y));
				break;
			case('u'):
				robotLib->getMap()->setNode(x, y, map_node_t::BLOCK_UNKNOWN, std::make_pair<double, double>(x, y));
				break;
			case('r'):
				robotLib->getMap()->setNode(x, y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			}
			x++;
		}
		y++; x = 0;		
	}
}

void MapTests::initMapTest()
{
	if (robotLib->getMap() == NULL)	
	{
		testLib->AddTestResult("Map Tests", "Initialize Map Test", eTestResult::FAILED, "Map returned NULL");
	}
	else
	{
		testLib->AddTestResult("Map Tests", "Initialize Map Test", eTestResult::SUCCESS);
	}	
}

void MapTests::loadMapsTest()
{
	loadYardMap();	
	std::vector<MapNode *> baseStations = robotLib->getMap()->getBaseStations();
	if (baseStations.size() == 0)
	{
		testLib->AddTestResult("Map Tests", "Load Maps Test", eTestResult::FAILED, "No base stations found");
		return;
	}
	
	MapNode *baseStation = baseStations[0];
	std::stringstream ss;
	int x = 0; 
	int y = 0;
	x = baseStation->getGridCoord().first;
	y = baseStation->getGridCoord().second;
	ss << "Base station found at(" << x << "," << y << ")";
	std::clog << ss;
	robotLib->Log(ss.str());	
	testLib->AddTestResult("Map Tests",
		"Load Maps Test",
		eTestResult::SUCCESS);
}

void MapTests::closestGrassTest()
{
	loadYardMap(); 
	MapNode *node = robotLib->getMap()->closestNodeOfType(Point(0, 0), map_node_t::BLOCK_GRASS);
	if (node == NULL)
	{
		testLib->AddTestResult("Map Tests", "Closest Grass Test", eTestResult::FAILED, "Didnt find closest grass block");
		return;
	}
	std::stringstream ss;
	ss << "Closest Grass Test (" << node->getGridCoord().first << "," << node->getGridCoord().second << ")";
	testLib->AddTestResult("Map Tests", ss.str(), eTestResult::SUCCESS);
}

PiRobotTestLib *MapTests::runTests()
{
	try
	{
		initMapTest();
	}
	catch (std::exception &e)
	{
		testLib->AddTestResult("Map Tests", "Initialize Map Test", eTestResult::FAILED, e.what());		
	}
		
	try
	{
		loadMapsTest();
	}
	catch (std::exception &e)
	{
		testLib->AddTestResult("Map Tests", "Load Maps Test", eTestResult::FAILED, e.what());		
	}
	
	try
	{
		closestGrassTest();
	}
	catch (std::exception &e)
	{
		testLib->AddTestResult("Map Tests", "Closest Grass Test", eTestResult::FAILED, e.what());		
	}	
	return testLib;
}