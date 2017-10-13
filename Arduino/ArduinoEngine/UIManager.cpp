#include "UIManager.h"

/// <summary>
/// Creates the window Manager and main window, and displays it
/// </summary>
UIManager::UIManager() 
{
	windowManager = WindowManager::instance();	
	uidata = new UIData();
	changeDisplayedPage("MAIN");
}

/// <summary>
/// Destructor for UIManager, deleting all of the pages created
/// </summary>
UIManager::~UIManager()
{
	std::map<std::string, PageBase*>::iterator it;
	for (it = pages.begin(); it != pages.end(); it++)
	{
		delete(it->second);
	}
}

/// <summary>
/// Handles displaying what is necessary to display, as well as
/// all of the touch input
/// </summary>
void UIManager::Update()
{	
	
	if (pages.find(currentPage) == pages.end())
	{
		// This shouldn't ever happen, how did we get a 
		// touch event on a page that doesn't exist?
		Serial.println("*** CRITICAL ERROR ***");
		Serial.print("Attempted to access non-existent page: ");
		Serial.println(currentPage.c_str());
		return;
	}
	pages.find(currentPage)->second->Update();
	pages.find(currentPage)->second->SetUIData(uidata);

	sTouchResponse tr = windowManager->GetLastTouchEvent();
	if (tr.touchReponse == eTouchResponse::BringToFront)
		windowManager->MoveControlToFront(tr.controlID);
	if (tr.touchReponse == eTouchResponse::CloseControl)
		windowManager->DeleteElement(tr.controlID);
	// A page was touched, did it click something that requires us to display
	// a new page?
	if (tr.touchReponse == eTouchResponse::ControlTouched)
	{
		std::string ctrlPage = pages.find(currentPage)->second->GetNewPage();
		if(ctrlPage!=currentPage)
		{
			currentPage = ctrlPage;
			changeDisplayedPage(ctrlPage);
		}
	}
}

/// <summary>
/// Creates a new page (If needed) and changes the WM to display it
/// If new page is developed, it has to be put here
/// </summary>
/// <param name="page"></param>
void UIManager::changeDisplayedPage(std::string pageName)
{
	Logger::Trace("Adding Page: %s", pageName.c_str());
	if (pageName == "MAIN")
	{
		if (pages.find("MAIN") == pages.end())
		{
			// Page hasn't been added yet need to add
			// Temporary for testing, eventually we will actually add the data
			uidata->battPct = 75;
			uidata->altitude = 106.63;
			uidata->backBumper = true;
			uidata->frontBumper = false;
			uidata->backSonorIn = 150;
			uidata->frontSonorIn = 150;
			uidata->leftSonorIn = 12;
			uidata->rightSonorIn = 150;
			uidata->cardinalLat = 'N';
			uidata->cardinalLon = 'W';
			uidata->degreesLat = 28;
			uidata->degreesLon = 81;
			uidata->minutesLat = 5383355;
			uidata->minutesLon = 3792365;
			uidata->blade = true;
			uidata->gpsSatNum = 5;
			uidata->heading = 270;
			uidata->leftWheel = 1;
			uidata->rightWheel = 1;			
			MainPage *page = new MainPage(*windowManager->GetDriver(), uidata);			
			pages.insert(std::make_pair<std::string, PageBase*>("MAIN", page));
		}
	}
	if (pages.find(pageName) == pages.end())
	{
		// This is a compile time error, either the name is wrong
		// or we haven't put the class in
		Serial.print("Error in UIManager, page definition not found for page '");
		Serial.print(pageName.c_str());
		Serial.println("'");
		return;
	}
	windowManager->ClearElements();
	std::map<std::string, PageBase *>::iterator p = pages.find(pageName);
	Logger::Trace("Page Name: %s", p->first.c_str());
	Logger::Trace("Number of child elements: %d", pages.find(pageName)->second->GetChildElements().size());
	std::vector<UIElement *> cElements = p->second->GetChildElements();
	for (int i = 0; i < p->second->GetChildElements().size(); i++)
	{
		windowManager->RegisterElement(p->second->GetChildElements()[i]);
	}
	currentPage = pageName;

}