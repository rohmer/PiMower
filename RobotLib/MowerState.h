#pragma once

// finate state machine states
typedef enum MOWER_STATE_T
{
	STATE_OFF,          // off
	STATE_FORWARD,      // drive forward
	STATE_ROLL,         // drive roll right/left
	STATE_REVERSE,      // drive reverse
	STATE_ERROR,        // error
	STATE_STATION,       // in station
	STATE_STATION_CHARGING,       // in station charging
	STATE_STATION_CHECK, //checks if station is present
	STATE_LOW_BATTERY,		// Low battery condition, tracking station
} MOWER_STATE_T;

typedef enum MOWER_PATTERN
{
	Random = 0,
	Lane   = 1,
	Spiral = 2
} MOWER_PATTERN_T;
