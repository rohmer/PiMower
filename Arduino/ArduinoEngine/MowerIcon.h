#pragma once
#include <vector>
#include "Options.h"
#include "Utility/Rectangle.h"
#include "Driver/DriverBase.h"
#include "Utility/Color.h"
#include "MowerStats.h"

#ifdef FT8XX
#include "UIElements/FT8XX/UIPrimitives.h"
#endif
#ifdef RA8875
#include "UIElements/RA8875/UIPrimitives.h"
#endif

class MowerIcon
{
public:
	static Rectangle Draw(DriverBase &tft, Rectangle location, uint16_t frontSonorIn, uint16_t leftSonorIn,
		uint16_t rightSonorIn, uint16_t backSonorIn, uint8_t leftWheel, uint8_t rightWheel, bool blade,
		tColor mowerColor, tColor bladeEngagedColor, tColor bladeOffColor, tColor wheelForwardColor,
		tColor wheelBackColor, tColor wheelIdleColor, tColor bgColor, bool frontBumperActivated,
		bool backBumperActivated, int degreesLat, int degreesLon,
		uint32_t minutesLat, uint32_t minutesLon, std::string cardnialLat, std::string cardinalLon,
		std::string nextSchedule, uint8_t numGPSSats);
private:
	static void sonor(DriverBase &tft, Point point, uint8_t distance, tColor bgColor);
};
