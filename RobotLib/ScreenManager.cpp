#include "ScreenManager.h"

ScreenManager::ScreenManager(RobotLib *robotLib, DigoleLCD *lcd)
{
	this->lcd = lcd;
	this->shutdown = false;
	this->robotLib = robotLib;
}

ScreenManager::~ScreenManager()
{
	this->shutdown = true;
	robotLib->Log("ScreenManager shutting down");
	screenManagerThread.join();
}

void ScreenManager::start()
{
	// Start the screen manager
	ScreenManager *screenManager = this;
	screenManagerThread = std::thread(&ScreenManager::screenDriver, this);
}

int ScreenManager::addElement(UIElement *element)
{
	// First add it to our list of items
	if (element->isUITarget())
	{
		interactiveElements.emplace(elementIDCounter, element);
	}
	else
	{
		staticElements.emplace(elementIDCounter, element);
	}
	elementIDCounter++;
	elementsToUpdate.push_back(element);
}

void ScreenManager::setDirty(UIElement *element)
{
	elementsToUpdate.push_back(element);
}

void ScreenManager::screenDriver()
{
	robotLib->Log("Starting ScreenDriver");
	while (!shutdown)
	{
		int ct = 0;
		std::vector<int> elementsToRemove;
		for (std::vector<UIElement*>::iterator it = elementsToUpdate.begin(); it != elementsToUpdate.end(); ++it)
		{
			robotLib->Log("Updating Element");
			(*it)->update(lcd, NULL);
			if (!(*it)->updateRequired())
			{
				elementsToRemove.push_back(ct);
			}
			ct++;
		}
		for (std::vector<int>::iterator it = elementsToRemove.begin(); it != elementsToRemove.end(); ++it)
		{
			elementsToUpdate.erase(elementsToUpdate.begin() + *it);
		}
		elementsToRemove.clear();
		// We also need to check on touches, but for now lets just draw the screen
		/*Point pt = lcd->getTouchEvent();
			std::stringstream ss;
			ss << "Touch received: " << pt.x << "," << pt.y;
			robotLib->Log(ss.str());
			*/
		msleep(250);
	}
}

int ScreenManager::msleep(unsigned long milisec)
{
	struct timespec req = { 0 };
	time_t sec = (int)(milisec / 1000);
	milisec = milisec - (sec * 1000);
	req.tv_sec = sec;
	req.tv_nsec = milisec * 1000000L;
	while (nanosleep(&req, &req) == -1)
		continue;
	return 1;
}