#pragma once
#include "SensorBase.h"

// Set HAS_OPENCV in SensorBase.h if you want to include this

#ifdef HAS_OPENCV

class GrassDetection : public SensorBase
{
	public:	
		GrassDetection(RobotLib *robotLib);
	
	private: 
		bool init();
		bool initalized = false;
		SensorBase *imageSensor;
};

#endif

