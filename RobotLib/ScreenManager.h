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
		DigoleLCD *getLCD() const
		{
			return lcd;
		}
	// Returns -1 if no item is touched
	// If an item is returned, this is automatically reset to -1
		int getItemTouched()
		{
			if (lastTouched == -1)
				return -1;
			int itemId = lastTouched;
			lastTouched = -1;
			return itemId;
		}

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
		int lastTouched = -1;
};
