#pragma once
#include "../UIElements/UIWindow.h"
#include <map>
#include <vector>
#include <algorithm>

#ifdef FT8XX
#include "../Driver/FT8XXDriver.h"
#endif
#ifdef RA8875 
#include "../Driver/RA8875Driver.h"
#endif

enum eLCDSizes
{
	lcd800x480,
	lcd480x272
};

/// <summary>
/// This is the base class of the UI Library
//		* Controls all window functions
//		* Provides chromeless base-window for holding everything
//		* Handles all input
/// </summary>
class WindowManager
{
public:
	static WindowManager *instance()
	{
		return s_instance;
	}

	static WindowManager *instance(const uint8_t cs=10, const uint8_t rst = 9,
		const uint8_t mosi = 11, const uint8_t sclk = 13, const uint8_t miso = 12,
		eLCDSizes lcdSize = eLCDSizes::lcd800x480)
	{
		if (!s_instance)
		{
			s_instance = new WindowManager(cs, rst, mosi, sclk, miso, lcdSize);
		}
		return s_instance;
	}

	void MoveControlToFront(unsigned long controlID);
	void DeleteElement(unsigned long elementID);
	
	void RegisterElement(UIElement *element);

	void Update();
	

private:
	UIWindow *wmCanvas;
	static WindowManager *s_instance;
	WindowManager(const uint8_t cs, const uint8_t rst = 255, const uint8_t mosi = 11,
		const uint8_t sclk = 13, const uint8_t miso = 12, eLCDSizes lcdSize = eLCDSizes::lcd800x480);

	~WindowManager();
	void processTouch();

#ifdef RA8875
	RA8875Driver tft;
#endif
#ifdef FT8875
	FT8XXDriver tft;
#endif
	
	void updateOccluded(unsigned long id);
	
	std::map<unsigned long, UIElement *> elementMap;
	std::vector<unsigned long> elementOrder;
	
	sTouchResponse lastTouchEvent;
};
