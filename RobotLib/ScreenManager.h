#pragma once
#include "UIElement.h"
#include <map>
#include <utility>
#include <thread>
#include <time.h>
#include <signal.h>
#include <vector>

/*
	Manages drawing the screen and figuring out the UI elements interaction via touch
*/

class ScreenManager
{
	public:
		ScreenManager(RobotLib *robotLib, DigoleLCD *lcd);
		~ScreenManager();
		int addElement(UIElement *element);
		void start();
		void setDirty(UIElement *element);
	
	private:	
		DigoleLCD *lcd;
		std::map<int, UIElement *> staticElements;
		std::map<int, UIElement *> interactiveElements;
		
		std::vector<UIElement *> elementsToUpdate;
		RobotLib *robotLib;
	
		std::thread screenManagerThread;
		bool shutdown;
		int elementIDCounter = 0;
	
		int msleep(unsigned long milisec);
		void screenDriver();
};

