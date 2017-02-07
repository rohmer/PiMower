#pragma once
#include "MapLibConstants.h"
#include <utility>

class MapNode
{
	public:
		MapNode(std::pair<int,int> coord, map_node_t nodeContent, std::pair<double,double> location);	
		std::pair<int,int> getGridCoord();
		map_node_t blockContents() const;
		bool isBlocking() const;
		void setContents(map_node_t nodeContent);
		std::pair<double, double> getLocation();
		void setMapWeight(int weight);
		int getMapWeight();
		void setMowedFlag(bool val)
		{
			mowedSession = val;
		}
	
	private:
		int gridX;
		int gridY;
		double latitude, longitude;			// Approximate location of center per GPS
		map_node_t nodeContent;
		int mapWeight;
		bool mowedSession;
};
