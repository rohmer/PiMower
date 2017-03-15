#include "Simulator.h"

Simulator::Simulator()
{
	robotLib = &RobotLib::getInstance();	
}

bool Simulator::beginSimulation(std::string file)
{
	if (file.substr(file.find_last_of(".") + 1) == ".xml")
	{
		if (!loadSimulationFile(file))
		{
			robotLib->LogError("Could not load simulation file, simulation will not run");
			return false;
		}
	}
	else
	{
		if (!createSimulationFile(file))
		{			
			robotLib->LogError("Could not create and load simulation file, simulation will not run");			
			return false;
		}
	}	
	// We will set the simulation starting at the first dock on list
	std::vector<MapNode *> baseStation = robotLib->getMap()->getBaseStations();
	if (baseStation.size() == 0)
	{
		robotLib->LogError("Cannot begin simulation without base stations");
		return false;
	}
	std::pair <int, int> baseLoc = baseStation[0]->getGridCoord();
	robotLib->setSimulatedPosition(baseLoc.first, baseLoc.second);
	robotLib->setSimulation(true);	
	return true;
}

// Loads a previously saved map file
bool Simulator::loadSimulationFile(std::string file)
{
	robotLib->getMap()->clear();
	return robotLib->getMap()->loadMap(file);
}

// Loads a text file and creates an XML simulation file
bool Simulator::createSimulationFile(std::string file)
{	
	std::ifstream infile(file);
	if (!infile.is_open())
	{
		std::stringstream ss;
		ss << "Could not open file: " << file << " for reading";
		robotLib->LogError(ss.str());
		return false;
	}
	robotLib->getMap()->clear();	
	std::vector<std::string> lines;
	std::string line;
	while (getline(infile, line))
	{
		lines.emplace_back(line);
	}
	int xStart = lines[0].length() / 2 * -1;
	int yStart = lines.size() / 2 * -1;
	int y = 0;
	while (y < lines.size())
	{
		int x = 0;
		line = lines[y];
		while (x < line.size())
		{
			if (line[x] == 's')
			{
				robotLib->getMap()->setNode(xStart + x, yStart + y, map_node_t::BLOCK_BASE_STATION, std::make_pair(0, 0));
			}
			if (line[x] == 'x')
			{
				robotLib->getMap()->setNode(xStart + x, yStart + y, map_node_t::BLOCK_BUMP, std::make_pair(0, 0));
			}
			if (line[x] == 'c')
			{
				robotLib->getMap()->setNode(xStart + x, yStart + y, map_node_t::BLOCK_OPTICAL_AVOIDANCE, std::make_pair(0, 0));
			}
			if (line[x] == 'g')
			{
				robotLib->getMap()->setNode(xStart + x, yStart + y, map_node_t::BLOCK_GRASS, std::make_pair(0, 0));
			}
			if (line[x] == 'u')
			{
				robotLib->getMap()->setNode(xStart + x, yStart + y, map_node_t::BLOCK_UNKNOWN, std::make_pair(0, 0));
			}
			if (line[x] == 'r')
			{
				robotLib->getMap()->setNode(xStart + x, yStart + y, map_node_t::BLOCK_RANGEFINDING_AVOIDANCE, std::make_pair(0, 0));
			}
			if (line[x] == 'n')
			{				
				robotLib->getMap()->setNode(x, y, map_node_t::BLOCK_NOT_GRASS, std::make_pair<double, double>(x, y));
			}
			x++;
		}
		y++;
	}
	robotLib->getMap()->saveMap(file + ".xml");
}