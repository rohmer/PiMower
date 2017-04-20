#include "IdlePage.h"
#include "BatteryIcons.h"

IdlePage::IdlePage()
	: UIElement(Point(0, 0), false, false)
{
	nextUpdate = time(0);
	elementArea = Rectangle(0, 0, 240, 320);
}

void IdlePage::update(DigoleLCD *lcd, RobotLib *robotLib)
{
	// Defer update, we should only update every minute
	if (time(0) < nextUpdate)
		return;
	if (batMon == NULL)
		batMon = new BQ34Z100G1(robotLib);
	time_t now = time(0);
	nextUpdate = now + 60;
	lcd->setRotation(DigoleLCD::eDrawRot::rot90);

	// TODO: Actually check the battery for percentage
	int pct = 85;

	lcd->setColor(DigoleLCD::BLACK);
	lcd->drawBoxFill(174, 4, 62, 70);
	if (pct == 100)
		lcd->drawBitmap256(175, 5, 60, 34, battery100pct);
	else
		if (pct >= 85)
		lcd->drawBitmap256(175, 5, 60, 34, battery85pct);
	else
		if (pct >= 60)
		lcd->drawBitmap256(175, 5, 60, 34, battery60pct);
	else
		if (pct >= 45)
		lcd->drawBitmap256(175, 5, 60, 34, battery45pct);
	else
		if (pct >= 30)
		lcd->drawBitmap256(175, 5, 60, 34, battery30pct);
	else
		if (pct >= 15)
		lcd->drawBitmap256(175, 5, 60, 34, battery15pct);
	else
		lcd->drawBitmap256(175, 5, 60, 34, battery0pct);
	lcd->setColor(DigoleLCD::WHITE);
	std::stringstream pctStr;
	pctStr << pct << "%";
	lcd->setFont(UIFont::u8g_font_6x10);
	lcd->printxy_abs(200, 97, pctStr.str());

	std::stringstream dtStr;

	tm *ltm = localtime(&now);
	int year = 1900 + ltm->tm_year;
	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;
	int hour = 1 + ltm->tm_hour;
	int min = 1 + ltm->tm_min;
	int sec = 1 + ltm->tm_sec;
	dtStr << hour << ":" << min << ":" << sec << " " << month << "/" << day << "/" << year;
	lcd->setFont(UIFont::u8g_font_osr35n);
	lcd->printxy_abs(10, 125, dtStr.str());
}

int IdlePage::processTouch(Point pt)
{
	return 1;
}