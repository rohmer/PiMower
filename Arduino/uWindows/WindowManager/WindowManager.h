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

enum ePowerState
{
	Normal = 0,
	LowPower = 1,
	ScreenOff =2
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

	static WindowManager *instance(const uint8_t cs, const uint8_t rst = 9,
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
	void SetLowPowerTime(uint16_t secondsToLow)
	{
		lowPowerTime = secondsToLow;
	}
	void SetScreenOffTime(uint16_t secondsToOff)
	{
		screenOffTime = secondsToOff;
	}

#ifdef RA8875
	RA8875Driver *GetDriver()
	{
		return tft;
	}
#endif

#ifdef FT8XX
	FT8XXDriver *GetDriver()
	{
		return tft;
	}
#endif


private:
	UIWindow *wmCanvas;
	static WindowManager *s_instance;
	WindowManager(const uint8_t cs, const uint8_t rst = 255, const uint8_t mosi = 11,
		const uint8_t sclk = 13, const uint8_t miso = 12, eLCDSizes lcdSize = eLCDSizes::lcd800x480);

	
	~WindowManager();
	void processTouch();
	void updatePowerTriggerTime();

#ifdef RA8875
	RA8875Driver *tft;
#endif
#ifdef FT8XX
	FT8XXDriver *tft;
#endif
	
	void updateOccluded(unsigned long id);
	
	std::map<unsigned long, UIElement *> elementMap;
	std::vector<unsigned long> elementOrder;
	ePowerState powerState = ePowerState::Normal;
	uint16_t lowPowerTime = 30;
	uint16_t screenOffTime = 300;
	uint32_t lowPowerTrigger, screenOffTrigger;
	sTouchResponse lastTouchEvent;
};
