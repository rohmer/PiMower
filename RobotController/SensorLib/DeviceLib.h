#pragma once

typedef enum
{
	DEVICE_AVAILABLE    = (1),		// Device is connected, Initialized and functioning
	DEVICE_CONNECTED    = (2),		// Device is detected but not initialize
	DEVICE_UNCONFIGURED = (3),		// Device is detected but needs configuration to function
	DEVICE_UNAVAILBLE   = (4),		// Device can be detected and isnt connected or erroring in connection
	DEVICE_UNKNOWN      = (5),		// Cant detect device, or havent tried to communicate
	DEVICE_EMULATED     = (6)		// Device is in emulation mode
} device_status_t;

typedef enum
{
	DEVICETYPE_SENSOR = (1),
	DEVICETYPE_INPUT  = (2),
	DEVICETYPE_OUTPUT = (3),
	DEVICETYPE_IO     = (4)
} device_type_t;