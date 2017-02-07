#include "PathFinderTests.h"

TEST_GROUP(PathfinderTests)
{
	void setup()
	{
		pfRobotLib = new RobotLib();
		mapObject = new LawnMap(pfRobotLib);	
	}
	
	void teardown()
	{
		delete(mapObject);
		delete(pfRobotLib);
	}	
};

TEST(PathfinderTests, SimpleInit)
{
	if (!mapObject)
		FAIL("Init Failed");
}

TEST(PathfinderTests, TestPath)
{
	std::ifstream mapStream("PathTest.txt");
	int x = 0, y = 0;
	std::string line;
	while (std::getline(mapStream, line))
	{
				
		for (int a = 0; a < line.length(); a++)
		{
			switch (line[a])
			{
			case('s'):
				mapObject->setNode(x, y, map_node_t::BLOCK_BASE_STATION, std::make_pair<double, double>(x, y));
				break;
			case('x'):
				mapObject->setNode(x, y, map_node_t::BLOCK_BUMP, std::make_pair<double, double>(x, y));
				break;
			case('c'):
				mapObject->setNode(x, y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			case('g'):
				mapObject->setNode(x, y, map_node_t::BLOCK_GRASS, std::make_pair<double, double>(x, y));
				break;
			case('u'):
				mapObject->setNode(x, y, map_node_t::BLOCK_UNKNOWN, std::make_pair<double, double>(x, y));
				break;
			case('r'):
				mapObject->setNode(x, y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			}
			x++;
		}
		y++; x = 0;
	}
	mapStream.close();
	
	std::vector<MapNode *> baseStations = mapObject->getBaseStations();
	if (baseStations.size() == 0)
		FAIL("Failed to find base station");
	MapNode *baseStation = baseStations[0];
	std::stringstream ss;
	x = 0; 
	y = 0;
	x = baseStation->getGridCoord().first;
	y = baseStation->getGridCoord().second;
	ss << "Base station found at(" << x << "," << y << ")";
	pfRobotLib->Log(ss.str());
	
	
}
	
TEST(PathfinderTests, CreateMap)
{
	std::ifstream mapStream("map.txt");
	int x = 0, y = 0;
	std::string line;
	while (std::getline(mapStream, line))
	{
				
		for (int a = 0; a < line.length(); a++)
		{
			switch (line[a])
			{
			case('s'):
				mapObject->setNode(x, y, map_node_t::BLOCK_BASE_STATION, std::make_pair<double, double>(x, y));
				break;
			case('x'):
				mapObject->setNode(x, y, map_node_t::BLOCK_BUMP, std::make_pair<double, double>(x, y));
				break;
			case('c'):
				mapObject->setNode(x, y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			case('g'):
				mapObject->setNode(x, y, map_node_t::BLOCK_GRASS, std::make_pair<double, double>(x, y));
				break;
			case('u'):
				mapObject->setNode(x, y, map_node_t::BLOCK_UNKNOWN, std::make_pair<double, double>(x, y));
				break;
			case('r'):
				mapObject->setNode(x, y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			}
			x++;
		}
		y++;x = 0;
	}
	mapStream.close();
	
	if (!mapObject)
	{
		FAIL("Failed to create map");
	}
	if (mapObject->getNode(54, 16)->blockContents() != map_node_t::BLOCK_GRASS)
		FAIL("Expected node 54,16 to be map_node_t::BLOCK_GRASS");
	if (!mapObject->getNode(0, 0)->isBlocking())
		FAIL("Expected node 0,0 to be blocking")
}

TEST(PathfinderTests, PathTest1)
{
	std::ifstream mapStream("PathTest.txt");
	int x = 0, y = 0;
	std::string line;
	while (std::getline(mapStream, line))
	{
				
		for (int a = 0; a < line.length(); a++)
		{
			switch (line[a])
			{
			case('s'):
				mapObject->setNode(x, y, map_node_t::BLOCK_BASE_STATION, std::make_pair<double, double>(x, y));
				break;
			case('x'):
				mapObject->setNode(x, y, map_node_t::BLOCK_BUMP, std::make_pair<double, double>(x, y));
				break;
			case('c'):
				mapObject->setNode(x, y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			case('g'):
				mapObject->setNode(x, y, map_node_t::BLOCK_GRASS, std::make_pair<double, double>(x, y));
				break;
			case('u'):
				mapObject->setNode(x, y, map_node_t::BLOCK_UNKNOWN, std::make_pair<double, double>(x, y));
				break;
			case('r'):
				mapObject->setNode(x, y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			}
			x++;
		}
		y++; x = 0;
	}
	mapStream.close();
	
	if (!mapObject)
	{
		FAIL("Failed to create map");
	}
	std::vector<MapNode*> path = mapObject->findPath(std::make_pair(2, 3), std::make_pair(28,7));
	if (path.size() == 0)
		FAIL("Failed to find a path and one exists");
	std::stringstream ss;
	for (int a = 0; a < path.size(); a++)
	{
		if (a == 0)
			ss << "Path: (" << path[a]->getLocation().first << "," << path[a]->getLocation().second << ")";
		else
			ss << "->("<< path[a]->getLocation().first << "," << path[a]->getLocation().second << ")";
	}
	pfRobotLib->Log(ss.str());
}

TEST(PathfinderTests, TestPathMap)
{
	std::ifstream mapStream("PathTest.txt");
	int x = 0, y = 0;
	std::string line;
	while (std::getline(mapStream, line))
	{
				
		for (int a = 0; a < line.length(); a++)
		{
			switch (line[a])
			{
			case('s'):
				mapObject->setNode(x, y, map_node_t::BLOCK_BASE_STATION, std::make_pair<double, double>(x, y));
				break;
			case('x'):
				mapObject->setNode(x, y, map_node_t::BLOCK_BUMP, std::make_pair<double, double>(x, y));
				break;
			case('c'):
				mapObject->setNode(x, y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			case('g'):
				mapObject->setNode(x, y, map_node_t::BLOCK_GRASS, std::make_pair<double, double>(x, y));
				break;
			case('u'):
				mapObject->setNode(x, y, map_node_t::BLOCK_UNKNOWN, std::make_pair<double, double>(x, y));
				break;
			case('r'):
				mapObject->setNode(x, y, map_node_t::BLOCK_RANGEFINDING_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			}
			x++;
		}
		y++; x = 0;
	}
	mapStream.close();
	
	if (!mapObject)
	{
		FAIL("Failed to create map");
	}
	
	std::ifstream ms("PathTest.txt");
	x = 0, y = 0;
	while (std::getline(ms, line))
	{			
		for (int a = 0; a < line.length(); a++)
		{
			switch (line[a])
			{
			case('s'):
				if (mapObject->getCartNodeWeight(x, y) != 1)
				{
					std::stringstream ss;
					ss << "File stated (" << x << "," << y << ") was base station, expected weight 1, got weight==" << mapObject->getCartNodeWeight(x, y);
					FAIL(ss.str().c_str());
				}
				break;
			case('x'):
				if (mapObject->getCartNodeWeight(x, y) != 10)
				{
					std::stringstream ss;
					ss << "File stated (" << x << "," << y << ") was bump, expected weight 10, got weight==" << mapObject->getCartNodeWeight(x, y);
					FAIL(ss.str().c_str());
				}
				break;
			case('c'):
				if (mapObject->getCartNodeWeight(x, y) != 10)
				{
					std::stringstream ss;
					ss << "File stated (" << x << "," << y << ") was optical avoidance, expected weight 10, got weight==" << mapObject->getCartNodeWeight(x, y);
					FAIL(ss.str().c_str());
				}
				break;
			case('g'):
				if (mapObject->getCartNodeWeight(x, y) != 1)
				{
					std::stringstream ss;
					ss << "File stated (" << x << "," << y << ") was grass, expected weight 1, got weight==" << mapObject->getCartNodeWeight(x, y);
					FAIL(ss.str().c_str());
				}
				break;
			case('u'):
				if (mapObject->getCartNodeWeight(x, y) != 2)
				{
					std::stringstream ss;
					ss << "File stated (" << x << "," << y << ") was unknown, expected weight 2, got weight==" << mapObject->getCartNodeWeight(x, y);
					FAIL(ss.str().c_str());
				}
				break;
			case('r'):
				if (mapObject->getCartNodeWeight(x, y) != 4)
				{
					std::stringstream ss;
					ss << "File stated (" << x << "," << y << ") was range finding, expected weight 4, got weight==" << mapObject->getCartNodeWeight(x, y);
					FAIL(ss.str().c_str());
				}
				break;
			}
			x++;
		}
		y++; x = 0;
	}
	mapStream.close();
	
}

TEST(PathfinderTests, MultiStationPathText)
{
	std::ifstream mapStream("MultiStationPath.txt");
	int x = 0, y = 0;
	std::string line;
	while (std::getline(mapStream, line))
	{
				
		for (int a = 0; a < line.length(); a++)
		{
			switch (line[a])
			{
			case('s'):
				mapObject->setNode(x, y, map_node_t::BLOCK_BASE_STATION, std::make_pair<double, double>(x, y));
				break;
			case('x'):
				mapObject->setNode(x, y, map_node_t::BLOCK_BUMP, std::make_pair<double, double>(x, y));
				break;
			case('c'):
				mapObject->setNode(x, y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			case('g'):
				mapObject->setNode(x, y, map_node_t::BLOCK_GRASS, std::make_pair<double, double>(x, y));
				break;
			case('u'):
				mapObject->setNode(x, y, map_node_t::BLOCK_UNKNOWN, std::make_pair<double, double>(x, y));
				break;
			case('r'):
				mapObject->setNode(x, y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair<double, double>(x, y));
				break;
			}
			x++;
		}
		y++; x = 0;
	}
	mapStream.close();
	
	if (!mapObject)
	{
		FAIL("Failed to create map");
	}
	std::vector<MapNode*> path = mapObject->getPathToClosestBase(std::make_pair(2, 3));
	if (path.size() == 0)
		FAIL("Failed to find a path and one exists");
	std::stringstream ss;
	for (int a = 0; a < path.size(); a++)
	{
		if (a == 0)
			ss << "Path: (" << path[a]->getLocation().first << "," << path[a]->getLocation().second << ")";
		else
			ss << "->(" << path[a]->getLocation().first << "," << path[a]->getLocation().second << ")";
	}
	pfRobotLib->Log(ss.str());
}

