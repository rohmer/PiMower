#pragma once
#include "../../RobotLib/RobotLib.h"
#include "TestCommon.h"
#include "Maps.h"
#include "CppUTest/TestHarness.h"  // MUST GO LAST


RobotLib *mapTestRobotLib;
LawnMap *mapTestLawnMap;

void loadYardMap();
