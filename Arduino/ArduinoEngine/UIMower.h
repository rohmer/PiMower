#pragma once
#include <map>
#include <vector>
#include "Utility/Color.h"
#include "UIElements/UIElement.h"
#include <SPI.h>
#include "MowerIcon.h"


class UIMower : public UIElement
{
public:
	UIMower(DriverBase &tft, Rectangle location, uint16_t frontSonorIn, uint16_t leftSonorIn,
		uint16_t rightSonorIn, uint16_t backSonorIn, uint8_t leftWheel, uint8_t rightWheel, bool blade,
		tColor mowerColor, tColor bladeEngagedColor, tColor bladeOffColor, tColor wheelForwardColor,
		tColor wheelBackColor, tColor wheelIdleColor, tColor bgColor, 
		bool frontBumperActivated, bool backBumperActivated, long degreesLat, long degreesLon,
		uint32_t minutesLat, uint32_t minutesLon, std::string cardnialLat, std::string cardinalLon,
		uint8_t numGPSSats);

	sTouchResponse ProcessTouch(Point touchPoint)
	{
		return sTouchResponse(this->elementID, eTouchResponse::NoOp);
	};
	void Update() override;
	void SetLeftWheel(uint8_t val)
	{
		if (val > 2)
			val = 2;
		leftWheel = val;
	}

	void SetRightWheel(uint8_t val)
	{
		if (val > 2)
			val = 2;
		rightWheel = val;
	}

	bool SetBlade(bool val)
	{
		blade = val;
	}
	void SetFrontSonor(uint16_t val)
	{
		frontSonorIn = val;
	}
	void SetBackSonor(uint16_t val)
	{
		backSonorIn= val;
	}
	void SetLeftSonor(uint16_t val)
	{
		leftSonorIn = val;
	}
	void SetRightSonor(uint16_t val)
	{
		rightSonorIn = val;
	}
private:
	uint8_t pctCharged,leftWheel,rightWheel;
	bool blade;
	tColor borderColor, pctTextColor, bgColor;
	std::vector<tColor> barColors;
	eUITextFont pctFont;
	uint16_t frontSonorIn, backSonorIn, leftSonorIn, rightSonorIn;
	bool rightAlignment, showPct;
	bool frontBumperActivated, backBumperActivated;
	tColor mowerColor, bladeEngagedColor, bladeOffColor, wheelForwardColor, wheelBackColor, wheelIdleColor;
	long degreesLat, degreesLon;
	uint16_t minutesLat, minutesLon;
	uint8_t numGPSSats;
	std::string cardnialLat;
	std::string cardinalLon;
	std::string nextSchedule;
};
