#include "MowerIcon.h"

Rectangle MowerIcon::Draw(DriverBase &tft, Rectangle location, uint16_t frontSonorIn, uint16_t leftSonorIn,
	uint16_t rightSonorIn, uint16_t backSonorIn, uint8_t leftWheel, uint8_t rightWheel, bool blade,
	tColor mowerColor, tColor bladeEngagedColor, tColor bladeOffColor, tColor wheelForwardColor,
	tColor wheelBackColor, tColor wheelIdleColor, tColor bgColor, bool frontBumperActivated,
	bool backBumperActivated, int degreesLat, int degreesLon,
	uint32_t minutesLat, uint32_t minutesLon, std::string cardnialLat, std::string cardinalLon,
	std::string nextSchedule, uint8_t numGPSSats)
{
	uint8_t hTenths = location.height / 10;
	uint8_t wTenths = location.width / 10;

	bool wider = true;
	if (location.height > location.width)
		wider = false;
	
	uint8_t radius;
	if (wider)
	{
		radius = hTenths * 2.5;
	}
	else
	{
		radius = wTenths * 2.5;
	}
	// Mower is essentially a filled circle and filled square
	uint16_t centerX = location.center().x + wTenths *1.2;
	tft.fillCircle(centerX+ wTenths, location.center().y, radius, mowerColor);
	tft.fillRoundRect(centerX - radius, location.center().y - radius, 
		radius*2+6, radius*2+6, 6, mowerColor);

	// Draw Bumper
	tColor bumperColor = Color::LightGreen;
	if (frontBumperActivated)
		bumperColor = Color::Red;
	// Bumper is two boxes in front of mower
	tft.fillRoundRect(centerX + wTenths * 2, location.center().y - radius-10, 15, 15, 3, bumperColor);
	tft.fillRoundRect(centerX + wTenths * 2, location.center().y + radius - 10, 15, 15, 3, bumperColor);
	bumperColor = Color::LightGreen;
	if (backBumperActivated)
		bumperColor = Color::Red;
	tft.fillRoundRect(centerX-wTenths*2, location.center().y - radius, 15, 15, 3, bumperColor);
	tft.fillRoundRect(centerX - wTenths * 2, location.center().y + radius - 10, 15, 15, 3, bumperColor);

	// Draw a drive shaft
	tft.fillRect(centerX - (radius*.7), location.center().y - radius - 7, 5, radius * 2 + 20, mowerColor);

	tColor leftDriveColor=wheelIdleColor, rightDriveColor=wheelIdleColor;
	if (leftWheel == 1)
	{
		leftDriveColor = wheelForwardColor;
	}
	if (leftWheel = 2)
	{
		leftDriveColor = wheelBackColor;
	}
	
	if (rightWheel== 1)
	{
		rightDriveColor= wheelForwardColor;
	}
	if (rightWheel = 2)
	{
		rightDriveColor = wheelBackColor;
	}

	// Draw the wheels
	tft.fillRoundRect(centerX - (radius), location.center().y - radius - 18, wTenths, 6, 3, leftDriveColor);
	tft.fillRoundRect(centerX - (radius), location.center().y + radius + 18, wTenths, 6, 3, rightDriveColor);
	tColor bladeColor;
	if (blade)
		bladeColor = bladeEngagedColor;
	else
		bladeColor = bladeOffColor;
	tft.fillCircle(centerX + wTenths, location.center().y, radius - 5, bladeColor);

	tColor bColor;
	tColor fColor;
	// Now draw sonor icons
	sonor(tft, Point(centerX +10, location.center().y - radius - 45), backSonorIn,bgColor);
	sonor(tft, Point(centerX + 10, location.center().y + radius + 45), frontSonorIn, bgColor);
	sonor(tft, Point(centerX - radius - 45, location.center().y), leftSonorIn, bgColor);
	sonor(tft, Point(centerX + radius + 85, location.center().y), rightSonorIn, bgColor);

	MowerStats::Draw(tft, nextSchedule, degreesLat, degreesLon, 
		minutesLat, minutesLon, cardnialLat, cardinalLon, numGPSSats,
		Point(location.x1, location.y1 + 5));

}

void MowerIcon::sonor(DriverBase &tft, Point point, uint8_t distance, tColor color)
{
	std::string d = "999";
	uint8_t textWidth = FontHelper::GetTextRect(tft, d, eUITextFont::AntiAliasFont27, point).width;

	tColor bColor, fColor;
	if (distance  < 140 && distance  >60)
	{
		bColor = Color::Yellow;
		fColor = Color::DarkBlue;
	}
	else
	{
		if (distance <= 60)
		{
			bColor = Color::DarkRed;
			fColor = Color::White;
		}
	}
	if (distance  > 140)
	{
		bColor = Color::Green;
		fColor = Color::White;
	}


	UIPrimitives::CircleFlat(tft, bColor, 255, point.x, point.y, textWidth/2+6);
	UIPrimitives::CircleFlat(tft, color, 255, point.x, point.y, textWidth/2+4);
	UIPrimitives::CircleFlat(tft, bColor, 255, point.x, point.y, textWidth/2+2);
	char buf[8];
	sprintf(buf, "%d", distance);
	std::string pString(buf);
	UIPrimitives::Text(tft, fColor, 255, point.x, point.y-10, eUITextFont::AntiAliasFont27, false, pString.c_str());
}