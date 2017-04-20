#include <string.h>

#define DEBUG

#ifdef DEBUG
#include <SerialDebug.h>
#define debug_setup() \
	SerialDebugger.begin(9600);

#define errorPrint(LEVEL, LOCATION, MSG)	\
	SerialDebugger.debug(LEVEL,LOCATION,MSG);
#define debugPrint(MSG, LOCATION) \
	SerialDebugger.debug(NOTIFICATION,LOCATION,MSG);
#else
#define errorPrint(LEVEL,MSG)
#endif
