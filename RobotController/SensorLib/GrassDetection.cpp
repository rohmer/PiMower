#include "GrassDetection.h"

GrassDetection::GrassDetection(RobotLib *robotLib) :
	SensorBase(robotLib)
	
{	
	initialized = init();
}

// Loads the current dictionary, generates any dictionary if needed
// Also gets the image sensor 
bool GrassDetection::init()
{
	getThreshold();
	// Set camera parameters
	camera.set(CV_CAP_PROP_FORMAT, CV_8UC1);
	return true;
}

std::vector<std::string> GrassDetection::getImageFiles(std::string directory)
{
	DIR *dir;
	struct dirent *ent;
	std::vector<std::string> graphicFileTypes = { "png", "jpg", "jpeg", "gif" };
	std::vector<std::string> files;
	if ((dir = opendir(directory.c_str())) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			std::string fname = directory + "/" + ent->d_name;
			std::string::size_type idx;
			idx = fname.rfind('.');
			if (idx != std::string::npos)
			{
				std::string ext = fname.substr(idx + 1);
				std::transform(ext.begin(), ext.end(), ext.begin(),::tolower);
				for (int i = 0; i < graphicFileTypes.size(); i++)
				{
					if (graphicFileTypes[i] == ext)
					{						
						files.push_back(fname);
						i = graphicFileTypes.size() + 1;
					}
				}
			}
		}
	}
	return (files);
}

bool GrassDetection::needRetraining(std::vector<std::string> availableFiles)
{
	// First we load the trainedFiles.xml	
	std::ifstream trainingFile(TRAINING_FILE);
	if (!trainingFile.good())
	{
		robotLib->Log("Training file does not exist, regenerating");
		return true;
	}
	
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> *rootNode;
	
	std::vector<char> buffer((std::istreambuf_iterator<char>(trainingFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	rootNode = doc.first_node("TrainingFiles");
	if (!rootNode)
	{
		robotLib->Log("Training file does not have the proper root node (TrainingFiles)");
		return true;
	}
	rapidxml::xml_node<> *fileNode = rootNode->first_node("File");
	if (!fileNode)
	{
		robotLib->Log("Training file does not have File node(s)");
		return true;		
	}
	if (rootNode->first_attribute("GrassTheshold"))
		grassThreshold = atof(rootNode->first_attribute("GrassThreshold")->value());
	else
		grassThreshold = 0.01f;
	
	
	for (rapidxml::xml_node<> *fn = rootNode->first_node("File"); fn; fn = rootNode->next_sibling())
	{
		if (fn->first_attribute("Name"))
		{
			bool found = false;
			std::string file = fn->first_attribute("Name")->value();
			for (int a = 0; a < availableFiles.size(); a++)
			{
				if (availableFiles[a] == file)
				{
					found = true;
					availableFiles.erase(std::remove(availableFiles.begin(), availableFiles.end(), file), availableFiles.end());
					a = availableFiles.size() + 1;
				}
			}
			if (found == false)
			{
				return true;
			}
		}
	}
	if (availableFiles.size() > 0)
		return true;
	return false;
}

void GrassDetection::writeTrainedFiles(std::vector<std::string> filesTrained)
{
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<>* rootNode = doc.allocate_node(node_element, "TrainingFiles");
	for (int a = 0; a < filesTrained.size(); a++)
	{
		xml_node<>* fileNode = doc.allocate_node(node_element, "File");
		fileNode->append_attribute(doc.allocate_attribute("Name", filesTrained[a].c_str()));
		rootNode->append_node(fileNode);
	}
	rootNode->append_attribute(doc.allocate_attribute("GrassThreshold", std::to_string(grassThreshold).c_str()));
	doc.append_node(rootNode);
	std::string xmlString;
	print(std::back_inserter(xmlString), doc);
	std::ofstream trainedFiles;
	trainedFiles.open(TRAINING_FILE);
	trainedFiles << xmlString << "\n";
	trainedFiles.close();
}

void GrassDetection::getThreshold()
{
	std::vector<std::string> trainingFiles = getImageFiles(TRAINING_DIR);
	if (!needRetraining(trainingFiles) && grassThreshold!=0)
	{
		robotLib->Log("Training unnecessary");
		return;
	}
	cv::Mat input;
	cv::Ptr<cv::Feature2D> f2d = cv::xfeatures2d::SIFT::create();	
	std::vector<cv::KeyPoint> keypoints;	
	cv::Mat descriptor,featuresUnclustered;
	float lowestPct = 1;
	for (int a = 0; a < trainingFiles.size(); a++)
	{
		std::stringstream ss;
		ss << "Working on file: " << trainingFiles[a];
		robotLib->Log(ss.str());
		// Load image
		input = cv::imread(trainingFiles[a]);
		cv::blur(input, input, cv::Size(2, 2));
		cv::cvtColor(input, input, CV_BGR2HSV);
		cv::Mat HSV;
		cv::inRange(input, cv::Scalar(44, 90, 30), cv::Scalar(76, 255, 255), HSV);
		int num = cv::countNonZero(HSV);
		int total = HSV.rows*HSV.cols;
		double pct = static_cast<double>(num) / static_cast<double>(total);	
		if (pct < lowestPct)
			lowestPct = pct;
	}
	grassThreshold = lowestPct - (lowestPct * 0.005);
	writeTrainedFiles(trainingFiles);
}

bool GrassDetection::getEvent(sensors_event_t *event)
{
	if (!initialized)
	{		
		init();
		if (!initialized)
		{
			robotLib->LogError("Cannot initialize GrassDetection");
			return false;
		}			
	}
	//memset(event, 0, sizeof(sensors_event_t));
	
	if (!camera.isOpened())
	{
		if (!camera.open())
		{
			robotLib->LogError("Error opening camera");
			return false;
		}
	}
	
	// Capture an image
	cv::Mat image;
	camera.grab();
	camera.retrieve(image);
	cv::blur(image, image, cv::Size(2, 2));
	cv::cvtColor(image, image, CV_BGR2HSV);
	cv::Mat HSV;
	cv::inRange(image, cv::Scalar(44, 90, 30), cv::Scalar(76, 255, 255), HSV);
	int num = cv::countNonZero(HSV);
	int total = HSV.rows*HSV.cols;
	double pct = static_cast<double>(num) / static_cast<double>(total);	
	if (pct > grassThreshold)
	{
		event->objectDetection.objectDetected = true;
		event->objectDetection.pctCertainty = pct;
	}
	return true;
}
