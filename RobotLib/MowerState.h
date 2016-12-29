#pragma once

// finate state machine states
typedef enum MOWER_STATE
{
	STATE_OFF,          // off
	STATE_REMOTE,       // model remote control (R/C)
	STATE_FORWARD,      // drive forward
	STATE_ROLL,         // drive roll right/left  
	STATE_REVERSE,      // drive reverse
	STATE_CIRCLE,       // drive circle  
	STATE_ERROR,        // error
	STATE_PERI_FIND,    // perimeter find 
	STATE_PERI_TRACK,   // perimeter track
	STATE_PERI_ROLL,    // perimeter roll
	STATE_PERI_REV,     // perimeter reverse
	STATE_STATION,       // in station
	STATE_STATION_CHARGING,       // in station charging
	STATE_STATION_CHECK, //checks if station is present
	STATE_STATION_REV,   // charge reverse
	STATE_STATION_ROLL,  // charge roll
	STATE_STATION_FORW,  // charge forward
	STATE_MANUAL,       // manual navigation  
	STATE_ROLL_WAIT,    // drive roll right/left
	STATE_PERI_OUT_FORW, // outside perimeter forward driving without checkPerimeterBoundary()
	STATE_PERI_OUT_REV,   // outside perimeter reverse driving without checkPerimeterBoundary()
	STATE_PERI_OUT_ROLL,   // outside perimeter rolling driving without checkPerimeterBoundary()
} MOWER_STATE_T;

typedef enum MOWER_PATTERN
{
	Random = 0,
	Lane   = 1,
	Spiral = 2
} MOWER_PATTERN_T;
