#include "InertialGuidence.h"

InertialGuidence::InertialGuidence(RobotLib *robotLib)
{
	this->robotLib = robotLib;
	this->deviceManager = robotLib->getDeviceManager();
}

void InertialGuidence::initialize()
{
	
}