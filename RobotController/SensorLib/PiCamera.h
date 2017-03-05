#pragma once
#include "../../RobotLib/RobotLib.h"
#include "DeviceBase.h"
#include <vector>
#include "dirent.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>

// Set HAS_OPENCV in SensorBase.h if you want to include this

#ifdef HAS_OPENCV
#include "../../3rdParty/raspicam-0.1.4/src/raspicam_cv.h"
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/persistence.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define TRAINING_DIR "/usr/local/Robot/Detection"
#define TRAINING_FILE "/usr/local/Robot/Detection/trainedFiles.xml"

#define IMAGE_WIDTH 320
#define IMAGE_HEIGHT 240

class PiCamera : DeviceBase
{
public:
	PiCamera(RobotLib *robotLib);
	device_type_t getDeviceType() override
	{
		return device_type_t::DEVICETYPE_INPUT;
	}
	std::string getDeviceName() override
	{
		return "PiCameraGrassDetection";
	}
	std::string getDeviceDescription() override
	{
		return "Grass Sensor using PiCamera";
	}
	
	bool isGrass();
	
private:
	double grassThreshold;
	bool init();
	void getThreshold();
	bool initialized;
	std::vector<std::string> getImageFiles(std::string directory);
	bool needRetraining(std::vector<std::string> availableFiles);
	void writeTrainedFiles(std::vector<std::string> filesTrained);
	raspicam::RaspiCam_Cv camera;		
};

#endif
