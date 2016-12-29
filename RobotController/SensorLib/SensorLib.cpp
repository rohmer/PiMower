#include "SensorLib.h"

/*
	To test the library, include "SensorLib.h" from an application project
	and call SensorLibTest().
	
	Do not forget to add the library to Project Dependencies in Visual Studio.
*/

static int s_Test = 0;

int SensorLibTest()
{
	return ++s_Test;
}