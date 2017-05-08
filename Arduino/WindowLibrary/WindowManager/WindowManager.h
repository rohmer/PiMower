#pragma once
#include "../Driver/DriverBase.h"
#include <map>
#include <vector>
#include "../UIElements/UIElement.h"
#include "Theme.h"

enum eLCDSizes
{
	lcd800x400,
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
	static WindowManager *s_instance;
	WindowManager(const uint8_t cs, const uint8_t rst = 255, const uint8_t mosi = 11,
		const uint8_t sclk = 13, const uint8_t miso = 12, eLCDSizes lcdSize = eLCDSizes::lcd800x400);
	static std::map<unsigned long, UIElement *> elementMap;

public:
	static WindowManager *instance()
	{
		return s_instance;
	}

	static WindowManager *instance(const uint8_t cs, const uint8_t rst = 255,
		const uint8_t mosi = 11, const uint8_t sclk = 13, const uint8_t miso = 12,
		eLCDSizes lcdSize = eLCDSizes::lcd800x400)
	{
		if (!s_instance)
		{
			s_instance = new WindowManager(cs, rst, mosi, sclk, miso, lcdSize);
		}
		return s_instance;
	}
	void SetThemeAttribute(eThemeObjType objType, eThemeObjState objState, eThemeObjAttribute objAttribute, uint16_t value);
	int GetThemeAttribute(eThemeObjType objType, eThemeObjState objState, eThemeObjAttribute objAttribute);

	void MoveControlToFront(unsigned long controlID);
	static void DeleteElement(unsigned long elementID);
	static void RegisterElement(unsigned long elementID, UIElement *element)
	{
		elementMap.insert(std::make_pair(elementID, element));
	}

	Point GetTouch();

private:
	~WindowManager();
	DriverBase &tft;
	std::vector<UIElement *> childElements;
};
