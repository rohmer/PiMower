#pragma once
#include <vector>
#include "Options.h"
#include "UIElements\UIWindow.h"
#include "UIData.h"
#include "Driver\DriverBase.h"
#ifdef FT8XX
#include "Driver\FT8XXDriver.h"
#endif
#ifdef RA8875
#include "Driver\RA8875Driver.h"
#endif
#include "WindowManager/WindowManager.h"

class PageBase : public UIWindow
{
public:
	PageBase(DriverBase &tft, UIData *data, std::string pageName, uint16_t minimumRefreshInterval=100);
	~PageBase();

	std::string GetNewPage()
	{
		return showNewPage;
	}

	void SetUIData(UIData *data)
	{
		this->data = data;
	}
	
	void Update() override
	{};

	sTouchResponse ProcessTouch(Point touchPoint) override
	{};

protected:
	std::string showNewPage;
	std::string pageName;
	UIWindow *uiWindow;
	uint16_t minRefresh;
	uint32_t nextRefresh;
	UIData *data;
	WindowManager *wm;
};