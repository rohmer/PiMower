#include "MowerStats.h"

void MowerStats::Draw(DriverBase &tft,std::string nextSchedule, int degreesLat, int degreesLon, uint32_t minutesLat, uint32_t minutesLon,
	std::string cardnialLat, std::string cardinalLon, uint8_t numGPSSat, Point location)
{
	// First draw location
	char latLon[128];
	std::stringstream itos;
	itos << minutesLat;
	std::string mLat = itos.str();
	std::string minutes,seconds;
	if (mLat.length() > 2)
	{
		minutes = mLat.substr(0, 2);
		seconds = mLat.substr(2);
	}
	else
	{
		minutes = mLat;
		seconds = "0";
	}

	sprintf(latLon, "Lat: %d.%s.%s %s", degreesLat, minutes.c_str(), seconds.c_str(),cardnialLat.c_str());
	std::string latStr(latLon);
	UIPrimitives::Text(tft, Color::AntiqueWhite, 255, location.x+25, location.y+10, 
		eUITextFont::AntiAliasFont28, false, latStr,UIPrimitives::Left);
	std::stringstream ltos;
	ltos << minutesLon;
	std::string mLon = ltos.str();
	if (mLon.length())
	{
		minutes = mLon.substr(0, 2);
		seconds = mLon.substr(2);
	}
	else
	{
		minutes = mLat;
		seconds = "0";
	}
	sprintf(latLon, "Lon: %d.%s.%s %s", degreesLon, minutes.c_str(), seconds.c_str(), cardinalLon.c_str());
	std::string lonStr(latLon);
	UIPrimitives::Text(tft, Color::AntiqueWhite, 255, location.x+25, location.y+40, 
		eUITextFont::AntiAliasFont28, false, lonStr,UIPrimitives::Left);
	
	tColor textColor = Color::LawnGreen;
	if (numGPSSat < 3)
		textColor = Color::DarkRed;
	if (numGPSSat == 3)
		textColor = Color::Yellow;
	char gpsText[32];
	sprintf(gpsText, "GPS Satalites: %d", numGPSSat);
	std::string gpsStr(gpsText);
	UIPrimitives::Text(tft, textColor, 255, location.x + 25, location.y + 70,
		eUITextFont::AntiAliasFont28, false, gpsStr, UIPrimitives::Left);
}