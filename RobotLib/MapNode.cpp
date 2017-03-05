#include "MapNode.h"

MapNode::MapNode(std::pair<int, int>coord, map_node_t blockContent, std::pair<double, double> location)
{
	this->gridX = coord.first;
	this->gridY = coord.second;
	this->nodeContent = blockContent;	
	this->latitude = location.first;
	this->latitude = location.second;
	switch (nodeContent)
	{
		case(map_node_t::BLOCK_GRASS):
			this->mapWeight = 1;
			break;
		case(map_node_t::BLOCK_BASE_STATION):
			this->mapWeight = 1;
			break;
		case(map_node_t::BLOCK_BUMP):
			this->mapWeight = 10;
			break;
		case(map_node_t::BLOCK_OPTICAL_AVOIDANCE):
			this->mapWeight = 10;
			break;
		case(map_node_t::BLOCK_RANGEFINDING_AVOIDANCE):
			this->mapWeight = 5;
			break;
		case(map_node_t::BLOCK_UNKNOWN):
			this->mapWeight = 2;
			break;
	}
}

bool MapNode::isBlocking()
{
	if (nodeContent == BLOCK_GRASS || nodeContent == BLOCK_UNKNOWN 
		|| nodeContent == BLOCK_BASE_STATION)
		return false;
	return true;	
}

std::pair<double, double> MapNode::getLocation()
{
	return std::make_pair(this->latitude, this->longitude);
}

map_node_t MapNode::blockContents() 
{
	return this->nodeContent;
}

std::pair<int, int> MapNode::getGridCoord()
{
	return (std::pair<int, int> { gridX, gridY });	
}

void MapNode::setContents(map_node_t nodeContent)
{
	this->nodeContent = nodeContent;
	switch (nodeContent)
	{
		case(map_node_t::BLOCK_GRASS):
				this->mapWeight=0;
			break;
		case(map_node_t::BLOCK_BASE_STATION):
				this->mapWeight=0;
			break;
		case(map_node_t::BLOCK_BUMP):
				this->mapWeight=50;
			break;
		case(map_node_t::BLOCK_OPTICAL_AVOIDANCE):
				this->mapWeight=50;
			break;
		case(map_node_t::BLOCK_RANGEFINDING_AVOIDANCE):
				this->mapWeight=4;
			break;
		case(map_node_t::BLOCK_UNKNOWN):
				this->mapWeight=1;
			break;
	}
}

void MapNode::setMapWeight(int weight)
{
	this->mapWeight = weight;
}

int MapNode::getMapWeight()
{
	return this->mapWeight;
}