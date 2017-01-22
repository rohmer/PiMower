#include "GrassDetectionTests.h"

double analysePctForRange(int lowerBound, int upperBound, cv::Mat inputImage)
{
	cv::Mat testImage;
	cv::inRange(inputImage, cv::Scalar(44, 90, 30), cv::Scalar(76, 255, 255), testImage);
	int num=cv::countNonZero(testImage);
	int total = testImage.rows*testImage.cols;
	double pct = static_cast<double>(num) / static_cast<double>(total) ;	
	return pct;
}

cv::Mat convertHSV(std::string file)
{
	cv::Mat image = cv::imread(file);
	cv::Mat HSV;
	int dilation_size = 4;
	cv::blur(image, image, cv::Size(2, 2));
	cv::cvtColor(image, HSV, CV_BGR2HSV);
	return HSV;
}

double boundingCoverage(cv::Mat HSV)
{
	cv::Mat greenMask;
	cv::inRange(HSV, cv::Scalar(44, 90, 30), cv::Scalar(76, 255, 255),greenMask);
	cv::Mat obstacle;
	obstacle = 255 - greenMask;
	cv::morphologyEx(obstacle, obstacle, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(obstacle, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	double pct = 0;
	int total = HSV.cols*HSV.rows;
	for (size_t i = 0; i < contours.size(); i++)
	{
		cv::Rect rr = cv::boundingRect(contours[i]);
		pct += static_cast<double>(rr.area()) / static_cast<double>(total) ;
	}
	return pct;
}

int main(int argc, char *argv[])
{
	cv::Mat HSV = convertHSV("/usr/local/Robot/Detection/Grass1.jpg");	
	float pct = analysePctForRange(38, 106, HSV);	
	float boundingArea = boundingCoverage(HSV);
	std::cout << "Grass1.jpg: " << pct << "\n";
	std::cout << "Bounding Area " << boundingArea << "\n";
	
	HSV = convertHSV("/usr/local/Robot/Detection/Grass2.jpg");	
	pct = analysePctForRange(38, 106, HSV);
	std::cout << "Grass2.jpg: " << pct << "\n";
	boundingArea = boundingCoverage(HSV);
	std::cout << "Bounding Area " << boundingArea << "\n";	
	
	HSV = convertHSV("/usr/local/Robot/Detection/Grass3.jpg");	
	pct = analysePctForRange(38, 106, HSV);
	std::cout << "Grass3.jpg: " << pct << "\n";
	boundingArea = boundingCoverage(HSV);
	std::cout << "Bounding Area " << boundingArea << "\n";	
	
	HSV = convertHSV("/usr/local/Robot/Detection/NonGrass/Gravel-Non-Grass.jpg");	
	pct = analysePctForRange(38, 106, HSV);
	std::cout << "Gravel-Non-Grass.jpg: " << pct << "\n";
	boundingArea = boundingCoverage(HSV);
	std::cout << "Bounding Area " << boundingArea << "\n";	
	
	HSV = convertHSV("/usr/local/Robot/Detection/NonGrass/Gravel-Non-Grass2.jpg");	
	pct = analysePctForRange(38, 106, HSV);
	std::cout << "Gravel-Non-Grass2.jpg: " << pct << "\n";
	boundingArea = boundingCoverage(HSV);
	std::cout << "Bounding Area " << boundingArea << "\n";	
	
	HSV = convertHSV("/usr/local/Robot/Detection/NonGrass/Stone-Non-Grass.jpg");	
	pct = analysePctForRange(38, 106, HSV);
	std::cout << "Stone-Non-Grass.jpg: " << pct << "\n";
	boundingArea = boundingCoverage(HSV);
	std::cout << "Bounding Area " << boundingArea << "\n";	
	
	HSV = convertHSV("/usr/local/Robot/Detection/NonGrass/Stone-Non-Grass2.jpg");	
	pct = analysePctForRange(38, 106, HSV);
	std::cout << "Stone-Non-Grass2.jpg: " << pct << "\n";
	boundingArea = boundingCoverage(HSV);
	std::cout << "Bounding Area " << boundingArea << "\n";	
	
}