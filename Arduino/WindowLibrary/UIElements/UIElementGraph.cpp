#include "UIElementGraph.h"
#ifdef useElementGraph

UIElementGraph::UIElementGraph(DriverBase &tft, Rectangle location, CircularMinMaxBuffer &inValues,
	std::string itemLabel, eUITextFont font,
	tColor textColor, uint8_t textScale, tColor graphColor, tColor bgColor,
	eGraphType graphType = eGraphType::BarGraph,
	uint8_t cornerRadius = 4, std::string elementName = "", uint8_t alpha = 255) :
	UIElement(tft, location, elementName, eElementType::NotInteractive), values(inValues)	
{
	this->itemLabel = itemLabel;
	this->cornerRadius = cornerRadius;
	this->textColor = textColor;
	this->graphColor = graphColor;
	this->bgColor = bgColor;
	this->graphType = graphType;
	this->Invalidate();
	this->font = font;
}

void UIElementGraph::Update()
{
	if (prevValuesChecksum == values.GetChecksum())
	{
		return;
	}
	// First draw bg rect
	UIPrimitives::RaisedPanel(tft, location.x1, location.y1, location.width, location.height, cornerRadius, bgColor, alpha);
	Rectangle textRect;
	if (itemLabel.size() > 0)
	{
		textRect = FontHelper::GetTextRect(tft, itemLabel, font, Point(0, 0));
		UIPrimitives::Text(tft, textColor, alpha, location.center().x - textRect.height / 2, location.y1 + 3 + textRect.height / 2, font, true, itemLabel);
	}

	Rectangle graphRect = Rectangle(location.x1 + 3, location.y1 + 5 + textRect.height, location.x2 - 3, location.y2 - 3);

	uint16_t lineWidth = (graphRect.width-25) / values.GetSize()-1;
	float degPerPixel = (graphRect.height - 10) / (values.GetMax() - values.GetMin());
	for (int i = 0; i < values.GetSize(); i++)
	{	
		uint16_t xStart = graphRect.x1 + (lineWidth*i)+20;		
		float tempDif = values.GetValues()[i] - values.GetMin();		
		uint16_t startY = graphRect.y2 - 5 - (degPerPixel*tempDif);
		if (graphType == eGraphType::BarGraph)
		{
			Rectangle bar(xStart + 2, startY, xStart + lineWidth - 2, graphRect.y2 - 5);
			UIPrimitives::RaisedPanel(tft, bar.x1, bar.y1, bar.width, bar.height, 0, graphColor, alpha);
		}
		else
		{
			if (i > 0)
			{
				// Draw the line
				tempDif = values.GetValues()[i - 1] - values.GetMin();
				uint16_t startYPrev = graphRect.y2 - 5 - (degPerPixel*tempDif);
				uint16_t xStartPrev = graphRect.x1 + (lineWidth*(i - 1)) + 20;
				Logger::Trace("Line (%d,%d):(%d,%d)", xStartPrev, startYPrev, xStart, startY);
				UIPrimitives::DrawLine(tft, 1, Point(xStartPrev, startYPrev), Point(xStart, startY), graphColor, alpha);
			}
			// Draw the point
			UIPrimitives::DrawPoint(tft, 3, Point(xStart, startY), graphColor, alpha);
			
		}
	}

	// Draw Min/Max
	std::stringstream ss, ss1;
	ss << values.GetMin();
	std::string minVal = ss.str();
	ss1 << values.GetMax();
	std::string maxVal = ss1.str();	
	
	Logger::Trace("MinVal: \"%s\", MaxVal: \"%s\"", minVal.c_str(), maxVal.c_str());
	UIPrimitives::Text(tft, textColor, alpha, graphRect.x1 + 20, graphRect.y1 + 10, eUITextFont::AntiAliasFont26, false, maxVal, UIPrimitives::Center);
	UIPrimitives::Text(tft, textColor, alpha, graphRect.x1 + 20, graphRect.y2 - 20, eUITextFont::AntiAliasFont26, false, minVal, UIPrimitives::Center);

	prevValuesChecksum = values.GetChecksum();
	this->updatePending = false;
}
#endif