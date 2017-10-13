#include "PageBase.h"

/// <summary>
/// Base class for all pages
/// Provides a chromeless window for the page to be drawn on as well as a name
/// that the UIManager will use to display
/// </summary>
/// <param name="tft">DriverBase for TFT</param>
/// <param name="pageName">The name of the page (Needs to be unique)</param>
PageBase::PageBase(DriverBase &tft, UIData *data, std::string pageName, uint16_t minimumRefreshInterval) :
	UIWindow(tft, Rectangle(0, 0, tft.width(), tft.height()), eUITextFont::None),
	pageName(pageName), showNewPage(pageName), minRefresh(minimumRefreshInterval),
	data(data)
{
	nextRefresh = 0;
}

/// <summary>
/// Destructor for Pages, makes sure all children are destroyed
/// </summary>
/// <returns></returns>
PageBase::~PageBase()
{
	for (int i = 0; i < UIElement::GetChildElements().size(); i++)
		delete(UIElement::GetChildElements()[i]);
	UIWindow::GetChildElements().clear();
}

