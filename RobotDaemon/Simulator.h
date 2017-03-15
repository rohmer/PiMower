#pragma once
#include <vector>
#include "../RobotLib/RobotLib.h"

class Simulator
{
public:
	Simulator();
	
	bool beginSimulation(std::string file);
	
private:
	RobotLib *robotLib;
	bool loadSimulationFile(std::string file);
	bool createSimulationFile(std::string file);
	
};