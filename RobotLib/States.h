#pragma once

typedef enum
{
	STATE_CHARGING             = (1),
	STATE_FORWARD              = (2),
	STATE_TURN                 = (3),
	STATE_REVERSE              = (4),
	STATE_ERROR                = (5),
	STATE_STATION              = (6),
	STATE_FIND_STATION_LANDING = (7),
	STATE_FIND_STATION         = (8),
	STATE_GUIDE_TO_STATION     = (9),
	STATE_DOCKING              = (10),
	STATE_UNDOCKING            = (11),
	STATE_BUMP_FRONT           = (12),
	STATE_BUMP_BACK            = (13),
	STATE_IDLE                 = (14)
} states_t;