#include "DropDownList.h"

Rectangle DropDownList::Draw(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
	uint32_t textColor, uint32_t controlBGColor, uint32_t dropDownControlColor, uint8_t alpha,
	uint8_t cornerRadius, eUITextFont font, std::vector<std::string> items, uint8_t selectedIndex,
	bool is3D, bool dropDownPressed)
{
	Rectangle r = getMinSize(items, width, height, tft, font);
	if ((r.width + r.height / 2) > width)
		width = r.width + r.height / 2;
	if ((r.height*1.5) > height)
		height = r.height*1.5;
	
	Rectangle rect;
	if (is3D == true)
	{
		rect = UIPrimitives::RaisedPanel(tft, x, y, width, height, cornerRadius, controlBGColor, alpha);
	}
	else
	{
		rect = UIPrimitives::FlatPanel(tft, x, y, width, height, cornerRadius, controlBGColor, alpha);
	}

	// Now draw the arrow
	std::vector <Point> pts;
	Point pt;
	pt.x = rect.x2 - height - 8;
	pt.y = rect.y1 + 6;
	pts.push_back(pt);
	pt.x = rect.x2 - 8;
	pt.y = rect.y1 + 6;
	pts.push_back(pt);
	pt.x = rect.x2 - 8 - height / 2;
	pt.y = rect.y2 - 10;
	pts.push_back(pt);
	if (!dropDownPressed)
	{
		UIPrimitives::Polygon(tft, pts, textColor, alpha);
		tft.drawRect(pts[0].x - 3, pts[0].y - 3, (abs(pts[1].x - pts[0].x) + 3) + 1, (abs(pts[2].y - pts[0].y) + 7), textColor);
		tft.drawRect(pts[0].x - 2, pts[0].y - 2, (abs(pts[1].x - pts[0].x) + 4), (abs(pts[2].y - pts[0].y) + 5), textColor);
	}
	else
	{
		tft.fillRect(pts[0].x - 3, pts[0].y - 3, (abs(pts[1].x - pts[0].x) + 3) + 1, (abs(pts[2].y - pts[0].y) + 7), textColor);
		UIPrimitives::Polygon(tft, pts, controlBGColor, alpha);
	}
	// Now we need to draw the text for the selected item, then we are done :)
	UIPrimitives::Text(tft, textColor, alpha, x+cornerRadius, y+r.height+2, 
		font, is3D, items[selectedIndex], UIPrimitives::eTextHJustify::Left);

	return (rect);
}

Rectangle DropDownList::DrawExpanded(DriverBase &tft, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
		uint32_t textColor, uint32_t controlBGColor, uint32_t dropDownControlColor, uint8_t alpha,
		uint8_t cornerRadius, eUITextFont font,	std::vector<std::string> items, uint8_t selectedIndex, 
		bool is3D=true)
{
	// First we can use the Draw command, since that part is the same
	Rectangle r=Draw(tft, x, y, width, height, textColor, controlBGColor, dropDownControlColor, 
		alpha, cornerRadius, font, items, selectedIndex, is3D,true);

	// Now we need to draw the selection box, each row is R in size
	uint16_t y2 = r.y2;
	uint16_t textHeight = r.height;
	r.y1 = y2;

	r.y2 = r.y1 + r.height*items.size();
	r.update();
	Rectangle dropDownRect;
	if (is3D)
	{
		dropDownRect=UIPrimitives::RaisedPanel(tft, r.x1, r.y1, r.width, r.height, cornerRadius, controlBGColor, alpha);
	}
	else
	{
		dropDownRect=UIPrimitives::FlatPanel(tft, r.x1, r.y1, r.width, r.height, cornerRadius, controlBGColor, alpha);
	}
	
	// Now draw each of the text items
	for (int i = 0; i < items.size(); i++)
	{
		uint16_t textY = dropDownRect.y1 + ((textHeight + 1)*(i+1))-textHeight/2+2;
		if (i == selectedIndex)
		{
			UIPrimitives::FlatPanel(tft, dropDownRect.x1 + 2, textY - 2-textHeight/2, dropDownRect.width - 8, textHeight-2, 0, textColor);
			UIPrimitives::Text(tft, controlBGColor, alpha, dropDownRect.x1 + 3,
				textY, font, is3D, items[i], UIPrimitives::eTextHJustify::Left);
		}
		else
		{
			UIPrimitives::Text(tft, textColor, alpha, dropDownRect.x1 + 3,
				textY, font, is3D, items[i], UIPrimitives::eTextHJustify::Left);
		}
	}
	// Combine the rects height, r is higher
	dropDownRect.y1 = r.y1;
	return (dropDownRect);
}

// Returns -1 if the list should be collapsed, index # if one is selected
// This control will need to be redrawn by calling Draw with selected index as ProcessTouch's return
// In addition all things occluded by this controls drop down will need to be redrawn
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