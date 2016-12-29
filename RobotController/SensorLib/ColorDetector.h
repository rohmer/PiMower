#pragma once
#include "SensorBase.h"

#ifdef HAS_OPENCV
#include "ColorDetectionParams.h"
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "rapidxml.hpp"

// Defines the training image sizes
#define TRAINING_IMAGE_COLUMNS 320
#define TRAINING_IMAGE_ROWS 200

class ColorDetector
{
	public:
		ColorDetector(RobotLib *robotLib);
	
	private:
		RobotLib *robotLib;
		bool initialized = false;
		bool initTrainingSet();
		ColorDetectionParams addTrainingData(std::vector<std::string> files);
		ColorDetectionParams loadTrainingData();
		void saveTrainingData(ColorDetectionParams params);
};

#endif
