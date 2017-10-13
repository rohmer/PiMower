#pragma once

#include "WindowManager/WindowManager.h"
#include "PageBase.h"
#include "UIData.h"
#include "MainPage.h"
#include <map>

/// <summary>
/// Controls all UI Functions
/// </summary>
class UIManager
{
public:
	UIManager();
	~UIManager();
	void Update();
	
private:
	WindowManager *windowManager;
	std::map<std::string, PageBase*>pages;
	std::string currentPage;
	UIData *uidata;

	void changeDisplayedPage(std::string pageName);
};