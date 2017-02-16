#pragma once

typedef enum
{
	STATE_CHARGING			= (1),
	STATE_FORWARD			= (2),
	STATE_TURN				= (3),
	STATE_REVERSE			= (4),
	STATE_ERROR				= (5),
	STATE_STATION			= (6),
	STATE_FIND_STATION		= (7),
	STATE_DOCKING			= (8),
	STATE_UNDOCKING			= (9),
	STATE_BUMP_FRONT		= (10),
	STATE_BUMP_BACK			= (11),
	STATE_IDLE				= (12)
} states_t;