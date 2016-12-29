#include "ColorDetector.h"
#include "../../3rdParty/RapidXML/rapidxml.hpp"
#include "../../3rdParty/RapidXML/rapidxml_print.hpp"
#ifdef HAS_OPENCV
ColorDetector::ColorDetector(RobotLib *robotLib)
{
	this->robotLib = robotLib;
	initialized=initTrainingSet();
}

bool ColorDetector::initTrainingSet()
{
	// First load all the files
	DIR *dpdf;
	struct dirent *epdf;
	dpdf = opendir("/usr/local/Robot/ColorDetection");
	std::vector<std::string> files;
	if (dpdf)
	{
		while ((epdf  = readdir(dpdf)) != NULL)
		{			
			files.push_back(std::string(epdf->d_name));
		}
		closedir(dpdf);
	}
	else
	{
		robotLib->LogError("Coulding initalize training set");
		return false;
	}
	
	if (files.size() == 0)
	{
		robotLib->Log("No training data found in /usr/local/Robot/ColorDetector, run learning mode");
		return false;
	}
	
	ColorDetectionParams trainingFile = loadTrainingData();
	bool updateTrainingData = false;	
	std::vector<std::string> trainingFiles;
	for (int a = 0; a < files.size(); a++)
	{		
		std::string filename = "/usr/local/Robot/ColorDetection/" + files[a];
		cv::Mat image;
		image = cv::imread(filename);
		if (!image.data)
		{
			std::stringstream ss;
			ss << "No image data found, not processing file: " << filename;
			robotLib->Log(ss.str());
		}
		else
		{
			trainingFiles.push_back(filename);
			bool trained = false;
			for (int b = 0; b < trainingFile.filename.size(); b++)
			{
				if (trainingFile.filename[b] == filename)
					trained = true;
			}
			if (!trained)
			{				
				updateTrainingData = true;
			}
		}
	}	
	
	if (updateTrainingData)
	{		
		trainingFile=addTrainingData(trainingFiles);
		saveTrainingData(trainingFile);
	}
	return true;
}

void ColorDetector::saveTrainingData(ColorDetectionParams params)
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
	decl->append_attribute(doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
	doc.append_node(decl);

	rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "ColorDetection");
	doc.append_node(root);
	rapidxml::xml_node<>* boundsNode = doc.allocate_node(rapidxml::node_element, "Histogram");

	boundsNode->append_attribute(doc.allocate_attribute("LowerBound", std::to_string(params.lowerBound).c_str()));
	boundsNode->append_attribute(doc.allocate_attribute("UpperBound", std::to_string(params.upperBound).c_str()));
	root->append_node(boundsNode);
	
	rapidxml::xml_node<>* filesNode = doc.allocate_node(rapidxml::node_element, "Files");
	for (int a = 0; a < params.filename.size(); a++)
	{
		rapidxml::xml_node<>* fileNode = doc.allocate_node(rapidxml::node_element, "File");
		fileNode->append_attribute(doc.allocate_attribute("Name", params.filename[a].c_str()));
		filesNode->append_node(fileNode);
	}
	
	root->append_node(filesNode);
	std::string xml;
	rapidxml::print(std::back_inserter(xml), doc);
	std::ofstream filestream;
	try
	{
		filestream.open("/usr/local/Robot/ColorDetection/colorDetection.xml");
		filestream << doc;
		filestream.close();
	}
	catch (std::exception &e)
	{
		robotLib->LogException(e);
	}	
}

ColorDetectionParams ColorDetector::addTrainingData(std::vector<std::string> files)
{
	std::vector<cv::Mat> retVal;
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };

	const float *ranges[] = { range };
	std::vector<cv::Mat> inputImages;
	cv::Mat hsv, hue;
	std::vector<cv::Mat> hsvPlanes;
	for (int a = 0; a < files.size(); a++)
	{
		std::stringstream ss;
		ss << "Training positive file: " << files[a];
		robotLib->Log(ss.str());
		
		cv::Mat src = cv::imread(files[a]);
		if (src.data)
		{	
			if (src.rows != TRAINING_IMAGE_ROWS || src.cols != TRAINING_IMAGE_COLUMNS)
			{
				// Resize the image
				cv::resize(src, src, cv::Size(TRAINING_IMAGE_COLUMNS, TRAINING_IMAGE_ROWS));
				std::vector<int> params;
				params.push_back(0);
				cv::imwrite(files[a], src, params);
			}
			cv::cvtColor(src, hsv, CV_BGR2HSV_FULL);
			cv::split(hsv, hsvPlanes);
			hue = hsvPlanes[0];
			cv::GaussianBlur(hue, hue, cv::Size(7, 7), 0);
			// Push the first plane
			inputImages.push_back(hue);
		}
	}
	cv::Mat histogram;
	for (int a = 0; a < inputImages.size(); a++)
	{		
		cv::calcHist(&inputImages[a], 1, 0, cv::Mat(), histogram, 1, &histSize, &histRange, true, true);
	}
	std::map<float, int> histogramValues;
	std::vector<int> histogramCounts;
	int total = 0;
	for (int a = 0; a < 256; a++)
	{
		int val = histogram.at<float>(a);
		total += val;
		while (histogramValues.count(val) == 1)
			val++;
		histogramValues.emplace(std::pair<float, int>(val,a));				
		histogramCounts.push_back(val);
	}
	
	std::map<float, int>::iterator it;
	std::vector<float> keys;
	int a = 1;
	// Reverse order
	for (it = histogramValues.begin(); it != histogramValues.end(); it++)
	{
		keys.push_back(it->first);
	}
	std::sort(keys.begin(), keys.end());
	// now get 80% coverage
	int lowerBound = 256;
	int upperBound = 0;
	float coverage = 0;
	int totalPixels = TRAINING_IMAGE_COLUMNS*TRAINING_IMAGE_ROWS;
	int cutoff = totalPixels * 0.9;
	a = 0;
	while (coverage < cutoff)
	{
		coverage += keys[255-a];
		int colVal = histogramValues[keys[255-a]];
		if (colVal > upperBound)
			upperBound = colVal;
		if (colVal < lowerBound)
			lowerBound = colVal;
		a++;
	}
	float c = 100;
	bool tOrb = false;
	while (c > 0.9)
	{
		int t = 0;
		for (int a = lowerBound; a <= upperBound; a++)
		{
			t += histogramCounts[a];
		}
		c = (float)t / (float)totalPixels;
		if (c > 0.9)
		{
			if (tOrb)
			{
				lowerBound++;
				tOrb = false;
			}
			else
			{
				upperBound--;
				tOrb = true;
			}
		}
	}			
	
	ColorDetectionParams params;
	params.lowerBound = lowerBound;
	params.upperBound = upperBound;
	for (int a = 0; a < files.size(); a++)
		params.filename.push_back(files[a]);
	return params;
}

ColorDetectionParams ColorDetector::loadTrainingData()
{
	rapidxml::xml_document<> doc;
	ColorDetectionParams returnVal;
	std::ifstream trainingFile("/usr/local/Robot/ColorDetection/colorDetection.xml");
	if (!trainingFile.good())
		return returnVal;
	std::vector<char> buffer((std::istreambuf_iterator<char>(trainingFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	rapidxml::xml_node<> *rootNode;
	rootNode = doc.first_node("ColorDetection");
	rapidxml::xml_node<>* histNode = rootNode->first_node("Histogram");
	std::string lbs = histNode->first_attribute("greenLower")->value();
	std::string ubs = histNode->first_attribute("greenUpper")->value();
	
	if (!lbs.empty())
	{
		returnVal.lowerBound = std::stoi(lbs);
		if (!ubs.empty())
		{
			returnVal.upperBound = std::stoi(ubs);
		}
		else
		{
			returnVal.lowerBound = 0;
			returnVal.upperBound = 255;
		}
	}
	else
	{
		returnVal.lowerBound = 0;
		returnVal.upperBound = 255;
	}
	rapidxml::xml_node<>* filesNode = rootNode->first_node("Files");
	for (rapidxml::xml_node<>* fileNodes = filesNode->first_node("File"); filesNode; filesNode->next_sibling())
	{
		returnVal.filename.push_back(fileNodes->first_attribute("Name")->value());
	}
	
	return (returnVal);
}
#endif

/* XML Format 

<ColorDetection>
	<Histogram greenLower=12 greenUpper=127/>
	<files>
		<file name="foo.jpg">
	</files>
</ColorDetection>

*/