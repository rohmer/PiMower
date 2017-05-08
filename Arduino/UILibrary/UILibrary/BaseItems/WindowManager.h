#pragma once
#include "../DisplayConst.h"
#include <vector>
#include "../UIElements/UIWindow.h"
#include "../Rectangle.h"
#include "../BaseItems/Theme.h"
#include "../Color.h"
#include "../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "../Utility/Logger.h"
#include <typeinfo>
#include <algorithm>

class UIWindow;

/*
 * Handles drawing, updating, processing of touch for all displayed items
 */
class WindowManager
{
	static WindowManager *s_instance;
	WindowManager(const uint8_t CS, const uint8_t RST = 255, const uint8_t MOSI = 11,
		const uint8_t SCLK = 13, const uint8_t MISO = 12, RA8875sizes lcdSize=RA8875sizes::RA8875_800x480);
	static std::map<unsigned long, UIElement *> elementMap;

public:
	static WindowManager *instance()
	{
		return s_instance;
	}
	static WindowManager *instance(const uint8_t CS, const uint8_t RST = 255, 
		const uint8_t MOSI = 11, const uint8_t SCLK = 13, const uint8_t MISO = 12,
		RA8875sizes lcdSize=RA8875sizes::RA8875_800x480)
	{
		if (!s_instance)
		{
			s_instance = new WindowManager(CS, RST, MOSI, SCLK, MISO,lcdSize);
		}
		return s_instance;
	}
	
	void SetThemeAttribute(eThemeObjType objType, eThemeObjState objState, eThemeObjAttribute objAttribute, uint16_t value);
	int GetThemeAttribute(eThemeObjType objType, eThemeObjState objState, eThemeObjAttribute objAttribute);

	void setActiveControl(unsigned long controlID);
	void setActiveWindow(unsigned long windowID);

	~WindowManager();
	Point GetTouch();
	
	static void DeleteElement(unsigned long elementID);
	static void RegisterElement(unsigned long elementID, UIElement *element)
	{
		elementMap.insert(std::make_pair(elementID, element));
	}

	static std::vector<UIElement *> ElementOccludes(UIElement *element);

private:
	static UIWindow *baseWindow;     // All other windows, items, etc will be child elements
							  // of this chromeless window
	Adafruit_RA8875 *lcd;
	Rectangle displaySize;
	std::vector<UIElement *> childElements;

	void createBaseWindow();
	void setDefaultTheme();
	unsigned long activeWindow;
	unsigned long activeControl;
	Theme *theme;

	static std::vector<UIElement*> getChildUIElements(UIElement *element);
};