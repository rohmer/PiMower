#include "WindowManager.h"

WindowManager::WindowManager(RobotLib *robotLib, unsigned int minMilliRefresh)
{
	refreshRate = minMilliRefresh;
	shutdown = false;
	this->robotLib = robotLib;
	lcdDriver = reinterpret_cast<DigoleLCD*>(robotLib->getDeviceManager()->getByName("DigoleLCD"));
	if (!lcdDriver)
	{
		robotLib->LogError("Could not get LCD Driver");
		shutdown = true;
	}	
	int rc = pthread_create(&windowManagerThread, NULL, windowManagerHelper, this);
}

void *WindowManager::windowManagerHelper(void *wm)
{
	return (reinterpret_cast<WindowManager*>(wm)->windowManager());	
}

void *WindowManager::windowManager(void)
{	
	int *x=0, *y=0;
	while (!shutdown)
	{		
		// Draw everything that needs to be drawn
		for (int a = 0; a < uiElements.size(); a++)
		{
			if (uiElements[a]->updateNeeded())
			{
				uiElements[a]->update(lcdDriver);
			}
		}
		
		// Now get touch if any
		Point touchPoint = lcdDriver->getTouchEvent();
		if (touchPoint.x!=-1 && touchPoint.y!=-1)
		{
			// Route to proper control
			for (int a = 0; a < uiElements.size(); a++)
			{
				if (uiElements[a]->pointTouches(touchPoint))
				{
					// It can only touch one point, as its 2d, so lets break out
					a = uiElements.size();
				}
			}
		}
		msleep(refreshRate);
	}
}

int WindowManager::__nsleep(const struct timespec *req, struct timespec *rem)
{
	struct timespec temp_rem;
	if (nanosleep(req, rem) == -1)
		__nsleep(rem, &temp_rem);
	else
		return 1;		
}

int WindowManager::msleep(unsigned int milisec)
{
	struct timespec req = { 0 }, rem = { 0 };
	time_t sec = (int)(milisec / 1000);
	milisec = milisec - (sec * 1000);
	req.tv_sec = sec;
	req.tv_nsec = milisec*1000000L;
	__nsleep(&req, &rem);
	return 1;	
}

void WindowManager::addControl(UIElement *uiElement)
{
	uiElements.emplace(uiElements.begin(),uiElement);
	uiElement->update(lcdDriver);
}

WindowManager::~WindowManager()
{
	robotLib->Log("Shutting down WindowManager");
	shutdown = true;	
	pthread_join(windowManagerThread,NULL);
}
