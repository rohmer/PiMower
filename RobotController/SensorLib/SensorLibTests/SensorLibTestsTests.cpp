#include <gtest/gtest.h>
#include <stdio.h>
#include "../PCA9685.h"

/*
	This is a very basic sample demonstrating the GoogleTest framework.
	Read more about CppUTest syntax here: https://github.com/google/googletest
*/

TEST(Initialization, ScanI2CBus)
{    
	int a=PCA9685::scanForPCA9685();
}

TEST(Initialization, BaseInitializer)
{	
}

TEST(Initialization, InitializeToSpecificPort)
{	
}
