#include "FontHelper.h"
#ifdef RA8875
void FontHelper::setLCDFont(Adafruit_RA8875 &lcd, eUITextFont font)
{
	switch (font)
	{
#if defined(useAileronBlack9) || defined(useAllFonts)
	case(AileronBlack9):
		lcd.setFont(&Aileron_Black9pt7b);
		break;
#endif
#if defined(useAileronBlack12) || defined(useAllFonts)
	case(AileronBlack12):
		lcd.setFont(&Aileron_Black12pt7b);
		break;
#endif
#if defined(useAileronBlack18) || defined(useAllFonts)
	case(AileronBlack18):
		lcd.setFont(&Aileron_Black18pt7b);
		break;
#endif
#if defined(useAileronBlack24) || defined(useAllFonts)
	case(AileronBlack24):
		lcd.setFont(&Aileron_Black24pt7b);
		break;
#endif
#if defined(useAileronBlack36) || defined(useAllFonts)
	case(AileronBlack36):
		lcd.setFont(&Aileron_Black36pt7b);
		break;
#endif
#if defined(useAileronBlackItalic9) || defined(useAllFonts)
	case(AileronBlackItalic9):
		lcd.setFont(&Aileron_BlackItalic9pt7b);
		break;
#endif
#if defined(useAileronBlackItalic12) || defined(useAllFonts)
	case(AileronBlackItalic12):
		lcd.setFont(&Aileron_BlackItalic12pt7b);
		break;
#endif
#if defined(useAileronBlackItalic18) || defined(useAllFonts)
	case(AileronBlackItalic18):
		lcd.setFont(&Aileron_BlackItalic18pt7b);
		break;
#endif
#if defined(useAileronBlackItalic24) || defined(useAllFonts)
	case(AileronBlackItalic24):
		lcd.setFont(&Aileron_BlackItalic24pt7b);
		break;
#endif
#if defined(useAileronBlackItalic36) || defined(useAllFonts)
	case(AileronBlackItalic36):
		lcd.setFont(&Aileron_BlackItalic36pt7b);
		break;
#endif
#if defined(useAileronBold9) || defined(useAllFonts)
	case(AileronBold9):
		lcd.setFont(&Aileron_Bold9pt7b);
		break;
#endif
#if defined(useAileronBold12) || defined(useAllFonts)
	case(AileronBold12):
		lcd.setFont(&Aileron_Bold12pt7b);
		break;
#endif
#if defined(useAileronBold18) || defined(useAllFonts)
	case(AileronBold18):
		lcd.setFont(&Aileron_Bold18pt7b);
		break;
#endif
#if defined(useAileronBold24) || defined(useAllFonts)
	case(AileronBold24):
		lcd.setFont(&Aileron_Bold24pt7b);
		break;
#endif
#if defined(useAileronBold36) || defined(useAllFonts)
	case(AileronBold36):
		lcd.setFont(&Aileron_Bold36pt7b);
		break;
#endif
#if defined(useAileronBoldItalic9) || defined(useAllFonts)
	case(AileronBoldItalic9):
		lcd.setFont(&Aileron_BoldItalic9pt7b);
		break;
#endif
#if defined(useAileronBoldItalic12) || defined(useAllFonts)
	case(AileronBoldItalic12):
		lcd.setFont(&Aileron_BoldItalic12pt7b);
		break;
#endif
#if defined(useAileronBoldItalic18) || defined(useAllFonts)
	case(AileronBoldItalic18):
		lcd.setFont(&Aileron_BoldItalic18pt7b);
		break;
#endif
#if defined(useAileronBoldItalic24) || defined(useAllFonts)
	case(AileronBoldItalic24):
		lcd.setFont(&Aileron_BoldItalic24pt7b);
		break;
#endif
#if defined(useAileronBoldItalic36) || defined(useAllFonts)
	case(AileronBoldItalic36):
		lcd.setFont(&Aileron_BoldItalic36pt7b);
		break;
#endif
#if defined(useAileronHeavy9) || defined(useAllFonts)
	case(AileronHeavy9):
		lcd.setFont(&Aileron_Heavy9pt7b);
		break;
#endif
#if defined(useAileronHeavy12) || defined(useAllFonts)
	case(AileronHeavy12):
		lcd.setFont(&Aileron_Heavy12pt7b);
		break;
#endif
#if defined(useAileronHeavy18) || defined(useAllFonts)
	case(AileronHeavy18):
		lcd.setFont(&Aileron_Heavy18pt7b);
		break;
#endif
#if defined(useAileronHeavy24) || defined(useAllFonts)
	case(AileronHeavy24):
		lcd.setFont(&Aileron_Heavy24pt7b);
		break;
#endif
#if defined(useAileronHeavy36) || defined(useAllFonts)
	case(AileronHeavy36):
		lcd.setFont(&Aileron_Heavy36pt7b);
		break;
#endif
#if defined(useAileronHeavyItalic9) || defined(useAllFonts)
	case(AileronHeavyItalic9):
		lcd.setFont(&Aileron_HeavyItalic9pt7b);
		break;
#endif
#if defined(useAileronHeavyItalic12) || defined(useAllFonts)
	case(AileronHeavyItalic12):
		lcd.setFont(&Aileron_HeavyItalic12pt7b);
		break;
#endif
#if defined(useAileronHeavyItalic18) || defined(useAllFonts)
	case(AileronHeavyItalic18):
		lcd.setFont(&Aileron_HeavyItalic18pt7b);
		break;
#endif
#if defined(useAileronHeavyItalic24) || defined(useAllFonts)
	case(AileronHeavyItalic24):
		lcd.setFont(&Aileron_HeavyItalic24pt7b);
		break;
#endif
#if defined(useAileronHeavyItalic36) || defined(useAllFonts)
	case(AileronHeavyItalic36):
		lcd.setFont(&Aileron_HeavyItalic36pt7b);
		break;
#endif
#if defined(useAileronLight9) || defined(useAllFonts)
	case(AileronLight9):
		lcd.setFont(&Aileron_Light9pt7b);
		break;
#endif
#if defined(useAileronLight12) || defined(useAllFonts)
	case(AileronLight12):
		lcd.setFont(&Aileron_Light12pt7b);
		break;
#endif
#if defined(useAileronLight18) || defined(useAllFonts)
	case(AileronLight18):
		lcd.setFont(&Aileron_Light18pt7b);
		break;
#endif
#if defined(useAileronLight24) || defined(useAllFonts)
	case(AileronLight24):
		lcd.setFont(&Aileron_Light24pt7b);
		break;
#endif
#if defined(useAileronLight36) || defined(useAllFonts)
	case(AileronLight36):
		lcd.setFont(&Aileron_Light36pt7b);
		break;
#endif
#if defined(useAileronRegular9) || defined(useAllFonts)
	case(AileronRegular9):
		lcd.setFont(&Aileron_Regular9pt7b);
		break;
#endif
#if defined(useAileronRegular12) || defined(useAllFonts)
	case(AileronRegular12):
		lcd.setFont(&Aileron_Regular12pt7b);
		break;
#endif
#if defined(useAileronRegular18) || defined(useAllFonts)
	case(AileronRegular18):
		lcd.setFont(&Aileron_Regular18pt7b);
		break;
#endif
#if defined(useAileronRegular24) || defined(useAllFonts)
	case(AileronRegular24):
		lcd.setFont(&Aileron_Regular24pt7b);
		break;
#endif
#if defined(useAileronRegular36) || defined(useAllFonts)
	case(AileronRegular36):
		lcd.setFont(&Aileron_Regular36pt7b);
		break;
#endif
#if defined(useAileronSemiBold9) || defined(useAllFonts)
	case(AileronSemiBold9):
		lcd.setFont(&Aileron_SemiBold9pt7b);
		break;
#endif
#if defined(useAileronSemiBold12) || defined(useAllFonts)
	case(AileronSemiBold12):
		lcd.setFont(&Aileron_SemiBold12pt7b);
		break;
#endif
#if defined(useAileronSemiBold18) || defined(useAllFonts)
	case(AileronSemiBold18):
		lcd.setFont(&Aileron_SemiBold18pt7b);
		break;
#endif
#if defined(useAileronSemiBold24) || defined(useAllFonts)
	case(AileronSemiBold24):
		lcd.setFont(&Aileron_SemiBold24pt7b);
		break;
#endif
#if defined(useAileronSemiBold36) || defined(useAllFonts)
	case(AileronSemiBold36):
		lcd.setFont(&Aileron_SemiBold36pt7b);
		break;
#endif
#if defined(useAileronSemiBoldItalic9) || defined(useAllFonts)
	case(AileronSemiBoldItalic9):
		lcd.setFont(&Aileron_SemiBoldItalic9pt7b);
		break;
#endif
#if defined(useAileronSemiBoldItalic12) || defined(useAllFonts)
	case(AileronSemiBoldItalic12):
		lcd.setFont(&Aileron_SemiBoldItalic12pt7b);
		break;
#endif
#if defined(useAileronSemiBoldItalic18) || defined(useAllFonts)
	case(AileronSemiBoldItalic18):
		lcd.setFont(&Aileron_SemiBoldItalic18pt7b);
		break;
#endif
#if defined(useAileronSemiBoldItalic24) || defined(useAllFonts)
	case(AileronSemiBoldItalic24):
		lcd.setFont(&Aileron_SemiBoldItalic24pt7b);
		break;
#endif
#if defined(useAileronSemiBoldItalic36) || defined(useAllFonts)
	case(AileronSemiBoldItalic36):
		lcd.setFont(&Aileron_SemiBoldItalic36pt7b);
		break;
#endif
#if defined(useAileronThin9) || defined(useAllFonts)
	case(AileronThin9):
		lcd.setFont(&Aileron_Thin9pt7b);
		break;
#endif
#if defined(useAileronThin12) || defined(useAllFonts)
	case(AileronThin12):
		lcd.setFont(&Aileron_Thin12pt7b);
		break;
#endif
#if defined(useAileronThin18) || defined(useAllFonts)
	case(AileronThin18):
		lcd.setFont(&Aileron_Thin18pt7b);
		break;
#endif
#if defined(useAileronThin24) || defined(useAllFonts)
	case(AileronThin24):
		lcd.setFont(&Aileron_Thin24pt7b);
		break;
#endif
#if defined(useAileronThin36) || defined(useAllFonts)
	case(AileronThin36):
		lcd.setFont(&Aileron_Thin36pt7b);
		break;
#endif
#if defined(useAileronThinItalic9) || defined(useAllFonts)
	case(AileronThinItalic9):
		lcd.setFont(&Aileron_ThinItalic9pt7b);
		break;
#endif
#if defined(useAileronThinItalic12) || defined(useAllFonts)
	case(AileronThinItalic12):
		lcd.setFont(&Aileron_ThinItalic12pt7b);
		break;
#endif
#if defined(useAileronThinItalic18) || defined(useAllFonts)
	case(AileronThinItalic18):
		lcd.setFont(&Aileron_ThinItalic18pt7b);
		break;
#endif
#if defined(useAileronThinItalic24) || defined(useAllFonts)
	case(AileronThinItalic24):
		lcd.setFont(&Aileron_ThinItalic24pt7b);
		break;
#endif
#if defined(useAileronThinItalic36) || defined(useAllFonts)
	case(AileronThinItalic36):
		lcd.setFont(&Aileron_ThinItalic36pt7b);
		break;
#endif
#if defined(useAileronUltraLight9) || defined(useAllFonts)
	case(AileronUltraLight9):
		lcd.setFont(&Aileron_UltraLight9pt7b);
		break;
#endif
#if defined(useAileronUltraLight12) || defined(useAllFonts)
	case(AileronUltraLight12):
		lcd.setFont(&Aileron_UltraLight12pt7b);
		break;
#endif
#if defined(useAileronUltraLight18) || defined(useAllFonts)
	case(AileronUltraLight18):
		lcd.setFont(&Aileron_UltraLight18pt7b);
		break;
#endif
#if defined(useAileronUltraLight24) || defined(useAllFonts)
	case(AileronUltraLight24):
		lcd.setFont(&Aileron_UltraLight24pt7b);
		break;
#endif
#if defined(useAileronUltraLight36) || defined(useAllFonts)
	case(AileronUltraLight36):
		lcd.setFont(&Aileron_UltraLight36pt7b);
		break;
#endif
#if defined(useAileronUltraLightItalic9) || defined(useAllFonts)
	case(AileronUltraLightItalic9):
		lcd.setFont(&Aileron_UltraLightItalic9pt7b);
		break;
#endif
#if defined(useAileronUltraLightItalic12) || defined(useAllFonts)
	case(AileronUltraLightItalic12):
		lcd.setFont(&Aileron_UltraLightItalic12pt7b);
		break;
#endif
#if defined(useAileronUltraLightItalic18) || defined(useAllFonts)
	case(AileronUltraLightItalic18):
		lcd.setFont(&Aileron_UltraLightItalic18pt7b);
		break;
#endif
#if defined(useAileronUltraLightItalic24) || defined(useAllFonts)
	case(AileronUltraLightItalic24):
		lcd.setFont(&Aileron_UltraLightItalic24pt7b);
		break;
#endif

#if defined(useAileronUltraLightItalic36) || defined(useAllFonts)
	case(AileronUltraLightItalic36):
		lcd.setFont(&Aileron_UltraLightItalic36pt7b);
		break;
#endif
#if defined(useCourierPrime9) || defined(useAllFonts)
	case(CourierPrime9):
		lcd.setFont(&Courier_Prime9pt7b);
		break;
#endif
#if defined(useCourierPrime12) || defined(useAllFonts)
	case(CourierPrime12):
		lcd.setFont(&Courier_Prime12pt7b);
		break;
#endif
#if defined(useCourierPrime18) || defined(useAllFonts)
	case(CourierPrime18):
		lcd.setFont(&Courier_Prime18pt7b);
		break;
#endif
#if defined(useCourierPrime24) || defined(useAllFonts)
	case(CourierPrime24):
		lcd.setFont(&Courier_Prime24pt7b);
		break;
#endif
#if defined(useCourierPrime36) || defined(useAllFonts)
	case(CourierPrime36):
		lcd.setFont(&Courier_Prime36pt7b);
		break;
#endif
#if defined(useCourierPrimeBold9) || defined(useAllFonts)
	case(CourierPrimeBold9):
		lcd.setFont(&Courier_Prime_Bold9pt7b);
		break;
#endif
#if defined(useCourierPrimeBold12) || defined(useAllFonts)
	case(CourierPrimeBold12):
		lcd.setFont(&Courier_Prime_Bold12pt7b);
		break;
#endif
#if defined(useCourierPrimeBold18) || defined(useAllFonts)
	case(CourierPrimeBold18):
		lcd.setFont(&Courier_Prime_Bold18pt7b);
		break;
#endif
#if defined(useCourierPrimeBold24) || defined(useAllFonts)
	case(CourierPrimeBold24):
		lcd.setFont(&Courier_Prime_Bold24pt7b);
		break;
#endif
#if defined(useCourierPrimeBold36) || defined(useAllFonts)
	case(CourierPrimeBold36):
		lcd.setFont(&Courier_Prime_Bold36pt7b);
		break;
#endif
#if defined(useCourierPrimeBoldItalic9) || defined(useAllFonts)
	case(CourierPrimeBoldItalic9):
		lcd.setFont(&Courier_Prime_Bold_Italic9pt7b);
		break;
#endif
#if defined(useCourierPrimeBoldItalic12) || defined(useAllFonts)
	case(CourierPrimeBoldItalic12):
		lcd.setFont(&Courier_Prime_Bold_Italic12pt7b);
		break;
#endif
#if defined(useCourierPrimeBoldItalic18) || defined(useAllFonts)
	case(CourierPrimeBoldItalic18):
		lcd.setFont(&Courier_Prime_Bold_Italic18pt7b);
		break;
#endif
#if defined(useCourierPrimeBoldItalic24) || defined(useAllFonts)
	case(CourierPrimeBoldItalic24):
		lcd.setFont(&Courier_Prime_Bold_Italic24pt7b);
		break;
#endif
#if defined(useCourierPrimeBoldItalic36) || defined(useAllFonts)
	case(CourierPrimeBoldItalic36):
		lcd.setFont(&Courier_Prime_Bold_Italic36pt7b);
		break;
#endif
#if defined(useCourierPrimeItalic9) || defined(useAllFonts)
	case(CourierPrimeItalic9):
		lcd.setFont(&Courier_Prime_Italic9pt7b);
		break;
#endif
#if defined(useCourierPrimeItalic12) || defined(useAllFonts)
	case(CourierPrimeItalic12):
		lcd.setFont(&Courier_Prime_Italic12pt7b);
		break;
#endif
#if defined(useCourierPrimeItalic18) || defined(useAllFonts)
	case(CourierPrimeItalic18):
		lcd.setFont(&Courier_Prime_Italic18pt7b);
		break;
#endif
#if defined(useCourierPrimeItalic24) || defined(useAllFonts)
	case(CourierPrimeItalic24):
		lcd.setFont(&Courier_Prime_Italic24pt7b);
		break;
#endif
#if defined(useCourierPrimeItalic36) || defined(useAllFonts)
	case(CourierPrimeItalic36):
		lcd.setFont(&Courier_Prime_Italic36pt7b);
		break;
#endif
#if defined(useCrimsonBold9) || defined(useAllFonts)
	case(CrimsonBold9):
		lcd.setFont(&Crimson_Bold9pt7b);
		break;
#endif
#if defined(useCrimsonBold12) || defined(useAllFonts)
	case(CrimsonBold12):
		lcd.setFont(&Crimson_Bold12pt7b);
		break;
#endif
#if defined(useCrimsonBold18) || defined(useAllFonts)
	case(CrimsonBold18):
		lcd.setFont(&Crimson_Bold18pt7b);
		break;
#endif
#if defined(useCrimsonBold24) || defined(useAllFonts)
	case(CrimsonBold24):
		lcd.setFont(&Crimson_Bold24pt7b);
		break;
#endif
#if defined(useCrimsonBold36) || defined(useAllFonts)
	case(CrimsonBold36):
		lcd.setFont(&Crimson_Bold36pt7b);
		break;
#endif
#if defined(useCrimsonBoldItalic9) || defined(useAllFonts)
	case(CrimsonBoldItalic9):
		lcd.setFont(&Crimson_BoldItalic9pt7b);
		break;
#endif
#if defined(useCrimsonBoldItalic12) || defined(useAllFonts)
	case(CrimsonBoldItalic12):
		lcd.setFont(&Crimson_BoldItalic12pt7b);
		break;
#endif
#if defined(useCrimsonBoldItalic18) || defined(useAllFonts)
	case(CrimsonBoldItalic18):
		lcd.setFont(&Crimson_BoldItalic18pt7b);
		break;
#endif
#if defined(useCrimsonBoldItalic24) || defined(useAllFonts)
	case(CrimsonBoldItalic24):
		lcd.setFont(&Crimson_BoldItalic24pt7b);
		break;
#endif
#if defined(useCrimsonBoldItalic36) || defined(useAllFonts)
	case(CrimsonBoldItalic36):
		lcd.setFont(&Crimson_BoldItalic36pt7b);
		break;
#endif
#if defined(useCrimsonRoman9) || defined(useAllFonts)
	case(CrimsonRoman9):
		lcd.setFont(&Crimson_Roman9pt7b);
		break;
#endif
#if defined(useCrimsonRoman12) || defined(useAllFonts)
	case(CrimsonRoman12):
		lcd.setFont(&Crimson_Roman12pt7b);
		break;
#endif
#if defined(useCrimsonRoman18) || defined(useAllFonts)
	case(CrimsonRoman18):
		lcd.setFont(&Crimson_Roman18pt7b);
		break;
#endif
#if defined(useCrimsonRoman24) || defined(useAllFonts)
	case(CrimsonRoman24):
		lcd.setFont(&Crimson_Roman24pt7b);
		break;
#endif
#if defined(useCrimsonRoman36) || defined(useAllFonts)
	case(CrimsonRoman36):
		lcd.setFont(&Crimson_Roman36pt7b);
		break;
#endif
#if defined(useCrimsonSemiBold9) || defined(useAllFonts)
	case(CrimsonSemiBold9):
		lcd.setFont(&Crimson_Semibold9pt7b);
		break;
#endif
#if defined(useCrimsonSemiBold12) || defined(useAllFonts)
	case(CrimsonSemiBold12):
		lcd.setFont(&Crimson_Semibold12pt7b);
		break;
#endif
#if defined(useCrimsonSemiBold18) || defined(useAllFonts)
	case(CrimsonSemiBold18):
		lcd.setFont(&Crimson_Semibold18pt7b);
		break;
#endif
#if defined(useCrimsonSemiBold24) || defined(useAllFonts)
	case(CrimsonSemiBold24):
		lcd.setFont(&Crimson_Semibold24pt7b);
		break;
#endif
#if defined(useCrimsonSemiBold36) || defined(useAllFonts)
	case(CrimsonSemiBold36):
		lcd.setFont(&Crimson_Semibold36pt7b);
		break;
#endif
#if defined(useCrimsonSemiBoldItalic9) || defined(useAllFonts)
	case(CrimsonSemiBoldItalic9):
		lcd.setFont(&Crimson_SemiboldItalic9pt7b);
		break;
#endif
#if defined(useCrimsonSemiBoldItalic12) || defined(useAllFonts)
	case(CrimsonSemiBoldItalic12):
		lcd.setFont(&Crimson_SemiboldItalic12pt7b);
		break;
#endif
#if defined(useCrimsonSemiBoldItalic18) || defined(useAllFonts)
	case(CrimsonSemiBoldItalic18):
		lcd.setFont(&Crimson_SemiboldItalic18pt7b);
		break;
#endif
#if defined(useCrimsonSemiBoldItalic24) || defined(useAllFonts)
	case(CrimsonSemiBoldItalic24):
		lcd.setFont(&Crimson_SemiboldItalic24pt7b);
		break;
#endif
#if defined(useCrimsonSemiBoldItalic36) || defined(useAllFonts)
	case(CrimsonSemiBoldItalic36):
		lcd.setFont(&Crimson_SemiboldItalic36pt7b);
		break;
#endif
	}
}

Rectangle FontHelper::GetTextRect(Adafruit_RA8875 &tft, std::string text, eUITextFont font, Point textLoc)
{
	int16_t x, y, x1, y1;
	uint16_t w, h;
	x = textLoc.x;
	y = textLoc.y;
#ifdef DEBUG
	Logger::Trace("x=%d, y=%d", x, y);
#endif
	char *cstr = new char[text.size() + 1];
	strcpy(cstr, text.c_str());
	tft.getTextBounds(cstr, x, y, &x1, &y1, &w, &h);
	delete[](cstr);
	return (Rectangle(x1, y1, x1 + w, y1 + h));
}
#endif

#ifdef FT8XX
Rectangle FontHelper::GetTextRect(DriverBase &lcd, std::string text, eUITextFont font, Point textLoc)
{
	Point *charRect;
	switch (font)
	{
#if defined(useAileronBlack9) || defined(useAllFonts)
	case(AileronBlack9):
		charRect = new Point(10, 11);
		break;
#endif
#if defined(useAileronBlack12) || defined(useAllFonts)
	case(AileronBlack12):
		charRect = new Point(13, 14);
		break;
#endif
#if defined(useAileronBlack18) || defined(useAllFonts)
	case(AileronBlack18):
		charRect = new Point(19, 22);
		break;
#endif
#if defined(useAileronBlack24) || defined(useAllFonts)
	case(AileronBlack24):
		charRect = new Point(25, 29);
		break;
#endif
#if defined(useAileronBlack36) || defined(useAllFonts)
	case(AileronBlack36):
		charRect = new Point(38, 43);
		break;
#endif
#if defined(useAileronBlackItalic9) || defined(useAllFonts)
	case(AileronBlackItalic9):
		charRect = new Point(10, 11);
		break;
#endif
#if defined(useAileronBlackItalic12) || defined(useAllFonts)
	case(AileronBlackItalic12):
		charRect = new Point(13, 14);
		break;
#endif
#if defined(useAileronBlackItalic18) || defined(useAllFonts)
	case(AileronBlackItalic18):
		charRect = new Point(19, 22);
		break;
#endif
#if defined(useAileronBlackItalic24) || defined(useAllFonts)
	case(AileronBlackItalic24):
		charRect = new Point(25, 29);
		break;
#endif
#if defined(useAileronBlackItalic36) || defined(useAllFonts)
	case(AileronBlackItalic36):
		charRect = new Point(37, 43);
		break;
#endif
#if defined(useAileronBoldItalic9) || defined(useAllFonts)
	case(AileronBoldItalic9):
		charRect = new Point(10, 11);
		break;
#endif
#if defined(useAileronBoldItalic12) || defined(useAllFonts)
	case(AileronBoldItalic12):
		charRect = new Point(12, 14);
		break;
#endif
#if defined(useAileronBoldItalic18) || defined(useAllFonts)
	case(AileronBoldItalic18):
		charRect = new Point(19, 22);
		break;
#endif
#if defined(useAileronBoldItalic24) || defined(useAllFonts)
	case(AileronBoldItalic24):
		charRect = new Point(25, 29);
		break;
#endif
#if defined(useAileronBoldItalic36) || defined(useAllFonts)
	case(AileronBoldItalic36):
		charRect = new Point(37, 43);
		break;
#endif
#if defined(useAileronHeavy9) || defined(useAllFonts)
	case(AileronHeavy9):
		charRect = new Point(10, 11);
		break;
#endif
#if defined(useAileronHeavy12) || defined(useAllFonts)
	case(AileronHeavy12):
		charRect = new Point(13, 14);
		break;
#endif
#if defined(useAileronHeavy18) || defined(useAllFonts)
	case(AileronHeavy18):
		charRect = new Point(19, 22);
		break;
#endif
#if defined(useAileronHeavy24) || defined(useAllFonts)
	case(AileronHeavy24):
		charRect = new Point(25, 29);
		break;
#endif
#if defined(useAileronHeavy36) || defined(useAllFonts)
	case(AileronHeavy36):
		charRect = new Point(37, 43);
		break;
#endif
#if defined(useAileronHeavyItalic9) || defined(useAllFonts)
	case(AileronHeavyItalic9):
		charRect = new Point(10, 11);
		break;
#endif
#if defined(useAileronHeavyItalic12) || defined(useAllFonts)
	case(AileronHeavyItalic12):
		charRect = new Point(13, 14);
		break;
#endif
#if defined(useAileronHeavyItalic18) || defined(useAllFonts)
	case(AileronHeavyItalic18):
		charRect = new Point(19, 22);
		break;
#endif
#if defined(useAileronHeavyItalic24) || defined(useAllFonts)
	case(AileronHeavyItalic24):
		charRect = new Point(25, 29);
		break;
#endif
#if defined(useAileronHeavyItalic36) || defined(useAllFonts)
	case(AileronHeavyItalic36):
		charRect = new Point(37, 43);
		break;
#endif
#if defined(useAileronLight9) || defined(useAllFonts)
	case(AileronLight9):
		charRect = new Point(10, 11);
		break;
#endif
#if defined(useAileronLight12) || defined(useAllFonts)
	case(AileronLight12):
		charRect = new Point(13, 14);
		break;
#endif
#if defined(useAileronLight18) || defined(useAllFonts)
	case(AileronLight18):
		charRect = new Point(19, 22);
		break;
#endif
#if defined(useAileronLight24) || defined(useAllFonts)
	case(AileronLight24):
		charRect = new Point(25, 29);
		break;
#endif
#if defined(useAileronLight36) || defined(useAllFonts)
	case(AileronLight36):
		charRect = new Point(37, 43);
		break;
#endif
#if defined(useAileronRegular9) || defined(useAllFonts)
	case(AileronRegular9):
		charRect = new Point(10, 11);
		break;
#endif
#if defined(useAileronRegular12) || defined(useAllFonts)
	case(AileronRegular12):
		charRect = new Point(13, 14);
		break;
#endif
#if defined(useAileronRegular18) || defined(useAllFonts)
	case(AileronRegular18):
		charRect = new Point(19, 22);
		break;
#endif
#if defined(useAileronRegular24) || defined(useAllFonts)
	case(AileronRegular24):
		charRect = new Point(25, 29);
		break;
#endif
#if defined(useAileronRegular36) || defined(useAllFonts)
	case(AileronRegular36):
		charRect = new Point(37, 43);
		break;
#endif
#if defined(useAileronSemiBold9) || defined(useAllFonts)
	case(AileronSemiBold9):
		charRect = new Point(10, 11);
		break;
#endif
#if defined(useAileronSemiBold12) || defined(useAllFonts)
	case(AileronSemiBold12):
		charRect = new Point(13, 14);
		break;
#endif
#if defined(useAileronSemiBold18) || defined(useAllFonts)
	case(AileronSemiBold18):
		charRect = new Point(19, 22);
		break;
#endif
#if defined(useAileronSemiBold24) || defined(useAllFonts)
	case(AileronSemiBold24):
		charRect = new Point(25, 29);
		break;
#endif
#if defined(useAileronSemiBold36) || defined(useAllFonts)
	case(AileronSemiBold36):
		charRect = new Point(37, 43);
		break;
#endif
#if defined(useAileronSemiBoldItalic9) || defined(useAllFonts)
	case(AileronSemiBoldItalic9):
		charRect = new Point(10, 11);
		break;
#endif
#if defined(useAileronSemiBoldItalic12) || defined(useAllFonts)
	case(AileronSemiBoldItalic12):
		charRect = new Point(13, 14);
		break;
#endif
#if defined(useAileronSemiBoldItalic18) || defined(useAllFonts)
	case(AileronSemiBoldItalic18)):
	charRect = new Point(19, 22);
	break;
#endif
#if defined(useAileronSemiBoldItalic24) || defined(useAllFonts)
	case(AileronSemiBoldItalic24):
		charRect = new Point(25, 29);
		break;
#endif
#if defined(useAileronSemiBoldItalic36) || defined(useAllFonts)
	case(AileronSemiBoldItalic36):
		charRect = new Point(37, 43);
		break;
#endif
#if defined(useAileronThin9) || defined(useAllFonts)
	case(AileronThin9):
		charRect = new Point(10, 11);
		break;
#endif
#if defined(useAileronThin12) || defined(useAllFonts)
	case(AileronThin12):
		charRect = new Point(13, 14);
		break;
#endif
#if defined(useAileronThin18) || defined(useAllFonts)
	case(AileronThin18):
		charRect = new Point(19, 22);
		break;
#endif

#if defined(useAileronThin24) || defined(useAllFonts)
	case(AileronThin24):
		charRect = new Point(25, 29);
		break;
#endif

#if defined(useAileronThin36) || defined(useAllFonts)
	case(AileronThin36):
		charRect = new Point(37, 43);
		break;
#endif

#if defined(useAileronThinItalic9) || defined(useAllFonts)
	case(AileronThinItalic9):
		charRect = new Point(10, 11);
		break;
#endif

#if defined(useAileronThinItalic12) || defined(useAllFonts)
	case(AileronThinItalic12):
		charRect = new Point(13, 14);
		break;
#endif

#if defined(useAileronThinItalic18) || defined(useAllFonts)
	case(AileronThinItalic18):
		charRect = new Point(19, 22);
		break;
#endif

#if defined(useAileronThinItalic24) || defined(useAllFonts)
	case(AileronThinItalic24):
		charRect = new Point(25, 29);
		break;
#endif

#if defined(useAileronThinItalic36) || defined(useAllFonts)
	case(AileronThinItalic36):
		charRect = new Point(37, 43);
		break;
#endif

#if defined(useAileronUltraLight9) || defined(useAllFonts)
	case(AileronUltraLight9):
		charRect = new Point(10, 11);
		break;
#endif

#if defined(useAileronUltraLight12) || defined(useAllFonts)
	case(AileronUltraLight12):
		charRect = new Point(13, 14);
		break;
#endif

#if defined(useAileronUltraLight18) || defined(useAllFonts)
	case(AileronUltraLight18):
		charRect = new Point(19, 22);
		break;
#endif

#if defined(useAileronUltraLight24) || defined(useAllFonts)
	case(AileronUltraLight24):
		charRect = new Point(25, 29);
		break;
#endif

#if defined(useAileronUltraLight36) || defined(useAllFonts)
	case(AileronUltraLight36):
		charRect = new Point(37, 43);
		break;
#endif

#if defined(useAileronUltraLightItalic9) || defined(useAllFonts)
	case(AileronUltraLightItalic9):
		charRect = new Point(10, 11);
		break;
#endif

#if defined(useAileronUltraLightItalic12) || defined(useAllFonts)
	case(AileronUltraLightItalic12):
		charRect = new Point(13, 14);
		break;
#endif

#if defined(useAileronUltraLightItalic18) || defined(useAllFonts)
	case(AileronUltraLightItalic18):
		charRect = new Point(19, 22);
		break;
#endif

#if defined(useAileronUltraLightItalic24) || defined(useAllFonts)
	case(AileronUltraLightItalic24):
		charRect = new Point(25, 29);
		break;
#endif

#if defined(useAileronUltraLightItalic36) || defined(useAllFonts)
	case(AileronUltraLightItalic36):
		charRect = new Point(37, 43);
		break;
#endif

#if defined(useCourierPrime9) || defined(useAllFonts)
	case(CourierPrime9):
		charRect = new Point(10, 11);
		break;
#endif

#if defined(useCourierPrime12) || defined(useAllFonts)
	case(CourierPrime12):
		charRect = new Point(13, 14);
		break;
#endif

#if defined(useCourierPrime18) || defined(useAllFonts)
	case(CourierPrime18):
		charRect = new Point(19, 22);
		break;
#endif

#if defined(useCourierPrime24) || defined(useAllFonts)
	case(CourierPrime24):
		charRect = new Point(25, 29);
		break;
#endif

#if defined(useCourierPrime36) || defined(useAllFonts)
	case(CourierPrime36):
		charRect = new Point(37, 43);
		break;
#endif

#if defined(useCourierPrimeBold9) || defined(useAllFonts)
	case(CourierPrimeBold9):
		charRect = new Point(10, 11);
		break;
#endif

#if defined(useCourierPrimeBold12) || defined(useAllFonts)
	case(CourierPrimeBold12):
		charRect = new Point(13, 14);
		break;
#endif

#if defined(useCourierPrimeBold18) || defined(useAllFonts)
	case(CourierPrimeBold18):
		charRect = new Point(19, 22);
		break;
#endif

#if defined(useCourierPrimeBold24) || defined(useAllFonts)
	case(CourierPrimeBold24):
		charRect = new Point(25, 29);
		break;
#endif

#if defined(useCourierPrimeBold36) || defined(useAllFonts)
	case(CourierPrimeBold36):
		charRect = new Point(37, 43);
		break;
#endif

#if defined(useCourierPrimeBoldItalic9) || defined(useAllFonts)
	case(CourierPrimeBoldItalic9):
		charRect = new Point(10, 11);
		break;
#endif

#if defined(useCourierPrimeBoldItalic12) || defined(useAllFonts)
	case(CourierPrimeBoldItalic12):
		charRect = new Point(13, 14);
		break;
#endif

#if defined(useCourierPrimeBoldItalic18) || defined(useAllFonts)
	case(CourierPrimeBoldItalic18):
		charRect = new Point(19, 22);
		break;
#endif

#if defined(useCourierPrimeBoldItalic24) || defined(useAllFonts)
	case(CourierPrimeBoldItalic24):
		charRect = new Point(25, 29);
		break;
#endif

#if defined(useCourierPrimeBoldItalic36) || defined(useAllFonts)
	case(CourierPrimeBoldItalic36):
		charRect = new Point(37, 43);
		break;
#endif

#if defined(useCourierPrimeItalic9) || defined(useAllFonts)
	case(CourierPrimeItalic9):
		charRect = new Point(10, 11);
		break;
#endif

#if defined(useCourierPrimeItalic12) || defined(useAllFonts)
	case(CourierPrimeItalic12):
		charRect = new Point(13, 14);
		break;
#endif

#if defined(useCourierPrimeItalic18) || defined(useAllFonts)
	case(CourierPrimeItalic18):
		charRect = new Point(19, 22);
		break;
#endif

#if defined(useCourierPrimeItalic24) || defined(useAllFonts)
	case(CourierPrimeItalic24):
		charRect = new Point(25, 29);
		break;
#endif

#if defined(useCourierPrimeItalic36) || defined(useAllFonts)
	case(CourierPrimeItalic36):
		charRect = new Point(37, 43);
		break;
#endif

#if defined(useCrimsonBold9) || defined(useAllFonts)
	case(CrimsonBold9):
		charRect = new Point(10, 11);
		break;
#endif

#if defined(useCrimsonBold12) || defined(useAllFonts)
	case(CrimsonBold12):
		charRect = new Point(13, 14);
		break;
#endif

#if defined(useCrimsonBold18) || defined(useAllFonts)
	case(CrimsonBold18):
		charRect = new Point(19, 22);
		break;
#endif

#if defined(useCrimsonBold24) || defined(useAllFonts)
	case(CrimsonBold24):
		charRect = new Point(25, 29);
		break;
#endif

#if defined(useCrimsonBold36) || defined(useAllFonts)
	case(CrimsonBold36):
		charRect = new Point(37, 43);
		break;
#endif

#if defined(useCrimsonBoldItalic9) || defined(useAllFonts)
	case(CrimsonBoldItalic9):
		charRect = new Point(10, 11);
		break;
#endif

#if defined(useCrimsonBoldItalic12) || defined(useAllFonts)
	case(CrimsonBoldItalic12):
		charRect = new Point(13, 14);
		break;
#endif

#if defined(useCrimsonBoldItalic18) || defined(useAllFonts)
	case(CrimsonBoldItalic18):
		charRect = new Point(19, 22);
		break;
#endif

#if defined(useCrimsonBoldItalic24) || defined(useAllFonts)
	case(CrimsonBoldItalic24):
		charRect = new Point(25, 29);
		break;
#endif

#if defined(useCrimsonBoldItalic36) || defined(useAllFonts)
	case(CrimsonBoldItalic36):
		charRect = new Point(37, 43);
		break;
#endif

#if defined(useCrimsonRoman9) || defined(useAllFonts)
	case(CrimsonRoman9):
		charRect = new Point(10, 11);
		break;
#endif

#if defined(useCrimsonRoman12) || defined(useAllFonts)
	case(CrimsonRoman12):
		charRect = new Point(13, 14);
		break;
#endif

#if defined(useCrimsonRoman18) || defined(useAllFonts)
	case(CrimsonRoman18):
		charRect = new Point(19, 22);
		break;
#endif

#if defined(useCrimsonRoman24) || defined(useAllFonts)
	case(CrimsonRoman24):
		charRect = new Point(25, 29);
		break;
#endif

#if defined(useCrimsonRoman36) || defined(useAllFonts)
	case(CrimsonRoman36):
		charRect = new Point(37, 43);
		break;
#endif

#if defined(useCrimsonSemiBold9) || defined(useAllFonts)
	case(CrimsonSemiBold9):
		charRect = new Point(10, 11);
		break;
#endif

#if defined(useCrimsonSemiBold12) || defined(useAllFonts)
	case(CrimsonSemiBold12):
		charRect = new Point(13, 14);
		break;
#endif

#if defined(useCrimsonSemiBold18) || defined(useAllFonts)
	case(CrimsonSemiBold18):
		charRect = new Point(19, 22);
		break;
#endif

#if defined(useCrimsonSemiBold24) || defined(useAllFonts)
	case(CrimsonSemiBold24):
		charRect = new Point(25, 29);
		break;
#endif

#if defined(useCrimsonSemiBold36) || defined(useAllFonts)
	case(CrimsonSemiBold36):
		charRect = new Point(37, 43);
		break;
#endif

#if defined(useCrimsonSemiBoldItalic9) || defined(useAllFonts)
	case(CrimsonSemiBoldItalic9):
		charRect = new Point(10, 11);
		break;
#endif

#if defined(useCrimsonSemiBoldItalic12) || defined(useAllFonts)
	case(CrimsonSemiBoldItalic12):
		charRect = new Point(13, 14);
		break;
#endif

#if defined(useCrimsonSemiBoldItalic18) || defined(useAllFonts)
	case(CrimsonSemiBoldItalic18):
		charRect = new Point(19, 22);
		break;
#endif

#if defined(useCrimsonSemiBoldItalic24) || defined(useAllFonts)
	case(CrimsonSemiBoldItalic24):
		charRect = new Point(25, 29);
		break;
#endif

#if defined(useCrimsonSemiBoldItalic36) || defined(useAllFonts)
	case(CrimsonSemiBoldItalic36):
		charRect = new Point(25, 29);
		break;
#endif
	}
	return(
		Rectangle(textLoc.x, textLoc.y, textLoc.x + (text.length()*charRect->x), textLoc.y + charRect->y)
		);
}
#endif
