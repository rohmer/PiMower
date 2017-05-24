#include "WindowManager.h"

WindowManager *WindowManager::s_instance;

WindowManager::WindowManager(const uint8_t cs, const uint8_t rst, const uint8_t mosi = 11,
	const uint8_t sclk = 13, const uint8_t miso = 12, eLCDSizes lcdSize = eLCDSizes::lcd800x480) 
{
	if (lcdSize == eLCDSizes::lcd800x480)
		tft.Init(800, 480, cs, rst);
	else
		tft.Init(480, 282, cs, rst);

 
	{
		wmCanvas = new UIWindow(tft, Rectangle(0, 0, tft.width(), tft.height()), eUITextFont::None, "", false, false, false, false, false,
			0, 0, 0, 0, 0);		
	}
#ifdef DEBUG
	Logger::Trace("WindowManager Initialized, wmCanvas: %d", wmCanvas->getElementID());
#endif
}

void WindowManager::Update()
{
	Logger::Trace("WindowManager::Update()");
	processTouch();
	wmCanvas->Update();
}

void WindowManager::RegisterElement(UIElement *element)
{
	Logger::Trace("Entering RegisterElement");
	elementMap.insert(std::make_pair(element->getElementID(), element));
	elementOrder.push_back(element->getElementID());
	WindowManager::wmCanvas->AddChildElement(element);	
}

void WindowManager::DeleteElement(unsigned long elementID)
{
	if (elementID == wmCanvas->getElementID())
	{
		Logger::Crit("Request made to delete wmCanvas, which cannot happen");
		return;
	}
	
	std::map<unsigned long, UIElement*>::iterator it = elementMap.find(elementID);
	if (it == elementMap.end())
	{
		Logger::Crit("Request made to delete element not in element map, ID: %d", elementID);
	}
	UIElement *element = it->second;
	// Walk the list of all elements, and see which need to be updated using
	// Rectangle occludes and force an update.
	
	updateOccluded(elementID);

	// Now delete the element and delete it from the map
	delete(it->second);
	elementMap.erase(it->first);

	// Erase it from the Z stack
	std::vector<unsigned long>::iterator eIt = std::find(elementOrder.begin(), elementOrder.end(), it->first);
	if (eIt == elementOrder.end())
	{
		Logger::Crit("Expected to find element in Z Stack, and it wasn't.  Element ID: %d", it->first);
	}
	else
	{
		elementOrder.erase(eIt);
	}

	// Complete! :)
}

void WindowManager::updateOccluded(unsigned long id)
{
	std::map<unsigned long, UIElement*>::iterator it = elementMap.find(id);
	if (it == elementMap.end())
	{
		Logger::Crit("Attempt made to update non-existent element: %d", id);
		return;
	}

	std::vector<unsigned long> neededUpdate;
	for (int i = 0; i < wmCanvas->GetChildElements().size();i++)
	{
		if (it->second->GetLocation().occludes(wmCanvas->GetChildElements()[i]->GetLocation()))
			neededUpdate.push_back(wmCanvas->GetChildElements()[i]->getElementID());
	}

	std::vector<unsigned long>::iterator eIt;
	// Now update them based on the stack 
	for (int i = 0; i < elementMap.size(); i++)
	{
		eIt = std::find(neededUpdate.begin(), neededUpdate.end(), elementMap[i]->getElementID());
		if (eIt != neededUpdate.end())
			elementMap[i]->Update();
	}
}

void WindowManager::MoveControlToFront(unsigned long controlID)
{
	std::vector<unsigned long>::iterator it = std::find(elementOrder.begin(), elementOrder.end(), controlID);
	if (it == elementOrder.end())
	{
		Logger::Warn("Element ID: %d is not in the Z Stack", controlID);
		return;
	}
	elementOrder.erase(it);
	elementOrder.push_back(controlID);
	updateOccluded(controlID);
}

void WindowManager::processTouch()
{
	if (!tft.touched())
	{
		Logger::Trace("TFT not touched");
		return;
	}

	uint16_t x, y;
	tft.touchRead(&x, &y);
#ifdef DEBUG
	Logger::Trace("TFT touched (%d,%d)", x, y);
#endif
	Point p(x, y);
	for (int i = elementOrder.size(); i >= 0; i++)
	{
		std::map<unsigned long, UIElement *>::iterator emIt = elementMap.find(elementOrder[i]);
		if (emIt != elementMap.end())
			if (emIt->second->GetLocation().contains(p))
			{
				if (emIt->second->isEnabled())
				{					
					// Set the touch event so something can query it
					lastTouchEvent = emIt->second->ProcessTouch(p);
				}
				else
				{
					lastTouchEvent = sTouchResponse(emIt->first, eTouchResponse::ControlTouchedInactive);
				}
				return;
			}
	}
	lastTouchEvent = sTouchResponse(wmCanvas->getElementID(),NoOp);
}

WindowManager::~WindowManager()
{
	std::map<unsigned long, UIElement *>::iterator i;
	for (i = elementMap.begin(); i != elementMap.end(); i++)
		delete(i->second);
}