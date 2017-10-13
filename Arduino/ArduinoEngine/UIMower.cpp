#include "UIMower.h"
UIMower::UIMower(DriverBase &tft, Rectangle location, uint16_t frontSonorIn, uint16_t leftSonorIn,
	uint16_t rightSonorIn, uint16_t backSonorIn, uint8_t leftWheel, uint8_t rightWheel, bool blade,
	tColor mowerColor, tColor bladeEngagedColor, tColor bladeOffColor, tColor wheelForwardColor,
	tColor wheelBackColor, tColor wheelIdleColor, tColor bgColor,
	bool frontBumperActivated, bool backBumperActivated, long degreesLat, long degreesLon,
	uint32_t minutesLat, uint32_t minutesLon, std::string cardnialLat, std::string cardinalLon, 
	uint8_t numGPSSats) :
	UIElement(tft, location, "MowerIcon", eElementType::NotInteractive),
	rightSonorIn(rightSonorIn), backSonorIn(backSonorIn), leftSonorIn(leftSonorIn), frontSonorIn(frontSonorIn),
	leftWheel(leftWheel), rightWheel(rightWheel), blade(blade), mowerColor(mowerColor),
	bladeEngagedColor(bladeEngagedColor), bladeOffColor(bladeOffColor), wheelForwardColor(wheelForwardColor),
	wheelBackColor(wheelBackColor), wheelIdleColor(wheelIdleColor), bgColor(bgColor), frontBumperActivated(frontBumperActivated),
	backBumperActivated(backBumperActivated), degreesLat(degreesLat), degreesLon(degreesLon),
	minutesLat(minutesLat),minutesLon(minutesLon),cardinalLon(cardinalLon),cardnialLat(cardnialLat),
	nextSchedule(nextSchedule), numGPSSats(numGPSSats)
{
}

void UIMower::Update()
{
	MowerIcon::Draw(tft, location, frontSonorIn, leftSonorIn,
		rightSonorIn, backSonorIn, leftWheel, rightWheel, blade, mowerColor,
		bladeEngagedColor, bladeOffColor, wheelForwardColor, wheelBackColor,
		wheelIdleColor, bgColor,frontBumperActivated,backBumperActivated,degreesLat,degreesLon,
		minutesLat,minutesLon,cardnialLat,cardinalLon,nextSchedule,numGPSSats);
}