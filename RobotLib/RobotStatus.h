#pragma once
#include "MowerState.h"
#include "Map.h"

class MowerState
{
	
	private:
		int bladeRPM;
		int odometerLeft, odometerRight;
		int leftRPM, rightRPM;
		int distanceTraveled;
		float currentBattery;
		float heading;
		
		MOWER_PATTERN_T currentMowPattern;
		MOWER_STATE_T currentMowerState;
		Map *map;		
};