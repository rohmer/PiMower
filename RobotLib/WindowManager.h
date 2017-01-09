#pragma once
#include "UIElement.h"
#include <vector>
#include <pthread.h>
#include <time.h>
/*
	Handles drawing everything and responding to input
*/

class WindowManager
{
	public:
		WindowManager(RobotLib *robotLib, unsigned int minMilliRefresh=250);
		~WindowManager();
		void addControl(UIElement *uiElement);
	
		void *windowManager(void);
		static void *windowManagerHelper(void *wm);
	
	private:
		int msleep(unsigned int milisec);
		int __nsleep(const struct timespec *req, struct timespec *rem);
		int refreshRate;
		RobotLib *robotLib;
		DigoleLCD *lcdDriver;
		std::vector<UIElement *> uiElements;
		bool shutdown;	
		pthread_t windowManagerThread;		
};