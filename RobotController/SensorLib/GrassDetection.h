#pragma once
#include "SensorBase.h"
#include <vector>
#include "dirent.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>

// Set HAS_OPENCV in SensorBase.h if you want to include this

#ifdef HAS_OPENCV
#include <raspicam/raspicam_cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/persistence.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#define TRAINING_DIR "/usr/local/Robot/Detection"
#define TRAINING_FILE "/usr/local/Robot/Detection/trainedFiles.xml"
#define TRAINING_VOCAB "/usr/local/Robot/Detection/vocab.xml"
#define TRAINING_DICT_SIZE 500

class GrassDetection : public SensorBase
{
	public:	
		GrassDetection(RobotLib *robotLib);
		device_type_t getDeviceType() override
		{
			return DEVICETYPE_SENSOR;
		}
		std::string getDeviceName() override
		{
			return "GrassSensor";
		}
		std::string getDeviceDescription() override
		{
			return "Grass Sensor using Raspicam";
		}
		sensors_type_t getSensorType() override
		{
			return SENSOR_TYPE_IMAGING;
		}
		bool getEvent(sensors_event_t *event) override;
	
	private: 
		double grassThreshold;
		bool init();
		void getThreshold();
		SensorBase *imageSensor;
		bool initialized;
		std::vector<std::string> getImageFiles(std::string directory);
		bool needRetraining(std::vector<std::string> availableFiles);
		void writeTrainedFiles(std::vector<std::string> filesTrained);
		raspicam::RaspiCam_Cv camera;
};

#endif

