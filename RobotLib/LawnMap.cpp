#include "LawnMap.h"
#include "Point.h"

LawnMap::LawnMap(RobotLib *robotLib)
{
	this->robotLib = robotLib;
	minXY = std::make_pair(0, 0);
	maxXY = std::make_pair(0, 0);
	mapModX = 0;
	mapModY = 0;
}

LawnMap::~LawnMap()
{
	robotLib->Log("Destroying LawnMap()");
	std::map<std::pair<int, int>, MapNode *>::iterator it;
	for (it = mapContents.begin(); it != mapContents.end(); it++)
	{
		delete(it->second);
	}
}

int LawnMap::getPathMap(int x, int y)
{
	return (pathMap[x][y]);	
}

void LawnMap::getExtents(std::pair<int, int> &minXY, std::pair<int, int> &maxXY)
{
	minXY = this->minXY;
	maxXY = this->maxXY;
}

void LawnMap::clear()
{
	std::map<std::pair<int, int>, MapNode *>::iterator it;
	for (it = mapContents.begin(); it != mapContents.end(); it++)
	{
		delete(it->second);
	}
	mapContents.clear();
}

void LawnMap::setNode(int x, int y, map_node_t nodeType, std::pair<double, double> location)	
{
	std::map<std::pair<int, int>, MapNode *>::iterator it = mapContents.find(std::pair<int, int>{ x, y });
	MapNode *mapNode;
			
	if (it != mapContents.end())
	{
		mapNode = it->second;
		mapNode->setContents(nodeType);
	}
	else
	{
		mapDirty = true;
		std::pair<int, int> coord;
		coord.first = x;
		coord.second = y;
		if (x < minXY.first)
		{
			minXY.first = x;
		}
		if (x > maxXY.first)
		{
			maxXY.first = x;
		}
		if (y < minXY.second)
		{
			minXY.second = y;
		}
		if (y > maxXY.second)
		{
			maxXY.second = x;
		}
		if (minXY.first < 0)
			mapModX = abs(minXY.first);
		if (minXY.second < 0)
			mapModY = abs(minXY.second);
		mapNode = new MapNode(coord, nodeType, location);
		mapContents.emplace(coord, mapNode);		
#ifdef TRACE
		std::stringstream ss;
		ss << "Added node (" << x << "," << y << ") with type: " << nodeType << " to map";		
		robotLib->Log(ss.str());
#endif
		if (nodeType == map_node_t::BLOCK_BASE_STATION)
		{
			if (std::find(baseStations.begin(), baseStations.end(), mapNode) == baseStations.end())
			{
#ifdef TRACE
				std::stringstream ss;
				ss << "Adding base station at (" << x << "," << y << ")";
				robotLib->Log(ss.str());
#endif
				baseStations.push_back(mapNode);
			}
		}
	}
}

int LawnMap::getCartNodeWeight(int x, int y)
{
	MapNode *node = getCartNode(x, y);
	if (node)
	{
		return node->getMapWeight();
	}
	// Now create an unknown node, just so we can save doing this in the
	// future
	setNode(x, y, map_node_t::BLOCK_UNKNOWN, std::make_pair<int, int>(-1, -1));
	return map_node_t::BLOCK_UNKNOWN;
}

void LawnMap::createPathMap()
{
	int h = getHeight();
	int w = getWidth();
	std::vector<int> row;
	for (int y = 0; y < h; y++)
	{
		row.clear();
		for (int x = 0; x < w; x++)
		{
			if (getCartNodeWeight(x, y) > 1)
				row.emplace_back(1);
			else
				row.emplace_back(0);
		}
		pathMap.emplace_back(row);
	}
}

MapNode *LawnMap::getCartNode(int x, int y)
{
	return getNode(x + mapModX, y + mapModY);
}

std::vector<MapNode *> LawnMap::getBaseStations()
{
	return baseStations;
}

map_node_t LawnMap::getNodeType(std::pair<int, int> location)
{
	std::map<std::pair<int, int>, MapNode *>::iterator it = mapContents.find(std::pair<int, int>{ location.first,location.second});
	if (it == mapContents.end())
	{
		return map_node_t::BLOCK_UNKNOWN;
	}
	return getNode(location.first, location.second)->blockContents();
}

map_node_t LawnMap::getNodeType(int x, int y)
{
	return getNodeType(std::make_pair(x, y));
}

map_node_t LawnMap::getNodeType(Point location)
{
	return getNodeType(std::make_pair(location.x, location.y));
}

MapNode* LawnMap::getNode(int x, int y)
{
	std::map<std::pair<int, int>, MapNode *>::iterator it = mapContents.find(std::pair<int, int>{ x, y });
	if (it == mapContents.end())
	{
		return NULL;
	}
	return it->second;
}

MapNode *LawnMap::loadMapNode(std::pair<int, int> coord)
{
	Poco::Data::Session session("SQLite", DB_LOCATION);
	Poco::Data::Statement stmt(session);
	int x, y, b, contents;
	double lat, lon;
	bool blocking;
	stmt << "SELECT (X,Y,Latitude,Longitude,Blocking,Contents) FROM LawnMap WHERE X=? AND Y=?",
		Poco::Data::Keywords::bind(coord.first),
		Poco::Data::Keywords::bind(coord.second),
		Poco::Data::Keywords::range(0, 1),
		Poco::Data::Keywords::into(x),
		Poco::Data::Keywords::into(y),
		Poco::Data::Keywords::into(b),
		Poco::Data::Keywords::into(lat),
		Poco::Data::Keywords::into(lon),
		Poco::Data::Keywords::into(blocking),
		Poco::Data::Keywords::into(contents);		
	{
		std::unique_lock<std::mutex> lock(Database::dbMutex);
		while (!stmt.done())
		{
			stmt.execute();
			MapNode *returnVal = new MapNode(std::make_pair(x, y), static_cast<map_node_t>(contents), std::make_pair(lat, lon));
			return returnVal;
		}
	}
	return NULL;
}

void LawnMap::storeMapNode(MapNode *mapNode)
{
	Poco::Data::Session session("SQLite", DB_LOCATION);
	Poco::Data::Statement stmt(session);
	double lat = mapNode->getLocation().first;
	double lon = mapNode->getLocation().second;
	int blockContents=mapNode->blockContents();
	bool isBlocking = mapNode->isBlocking();
	int gridX = mapNode->getGridCoord().first;
	int gridY = mapNode->getGridCoord().second;
	
	stmt << "UPDATE LawnMap SET Blocking=?, Contents=?, Latitude=?, Longitude=? WHERE X=? AND Y=?",
		Poco::Data::Keywords::bind(isBlocking),
		Poco::Data::Keywords::bind(blockContents),
		Poco::Data::Keywords::bind(lat),
		Poco::Data::Keywords::bind(lon),
		Poco::Data::Keywords::bind(gridX),
		Poco::Data::Keywords::bind(gridY),
		Poco::Data::Keywords::now;
	{
		std::unique_lock<std::mutex> lock(Database::dbMutex);

		if (stmt.execute() == 0)
		{
			Poco::Data::Statement stmt(session);
			stmt << "INSERT INTO LawnMap(?,?,?,?,?,?)",
				Poco::Data::Keywords::bind(gridX),
				Poco::Data::Keywords::bind(gridY);
			Poco::Data::Keywords::bind(lat),
			Poco::Data::Keywords::bind(lon),
			Poco::Data::Keywords::bind(isBlocking),
			Poco::Data::Keywords::bind(blockContents);
				
			stmt.execute();
		}
	}
}

// LawnMap format:
// <map minX=int minY=int maxX=int maxY=int>
//	<Node x=int, y=int, type=enum>
// </map>

bool LawnMap::saveMap()
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
	decl->append_attribute(doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
	doc.append_node(decl);

	rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "LawnMap");
	root->append_attribute(doc.allocate_attribute("minX", std::to_string(minXY.first).c_str()));
	root->append_attribute(doc.allocate_attribute("minY", std::to_string(minXY.second).c_str()));
	root->append_attribute(doc.allocate_attribute("maxX", std::to_string(maxXY.first).c_str()));
	root->append_attribute(doc.allocate_attribute("maxY", std::to_string(maxXY.second).c_str()));
	doc.append_node(root);
	for (std::map<std::pair<int, int>, MapNode *>::iterator it = mapContents.begin(); it != mapContents.end(); it++)
	{
		storeMapNode(it->second);
		rapidxml::xml_node<>* node = doc.allocate_node(rapidxml::node_element, "Node");
		node->append_attribute(doc.allocate_attribute("x", std::to_string(it->first.first).c_str()));
		node->append_attribute(doc.allocate_attribute("y", std::to_string(it->first.second).c_str()));
		node->append_attribute(doc.allocate_attribute("latitude", std::to_string(it->second->getLocation().first).c_str()));
		node->append_attribute(doc.allocate_attribute("longitude", std::to_string(it->second->getLocation().second).c_str()));
		node->append_attribute(doc.allocate_attribute("type", std::to_string(it->second->blockContents()).c_str()));
		root->append_node(node);
	}
	
	std::string xml;
	rapidxml::print(std::back_inserter(xml), doc);
	std::ofstream filestream;
	try
	{
		filestream.open(MAP_FILE);
		filestream << doc;
		filestream.close();
	}
	catch (std::exception &e)
	{
		robotLib->LogException(e);
		return false;
	}	
	return true;
}

bool LawnMap::loadMap()
{
	std::map<std::pair<int, int>, MapNode *>::iterator it;
	for (it = mapContents.begin(); it != mapContents.end(); it++)
	{
		delete(it->second);
	}
	mapContents.clear();
	Poco::Data::Session session("SQLite", DB_LOCATION);
	Poco::Data::Statement stmt(session);
	int x, y, b;
	double lat, lon;
	bool blocking;
	int contents;
	stmt << "SELECT (X,Y,Latitude,Longitude,Blocking,Contents) FROM LawnMap",
		Poco::Data::Keywords::into(x),
		Poco::Data::Keywords::into(y),
		Poco::Data::Keywords::into(b),
		Poco::Data::Keywords::into(lat),
		Poco::Data::Keywords::into(lon),
		Poco::Data::Keywords::into(blocking),
		Poco::Data::Keywords::into(contents),
		Poco::Data::Keywords::range(0, 1);	
	while (!stmt.done())
	{
		stmt.execute();
		MapNode *mNode = new MapNode(std::make_pair(x, y), static_cast<map_node_t>(contents), std::make_pair(lat, lon));
		mapContents.emplace(std::make_pair(x, y), mNode);
	}
}

// Adjusts the map to be 0->x as opposed to 0,0 being center
std::pair<int, int> LawnMap::getPathCoord(MapNode *node)
{
	int x=0;
	int y=0;
	std::pair<int, int> min, max;
	this->getExtents(min, max);
	std::pair<int, int> retVal;
	if (min.first < 0)
	{
		x = abs(min.first);
	}
	if (min.second < 0)
	{
		y = abs(min.second);
	}
	retVal.first = node->getGridCoord().first + x;
	retVal.second = node->getGridCoord().second + y;
	return retVal;
}
	
int LawnMap::getWidth()
{
	std::pair<int, int> min, max;
	getExtents(min, max);
	return max.first - min.first+1;
}

int LawnMap::getHeight()
{
	std::pair<int, int> min, max;
	getExtents(min, max);
	return max.second - min.second+1;
}

void LawnMap::setMapDirty(bool dirty)
{
	mapDirty = dirty;
}

bool LawnMap::getMapDirty()
{
	return mapDirty;
}

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
	return a.getPriority() > b.getPriority();
}

std::vector<MapNode *> LawnMap::findPath(std::pair<int, int> start, std::pair<int, int> end)
{
	int i, j, x, y, xdx, ydy;
	if (mapDirty)
	{
 		createPathMap();
		mapDirty = false;
	}
	// clear node maps
	std::vector<int> clearRow;
	openNodesMap.clear();
	closedNodesMap.clear();
	dirMap.clear();
	for (x = 0; x < getWidth(); x++)
		clearRow.emplace_back(0);
	for (y = 0; y < getHeight(); y++)
	{
		openNodesMap.emplace_back(clearRow);
		closedNodesMap.emplace_back(clearRow);
		dirMap.emplace_back(clearRow);
	}
	std::vector<MapNode *> path;
	
	int xStart = start.first;
	int yStart = start.second;
	int xFinish = end.first;
	int yFinish = end.second;
	
	std::priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
	int pqi; // pq index
	node* n0;
	node* m0;
	
	pqi = 0;
	// create the start node and push into list of open nodes
	n0 = new node(xStart, yStart, 0, 0);
	n0->updatePriority(xFinish, yFinish);
	pq[pqi].push(*n0);
	openNodesMap[yStart][xStart] = n0->getPriority(); // mark it on the open nodes map
	int width = getWidth();
	int height = getHeight();
	// A* search
	while (!pq[pqi].empty())
	{
	    // get the current node w/ the highest priority
	    // from the list of open nodes
		n0 = new node( pq[pqi].top().getxPos(),
			pq[pqi].top().getyPos(), 
			pq[pqi].top().getLevel(),
			pq[pqi].top().getPriority());

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); // remove the node from the open list
		openNodesMap[y][x] = 0;
		// mark it on the closed nodes map
		closedNodesMap[y][x] = 1;

		        // quit searching when the goal state is reached
		        //if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == xFinish && y == yFinish) 
		{
		    // generate the path from finish to start
		    // by following the directions
			path.clear();
			while (!(x == xStart && y == yStart))
			{
				j = dirMap[y][x];
				path.emplace_back(getCartNode(x, y));
				x += dx[j];
				y += dy[j];
			}
			// garbage collection
			delete n0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();           
			return path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i < 8; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if ((xdx >= 0 || xdx <= width - 1 || ydy >= 0 || ydy <= height - 1))
			{
				if (pathMap[ydy][xdx] != 1 && closedNodesMap[ydy][xdx] != 1)		
				{
				    // generate a child node
					m0 = new node( xdx,
						ydy,
						n0->getLevel(), 
						n0->getPriority());
					m0->nextLevel(i);
					m0->updatePriority(xFinish, yFinish);

									// if it is not in the open list then add into that
					if (openNodesMap[ydy][xdx] == 0)
					{
						openNodesMap[ydy][xdx] = m0->getPriority();
						pq[pqi].push(*m0);
						// mark its parent node direction
						dirMap[ydy][xdx] = (i + 8 / 2) % 8;
					}
					else if (openNodesMap[ydy][xdx] > m0->getPriority())
					{
					    // update the priority info
						openNodesMap[ydy][xdx] = m0->getPriority();
						// update the parent direction info
						dirMap[ydy][xdx] = (i + 8 / 2) % 8;

											// replace the node
											// by emptying one pq to the other one
											// except the node to be replaced will be ignored
											// and the new node will be pushed in instead
						while (!(pq[pqi].top().getxPos() == xdx && 
						       pq[pqi].top().getyPos() == ydy))
						{                
							pq[1 - pqi].push(pq[pqi].top());
							pq[pqi].pop();       
						}
						pq[pqi].pop(); // remove the wanted node
                    
						// empty the larger size pq to the smaller one
						if (pq[pqi].size() > pq[1 - pqi].size()) pqi = 1 - pqi;
						while (!pq[pqi].empty())
						{                
							pq[1 - pqi].push(pq[pqi].top());
							pq[pqi].pop();       
						}
						pqi = 1 - pqi;
						pq[pqi].push(*m0); // add the better node instead
					}
					else delete m0; // garbage collection
				}
			}
		}
		delete n0; // garbage collection
	}
	path.empty();
	return path;
}

std::vector<MapNode *> LawnMap::getPathToClosestBase(std::pair<int, int> start)
{
	std::vector<MapNode *> path;
	
	for (int a=0; a<baseStations.size(); a++)
	{
		std::vector<MapNode *> p = findPath(start, std::make_pair<int, int>(baseStations[a]->getGridCoord().first, baseStations[a]->getGridCoord().second));
		if (p.size() > 0 && ((p.size() < path.size()) || path.size()==0 ))
			path = p;
	}
	return path;
}

void LawnMap::clearMowedFlags()
{
	std::map<std::pair<int, int>, MapNode*>::iterator it;
	for (it = mapContents.begin(); it != mapContents.end(); it++)
	{
		it->second->setMowedFlag(false);
	}
}

MapNode *LawnMap::closestNodeOfType(Point currentLocation, map_node_t nodeType)
{
	return closestNodeOfType(std::make_pair(currentLocation.x, currentLocation.y), nodeType);
}

// Finds the closest node to the current node, using a spiral path outwards
MapNode *LawnMap::closestNodeOfType(std::pair<int, int> currentLocation, map_node_t nodeType)
{
	std::pair<int, int> minXY;
	std::pair<int, int> maxXY;
	getExtents(minXY, maxXY);
	int minX = minXY.first;
	int maxX = maxXY.first;
	int minY = minXY.second;
	int maxY = maxXY.second;
			
	int spiralSize = 0;
	Point startingPoint(currentLocation.first, currentLocation.second);
	
	while((spiralSize<(maxX-minX)) && (spiralSize<(maxY-minY)))
	{
		for (int dir = 0; dir <= 3; dir++)	
		{
			if (dir == 0)		// DOWN
			{
				int x = currentLocation.first + spiralSize;
				int y = currentLocation.first - spiralSize;
				if (y < minY)
					y = minY;
				if (x > maxX)
					x = maxX;
				for (int a = 0; a <= ((spiralSize * 2) + 1); a++)
				{
					if (getNodeType(x, y + a) == nodeType)
						return getNode(x, y + a);
				}
			}
			if (dir == 1)		// LEFT
			{
				int x = currentLocation.first + spiralSize;
				int y = currentLocation.first + spiralSize;
				if (y > maxY)
					y = maxY;
				if (x > maxX)
					x = maxX;
				for (int a = 0; a <= ((spiralSize * 2) + 1); a++)
				{
					if (getNodeType(x-a, y)== nodeType)
						return getNode(x-a, y);
				}
			}
			if (dir == 2)		// UP
			{
				int x = currentLocation.first - spiralSize;
				int y = currentLocation.first + spiralSize;
				if (y > maxY)
					y = maxY;
				if (x < minY)
					x = minY;
				for (int a = 0; a <= ((spiralSize * 2) + 1); a++)
				{
					if (getNodeType(x, y-a) == nodeType)
						return getNode(x, y-a);
				}
			}
			if (dir == 3)		// RIGHT
			{
				int x = currentLocation.first - spiralSize;
				int y = currentLocation.first - spiralSize;
				if (y < minY)
					y = minY;
				if (x < minY)
					x = minY;
				for (int a = 0; a <= ((spiralSize * 2) + 1); a++)
				{
					if (getNodeType(x+a, y)== nodeType)
						return getNode(x + a, y);
				}
			}			
		}
		spiralSize++;
	}
	
	// We did not find one on the map
	return NULL;
}

//Returns the closest grass node that hasnt been mowed
MapNode *LawnMap::closestUnmowedNode(std::pair<int, int> currentLocation)
{
	std::pair<int, int> minXY;
	std::pair<int, int> maxXY;
	getExtents(minXY, maxXY);
	int minX = minXY.first;
	int maxX = maxXY.first;
	int minY = minXY.second;
	int maxY = maxXY.second;
			
	int spiralSize = 0;
	Point startingPoint(currentLocation.first, currentLocation.second);
	
	while ((spiralSize < (maxX - minX)) && (spiralSize < (maxY - minY)))
	{
		for (int dir = 0; dir <= 3; dir++)	
		{
			if (dir == 0)		// DOWN
			{
				int x = currentLocation.first + spiralSize;
				int y = currentLocation.first - spiralSize;
				if (y < minY)
					y = minY;
				if (x > maxX)
					x = maxX;
				for (int a = 0; a <= ((spiralSize * 2) + 1); a++)
				{
					MapNode *node = getNode(x, y + a);					
					if (node->blockContents() == BLOCK_GRASS && !node->getMowedFlag())
						return node;
				}
			}
			if (dir == 1)		// LEFT
			{
				int x = currentLocation.first + spiralSize;
				int y = currentLocation.first + spiralSize;
				if (y > maxY)
					y = maxY;
				if (x > maxX)
					x = maxX;
				for (int a = 0; a <= ((spiralSize * 2) + 1); a++)
				{
					MapNode *node = getNode(x - a, y);					
					if (node->blockContents() == BLOCK_GRASS && !node->getMowedFlag())
						return node;					
				}
			}
			if (dir == 2)		// UP
			{
				int x = currentLocation.first - spiralSize;
				int y = currentLocation.first + spiralSize;
				if (y > maxY)
					y = maxY;
				if (x < minY)
					x = minY;
				for (int a = 0; a <= ((spiralSize * 2) + 1); a++)
				{
					MapNode *node = getNode(x, y - a);					
					if (node->blockContents() == BLOCK_GRASS && !node->getMowedFlag())
						return node;										
				}
			}
			if (dir == 3)		// RIGHT
			{
				int x = currentLocation.first - spiralSize;
				int y = currentLocation.first - spiralSize;
				if (y < minY)
					y = minY;
				if (x < minY)
					x = minY;
				for (int a = 0; a <= ((spiralSize * 2) + 1); a++)
				{
					MapNode *node = getNode(x+a, y);					
					if (node->blockContents() == BLOCK_GRASS && !node->getMowedFlag())
						return node;															
				}
			}			
		}
		spiralSize++;
	}
	
	// We did not find one on the map
	return NULL;
}

MapNode *LawnMap::closestUnmowedNode(Point currentLocation)
{
	return closestUnmowedNode(std::make_pair(currentLocation.x, currentLocation.y));
}