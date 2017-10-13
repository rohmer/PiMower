#include "MainPage.h"

MainPage::MainPage(DriverBase &tft, UIData *data) :
	PageBase(tft, data, "MAIN"),
	itemsGenerated(false)
{			
	generatePageItems();
	wm = WindowManager::instance();
}

void MainPage::Update()
{
	if (millis() > nextRefresh)
	{
		wm->Update();
		nextRefresh = millis() + minRefresh;
	}	

	if (wm->GetLastTouchEvent().touchReponse == eTouchResponse::ControlTouched)
	{
		// Deal with this pages controls
	}
}

void MainPage::generatePageItems()
{
	// An active button is essentially a button with children that are updated regularly
	// Lets create all our buttons
	navButton = new UIButton(tft, Rectangle(5, 5, 150, 150), "", eUITextFont::None, 
		Color::Black, 1, Color::Purple, 0, false,false, "NavButton");
	battButton = new UIButton(tft, Rectangle(5, 155, 150, 300), "", eUITextFont::None,
		Color::Black, 1, Color::Gray, 0, false, false, "BatButton");
	statusButton = new UIButton(tft, Rectangle(155, 5, 645, 300), "", eUITextFont::None,
		Color::Black, 1, Color::Blue, 0, false, false, "StatusButton");
	stopText = new UIStopButton(tft, Rectangle(0, 305, 800, 100));	
	this->AddChildElement(stopText);
	// Put a compass on Nav Button	
	this->AddChildElement(statusButton);
	compass = new UICompass(tft, Rectangle(15, 15, 125, 140), data->heading, Color::Yellow, Color::Red, eUITextFont::AntiAliasFont27, true, Color::White);
	this->AddChildElement(battButton);
	std::vector<tColor> battColors;
	battColors.push_back(Color::Red);
	battColors.push_back(Color::OrangeRed);
	battColors.push_back(Color::Orange);
	battColors.push_back(Color::Yellow);
	battColors.push_back(Color::GreenYellow);
	battColors.push_back(Color::Green);	
	mowerIcon = new UIMower(tft, statusButton->GetLocation(), data->frontSonorIn, data->leftSonorIn, data->rightSonorIn, data->backSonorIn,
		data->leftWheel, data->rightWheel, data->blade, Color::White, Color::Red, Color::Green, Color::Green,
		Color::OrangeRed, Color::Gray, Color::Blue, data->frontBumper, data->backBumper, data->degreesLat,
		data->degreesLon, data->minutesLat, data->minutesLon, data->cardinalLat, data->cardinalLon, data->gpsSatNum);
	statusButton->AddChildElement(mowerIcon);

	batteryIcon = new UIBattery(tft, Rectangle(15, 165, 125, 290), data->battPct, battColors, true);
	battButton->AddChildElement(batteryIcon);

	navButton->AddChildElement(compass);
	this->AddChildElement(navButton);	
}

sTouchResponse MainPage::ProcessTouch(Point touchPoint)
{
	//deal with this pages touch items
}