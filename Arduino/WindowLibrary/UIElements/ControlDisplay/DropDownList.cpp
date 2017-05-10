#include "DropDownList.h"

Rectangle DropDownList::Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
	uint32_t textColor, uint32_t controlBGColor, uint32_t dropDownControlColor, uint8_t alpha,
	uint8_t cornerRadius, eUITextFont font, std::vector<std::string> items, uint8_t selectedIndex,
	bool is3D = true)
{
	Rectangle r = getMinSize(items, width, height, tft, font);
	width = r.width;
	height = r.height;
	Rectangle rect;
	if (is3D == true)
	{
		rect = UIPrimitives::SunkenPanel(tft, x, y, width, height, cornerRadius, controlBGColor, alpha);
	}
	else
	{
		rect = UIPrimitives::FlatPanel(tft, x, y, width, height, cornerRadius, controlBGColor, alpha);
	}

	// Now draw the drop down button
	r = getDropDownButton(rect);
	if (is3D == true)
	{
		UIPrimitives::RaisedPanel(tft, r.x1, r.y1, r.width, r.height, cornerRadius, controlBGColor, alpha);
	}
	else
	{
		UIPrimitives::FlatPanel(tft, r.x1, r.y1, r.width, r.height, cornerRadius, controlBGColor, alpha);
	}

	// Now draw the arrow
	std::vector <Point> pts;
	Point pt;
	pt.x = r.x1 + 3;
	pt.y = r.y1 + 3;
	pts.push_back(pt);
	pt.x = r.x2 - 3;
	pt.y = r.y1 + 3;
	pts.push_back(pt);
	pt.x = r.center().x;
	pt.y = r.y2 - 3;
	pts.push_back(pt);
	UIPrimitives::Polygon(tft, pts, textColor, alpha);

	// Now we need to draw the text for the selected item, then we are done :)


}

Rectangle DropDownList::DrawExpanded(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
		uint32_t textColor, uint32_t controlBGColor, uint32_t dropDownControlColor, uint8_t alpha,
		uint8_t cornerRadius, eUITextFont font,	std::vector<std::string> items, uint8_t selectedIndex, 
		bool is3D=true)
{

}

// Returns -1 if the list should be collapsed, index # if one is selected
int16_t DropDownList::ProcessTouch(bool isExpanded, Point pt, DriverBase &tft, uint16_t x,
		uint16_t y, uint16_t width, uint16_t height, uint32_t textColor, uint32_t controlBGColor,
		uint32_t dropDownControlColor, uint8_t alpha, uint8_t cornerRadius, eUITextFont font,	
		std::vector<std::string> items, uint8_t selectedIndex, bool is3D=true)
{

}

Rectangle DropDownList::getMinSize(std::vector<std::string> items, uint16_t width, uint16_t height,
		DriverBase &tft, eUITextFont font)
{
	std::string longString = "";
	// Get the biggest item so we can make sure we fit
	for (int i = 0; i < items.size(); i++)
		if (items[i].length() > longString.length())
			longString = items[i];
	Rectangle minSize = FontHelper::GetTextRect(tft, longString,font,Point(0,0));
	if (width < (minSize.width+5+minSize.height))
		width = minSize.width+5+minSize.height;
	if (height < (minSize.height + 5+minSize.height))
		height = minSize.height + 5+minSize.height;
	return (minSize);
}

Rectangle DropDownList::getDropDownButton(Rectangle controlLocation)
{
	return Rectangle(controlLocation.x2-controlLocation.height-3,controlLocation.y1, 
		controlLocation.x2 - 3, controlLocation.y2);
}