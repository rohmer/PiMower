#include "MapTests.h"

TEST_GROUP(MapTests)
{
	void setup()
	{
		mapTestRobotLib = new RobotLib();
		mapTestLawnMap = new LawnMap(mapTestRobotLib);
	}
	
	void teardown()
	{
		delete(mapTestRobotLib);
		delete(mapTestLawnMap);
	}
};

void loadYardMap()
{
	mapTestLawnMap->clear();
	int x = 0; 
	int y = 0;
	for (int a = 0; a < testYardMap.size(); a++)
	{
		for (int b = 0; b < testYardMap[a].length(); b++)
		{
			switch (testYardMap[a][b])
			{
			case('s'):
				mapTestLawnMap->setNode(x, y, map_node_t::BLOCK_BASE_STATION, std::make_pair<double, double>(x, y));
				break;
			case('x'):
				mapTestLawnMap->setNode(x, y, map_node_t::BLOCK_BUMP, std::make_pair<double, double>(x, y));
				break;
			case('c'):
				mapTestLawnMap->setNode(x, y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			case('g'):
				mapTestLawnMap->setNode(x, y, map_node_t::BLOCK_GRASS, std::make_pair<double, double>(x, y));
				break;
			case('u'):
				mapTestLawnMap->setNode(x, y, map_node_t::BLOCK_UNKNOWN, std::make_pair<double, double>(x, y));
				break;
			case('r'):
				mapTestLawnMap->setNode(x, y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			}
			x++;
		}
		y++; x = 0;		
	}
}

TEST(MapTests,InitMapLib)
{
	if (mapTestLawnMap == NULL)
	{
		FAIL("Failed to init LawnMap");
	}	
}
;

TEST(MapTests, LoadMaps)
{
	loadYardMap();	
	std::vector<MapNode *> baseStations = mapTestLawnMap->getBaseStations();
	if (baseStations.size() == 0)
		FAIL("Failed to find base station");
	
	MapNode *baseStation = baseStations[0];
	std::stringstream ss;
	int x = 0; 
	int y = 0;
	x = baseStation->getGridCoord().first;
	y = baseStation->getGridCoord().second;
	ss << "Base station found at(" << x << "," << y << ")";
	mapTestRobotLib->Log(ss.str());	
}

TEST(MapTests, ClosestGrassTest)
{
	loadYardMap(); 
	MapNode *node = mapTestLawnMap->closestNodeOfType(Point(0, 0), map_node_t::BLOCK_GRASS);
}