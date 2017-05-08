#pragma once
#include "../../Options.h"
#ifdef RA8875
#include <SPI.h>
#include "../../External/Adafruit_RA8875/Adafruit_RA8875.h"

// Defines the includes based on which fonts were selected in Options, dont edit here, edit in Options.h
#if defined(useAileronBlack9) || defined(useAllFonts)
#include "Fonts\AileronBlack9.h"
#endif

#if defined(useAileronBlack12) || defined(useAllFonts)
#include "Fonts\AileronBlack12.h"
#endif

#if defined(useAileronBlack18) || defined(useAllFonts)
#include "Fonts\AileronBlack18.h"
#endif

#if defined(useAileronBlack24) || defined(useAllFonts)
#include "Fonts\AileronBlack24.h"
#endif

#if defined(useAileronBlack36) || defined(useAllFonts)
#include "Fonts\AileronBlack36.h"
#endif

#if defined(useAileronBlackItalic9) || defined(useAllFonts)
#include "Fonts\AileronBlackItalic9.h"
#endif

#if defined(useAileronBlackItalic12) || defined(useAllFonts)
#include "Fonts\AileronBlackItalic12.h"
#endif

#if defined(useAileronBlackItalic18) || defined(useAllFonts)
#include "Fonts\AileronBlackItalic18.h"
#endif

#if defined(useAileronBlackItalic24) || defined(useAllFonts)
#include "Fonts\AileronBlackItalic24.h"
#endif

#if defined(useAileronBlackItalic36) || defined(useAllFonts)
#include "Fonts\AileronBlackItalic36.h"
#endif

#if defined(useAileronBold9) || defined(useAllFonts)
#include "Fonts\AileronBold9.h"
#endif

#if defined(useAileronBold12) || defined(useAllFonts)
#include "Fonts\AileronBold12.h"
#endif

#if defined(useAileronBold18) || defined(useAllFonts)
#include "Fonts\AileronBold18.h"
#endif

#if defined(useAileronBold24) || defined(useAllFonts)
#include "Fonts\AileronBold24.h"
#endif

#if defined(useAileronBold36) || defined(useAllFonts)
#include "Fonts\AileronBold36.h"
#endif

#if defined(useAileronBoldItalic9) || defined(useAllFonts)
#include "Fonts\AileronBoldItalic9.h"
#endif

#if defined(useAileronBoldItalic12) || defined(useAllFonts)
#include "Fonts\AileronBoldItalic12.h"
#endif

#if defined(useAileronBoldItalic18) || defined(useAllFonts)
#include "Fonts\AileronBoldItalic18.h"
#endif

#if defined(useAileronBoldItalic24) || defined(useAllFonts)
#include "Fonts\AileronBoldItalic24.h"
#endif

#if defined(useAileronBoldItalic36) || defined(useAllFonts)
#include "Fonts\AileronBoldItalic36.h"
#endif

#if defined(useAileronHeavy9) || defined(useAllFonts)
#include "Fonts\AileronHeavy9.h"
#endif

#if defined(useAileronHeavy12) || defined(useAllFonts)
#include "Fonts\AileronHeavy12.h"
#endif

#if defined(useAileronHeavy18) || defined(useAllFonts)
#include "Fonts\AileronHeavy18.h"
#endif

#if defined(useAileronHeavy24) || defined(useAllFonts)
#include "Fonts\AileronHeavy24.h"
#endif

#if defined(useAileronHeavy36) || defined(useAllFonts)
#include "Fonts\AileronHeavy36.h"
#endif

#if defined(useAileronHeavyItalic9) || defined(useAllFonts)
#include "Fonts\AileronHeavyItalic9.h"
#endif

#if defined(useAileronHeavyItalic12) || defined(useAllFonts)
#include "Fonts\AileronHeavyItalic12.h"
#endif

#if defined(useAileronHeavyItalic18) || defined(useAllFonts)
#include "Fonts\AileronHeavyItalic18.h"
#endif

#if defined(useAileronHeavyItalic24) || defined(useAllFonts)
#include "Fonts\AileronHeavyItalic24.h"
#endif

#if defined(useAileronHeavyItalic36) || defined(useAllFonts)
#include "Fonts\AileronHeavyItalic36.h"
#endif

#if defined(useAileronLight9) || defined(useAllFonts)
#include "Fonts\AileronLight9.h"
#endif

#if defined(useAileronLight12) || defined(useAllFonts)
#include "Fonts\AileronLight12.h"
#endif

#if defined(useAileronLight18) || defined(useAllFonts)
#include "Fonts\AileronLight18.h"
#endif

#if defined(useAileronLight24) || defined(useAllFonts)
#include "Fonts\AileronLight24.h"
#endif

#if defined(useAileronLight36) || defined(useAllFonts)
#include "Fonts\AileronLight36.h"
#endif

#if defined(useAileronRegular9) || defined(useAllFonts)
#include "Fonts\AileronRegular9.h"
#endif

#if defined(useAileronRegular12) || defined(useAllFonts)
#include "Fonts\AileronRegular12.h"
#endif

#if defined(useAileronRegular18) || defined(useAllFonts)
#include "Fonts\AileronRegular18.h"
#endif

#if defined(useAileronRegular24) || defined(useAllFonts)
#include "Fonts\AileronRegular24.h"
#endif

#if defined(useAileronRegular36) || defined(useAllFonts)
#include "Fonts\AileronRegular36.h"
#endif

#if defined(useAileronSemiBold9) || defined(useAllFonts)
#include "Fonts\AileronSemiBold9.h"
#endif

#if defined(useAileronSemiBold12) || defined(useAllFonts)
#include "Fonts\AileronSemiBold12.h"
#endif

#if defined(useAileronSemiBold18) || defined(useAllFonts)
#include "Fonts\AileronSemiBold18.h"
#endif

#if defined(useAileronSemiBold24) || defined(useAllFonts)
#include "Fonts\AileronSemiBold24.h"
#endif

#if defined(useAileronSemiBold36) || defined(useAllFonts)
#include "Fonts\AileronSemiBold36.h"
#endif

#if defined(useAileronSemiBoldItalic9) || defined(useAllFonts)
#include "Fonts\AileronSemiBoldItalic9.h"
#endif

#if defined(useAileronSemiBoldItalic12) || defined(useAllFonts)
#include "Fonts\AileronSemiBoldItalic12.h"
#endif

#if defined(useAileronSemiBoldItalic18) || defined(useAllFonts)
#include "Fonts\AileronSemiBoldItalic18.h"
#endif

#if defined(useAileronSemiBoldItalic24) || defined(useAllFonts)
#include "Fonts\AileronSemiBoldItalic24.h"
#endif

#if defined(useAileronSemiBoldItalic36) || defined(useAllFonts)
#include "Fonts\AileronSemiBoldItalic36.h"
#endif

#if defined(useAileronThin9) || defined(useAllFonts)
#include "Fonts\AileronThin9.h"
#endif

#if defined(useAileronThin12) || defined(useAllFonts)
#include "Fonts\AileronThin12.h"
#endif

#if defined(useAileronThin18) || defined(useAllFonts)
#include "Fonts\AileronThin18.h"
#endif

#if defined(useAileronThin24) || defined(useAllFonts)
#include "Fonts\AileronThin24.h"
#endif

#if defined(useAileronThin36) || defined(useAllFonts)
#include "Fonts\AileronThin36.h"
#endif

#if defined(useAileronThinItalic9) || defined(useAllFonts)
#include "Fonts\AileronThinItalic9.h"
#endif

#if defined(useAileronThinItalic12) || defined(useAllFonts)
#include "Fonts\AileronThinItalic12.h"
#endif

#if defined(useAileronThinItalic18) || defined(useAllFonts)
#include "Fonts\AileronThinItalic18.h"
#endif

#if defined(useAileronThinItalic24) || defined(useAllFonts)
#include "Fonts\AileronThinItalic24.h"
#endif

#if defined(useAileronThinItalic36) || defined(useAllFonts)
#include "Fonts\AileronThinItalic36.h"
#endif

#if defined(useAileronUltraLight9) || defined(useAllFonts)
#include "Fonts\AileronUltraLight9.h"
#endif

#if defined(useAileronUltraLight12) || defined(useAllFonts)
#include "Fonts\AileronUltraLight12.h"
#endif

#if defined(useAileronUltraLight18) || defined(useAllFonts)
#include "Fonts\AileronUltraLight18.h"
#endif

#if defined(useAileronUltraLight24) || defined(useAllFonts)
#include "Fonts\AileronUltraLight24.h"
#endif

#if defined(useAileronUltraLight36) || defined(useAllFonts)
#include "Fonts\AileronUltraLight36.h"
#endif

#if defined(useAileronUltraLightItalic9) || defined(useAllFonts)
#include "Fonts\AileronUltraLightItalic9.h"
#endif

#if defined(useAileronUltraLightItalic12) || defined(useAllFonts)
#include "Fonts\AileronUltraLightItalic12.h"
#endif

#if defined(useAileronUltraLightItalic18) || defined(useAllFonts)
#include "Fonts\AileronUltraLightItalic18.h"
#endif

#if defined(useAileronUltraLightItalic24) || defined(useAllFonts)
#include "Fonts\AileronUltraLightItalic24.h"
#endif

#if defined(useAileronUltraLightItalic36) || defined(useAllFonts)
#include "Fonts\AileronUltraLightItalic36.h"
#endif

#if defined(useCourierPrime9) || defined(useAllFonts)
#include "Fonts\CourierPrime9.h"
#endif

#if defined(useCourierPrime12) || defined(useAllFonts)
#include "Fonts\CourierPrime12.h"
#endif

#if defined(useCourierPrime18) || defined(useAllFonts)
#include "Fonts\CourierPrime18.h"
#endif

#if defined(useCourierPrime24) || defined(useAllFonts)
#include "Fonts\CourierPrime24.h"
#endif

#if defined(useCourierPrime36) || defined(useAllFonts)
#include "Fonts\CourierPrime36.h"
#endif

#if defined(useCourierPrimeBold9) || defined(useAllFonts)
#include "Fonts\CourierPrimeBold9.h"
#endif

#if defined(useCourierPrimeBold12) || defined(useAllFonts)
#include "Fonts\CourierPrimeBold12.h"
#endif

#if defined(useCourierPrimeBold18) || defined(useAllFonts)
#include "Fonts\CourierPrimeBold18.h"
#endif

#if defined(useCourierPrimeBold24) || defined(useAllFonts)
#include "Fonts\CourierPrimeBold24.h"
#endif

#if defined(useCourierPrimeBold36) || defined(useAllFonts)
#include "Fonts\CourierPrimeBold36.h"
#endif

#if defined(useCourierPrimeBoldItalic9) || defined(useAllFonts)
#include "Fonts\CourierPrimeBoldItalic9.h"
#endif

#if defined(useCourierPrimeBoldItalic12) || defined(useAllFonts)
#include "Fonts\CourierPrimeBoldItalic12.h"
#endif

#if defined(useCourierPrimeBoldItalic18) || defined(useAllFonts)
#include "Fonts\CourierPrimeBoldItalic18.h"
#endif

#if defined(useCourierPrimeBoldItalic24) || defined(useAllFonts)
#include "Fonts\CourierPrimeBoldItalic24.h"
#endif

#if defined(useCourierPrimeBoldItalic36) || defined(useAllFonts)
#include "Fonts\CourierPrimeBoldItalic36.h"
#endif

#if defined(useCourierPrimeItalic9) || defined(useAllFonts)
#include "Fonts\CourierPrimeItalic9.h"
#endif

#if defined(useCourierPrimeItalic12) || defined(useAllFonts)
#include "Fonts\CourierPrimeItalic12.h"
#endif

#if defined(useCourierPrimeItalic18) || defined(useAllFonts)
#include "Fonts\CourierPrimeItalic18.h"
#endif

#if defined(useCourierPrimeItalic24) || defined(useAllFonts)
#include "Fonts\CourierPrimeItalic24.h"
#endif

#if defined(useCourierPrimeItalic36) || defined(useAllFonts)
#include "Fonts\CourierPrimeItalic36.h"
#endif

#if defined(useCrimsonBold9) || defined(useAllFonts)
#include "Fonts\CrimsonBold9.h"
#endif

#if defined(useCrimsonBold12) || defined(useAllFonts)
#include "Fonts\CrimsonBold12.h"
#endif

#if defined(useCrimsonBold18) || defined(useAllFonts)
#include "Fonts\CrimsonBold18.h"
#endif

#if defined(useCrimsonBold24) || defined(useAllFonts)
#include "Fonts\CrimsonBold24.h"
#endif

#if defined(useCrimsonBold36) || defined(useAllFonts)
#include "Fonts\CrimsonBold36.h"
#endif

#if defined(useCrimsonBoldItalic9) || defined(useAllFonts)
#include "Fonts\CrimsonBoldItalic9.h"
#endif

#if defined(useCrimsonBoldItalic12) || defined(useAllFonts)
#include "Fonts\CrimsonBoldItalic12.h"
#endif

#if defined(useCrimsonBoldItalic18) || defined(useAllFonts)
#include "Fonts\CrimsonBoldItalic18.h"
#endif

#if defined(useCrimsonBoldItalic24) || defined(useAllFonts)
#include "Fonts\CrimsonBoldItalic24.h"
#endif

#if defined(useCrimsonBoldItalic36) || defined(useAllFonts)
#include "Fonts\CrimsonBoldItalic36.h"
#endif

#if defined(useCrimsonRoman9) || defined(useAllFonts)
#include "Fonts\CrimsonRoman9.h"
#endif

#if defined(useCrimsonRoman12) || defined(useAllFonts)
#include "Fonts\CrimsonRoman12.h"
#endif

#if defined(useCrimsonRoman18) || defined(useAllFonts)
#include "Fonts\CrimsonRoman18.h"
#endif

#if defined(useCrimsonRoman24) || defined(useAllFonts)
#include "Fonts\CrimsonRoman24.h"
#endif

#if defined(useCrimsonRoman36) || defined(useAllFonts)
#include "Fonts\CrimsonRoman36.h"
#endif

#if defined(useCrimsonSemiBold9) || defined(useAllFonts)
#include "Fonts\CrimsonSemiBold9.h"
#endif

#if defined(useCrimsonSemiBold12) || defined(useAllFonts)
#include "Fonts\CrimsonSemiBold12.h"
#endif

#if defined(useCrimsonSemiBold18) || defined(useAllFonts)
#include "Fonts\CrimsonSemiBold18.h"
#endif

#if defined(useCrimsonSemiBold24) || defined(useAllFonts)
#include "Fonts\CrimsonSemiBold24.h"
#endif

#if defined(useCrimsonSemiBold36) || defined(useAllFonts)
#include "Fonts\CrimsonSemiBold36.h"
#endif

#if defined(useCrimsonSemiBoldItalic9) || defined(useAllFonts)
#include "Fonts\CrimsonSemiBoldItalic9.h"
#endif

#if defined(useCrimsonSemiBoldItalic12) || defined(useAllFonts)
#include "Fonts\CrimsonSemiBoldItalic12.h"
#endif

#if defined(useCrimsonSemiBoldItalic18) || defined(useAllFonts)
#include "Fonts\CrimsonSemiBoldItalic18.h"
#endif

#if defined(useCrimsonSemiBoldItalic24) || defined(useAllFonts)
#include "Fonts\CrimsonSemiBoldItalic24.h"
#endif

#if defined(useCrimsonSemiBoldItalic36) || defined(useAllFonts)
#include "Fonts\CrimsonSemiBoldItalic36.h"
#endif

enum eUITextFont
{
#if defined(useAileronBlack9) || defined(useAllFonts)
AileronBlack9,
#endif
#if defined(useAileronBlack12) || defined(useAllFonts)
AileronBlack12,
#endif
#if defined(useAileronBlack18) || defined(useAllFonts)
AileronBlack18,
#endif
#if defined(useAileronBlack24) || defined(useAllFonts)
AileronBlack24,
#endif
#if defined(useAileronBlack36) || defined(useAllFonts)
AileronBlack36,
#endif
#if defined(useAileronBlackItalic9) || defined(useAllFonts)
AileronBlackItalic9,
#endif
#if defined(useAileronBlackItalic12) || defined(useAllFonts)
AileronBlackItalic12,
#endif
#if defined(useAileronBlackItalic18) || defined(useAllFonts)
AileronBlackItalic18,
#endif
#if defined(useAileronBlackItalic24) || defined(useAllFonts)
AileronBlackItalic24,
#endif
#if defined(useAileronBlackItalic36) || defined(useAllFonts)
AileronBlackItalic36,
#endif
#if defined(useAileronBold9) || defined(useAllFonts)
AileronBold9,
#endif
#if defined(useAileronBold12) || defined(useAllFonts)
AileronBold12,
#endif
#if defined(useAileronBold18) || defined(useAllFonts)
AileronBold18,
#endif
#if defined(useAileronBold24) || defined(useAllFonts)
AileronBold24,
#endif
#if defined(useAileronBold36) || defined(useAllFonts)
AileronBold36,
#endif
#if defined(useAileronBoldItalic9) || defined(useAllFonts)
AileronBoldItalic9,
#endif
#if defined(useAileronBoldItalic12) || defined(useAllFonts)
AileronBoldItalic12,
#endif
#if defined(useAileronBoldItalic18) || defined(useAllFonts)
AileronBoldItalic18,
#endif
#if defined(useAileronBoldItalic24) || defined(useAllFonts)
AileronBoldItalic24,
#endif
#if defined(useAileronBoldItalic36) || defined(useAllFonts)
AileronBoldItalic36,
#endif
#if defined(useAileronHeavy9) || defined(useAllFonts)
AileronHeavy9,
#endif
#if defined(useAileronHeavy12) || defined(useAllFonts)
AileronHeavy12,
#endif
#if defined(useAileronHeavy18) || defined(useAllFonts)
AileronHeavy18,
#endif
#if defined(useAileronHeavy24) || defined(useAllFonts)
AileronHeavy24,
#endif
#if defined(useAileronHeavy36) || defined(useAllFonts)
AileronHeavy36,
#endif
#if defined(useAileronHeavyItalic9) || defined(useAllFonts)
AileronHeavyItalic9,
#endif
#if defined(useAileronHeavyItalic12) || defined(useAllFonts)
AileronHeavyItalic12,
#endif
#if defined(useAileronHeavyItalic18) || defined(useAllFonts)
AileronHeavyItalic18,
#endif
#if defined(useAileronHeavyItalic24) || defined(useAllFonts)
AileronHeavyItalic24,
#endif
#if defined(useAileronHeavyItalic36) || defined(useAllFonts)
AileronHeavyItalic36,
#endif
#if defined(useAileronLight9) || defined(useAllFonts)
AileronLight9,
#endif
#if defined(useAileronLight12) || defined(useAllFonts)
AileronLight12,
#endif
#if defined(useAileronLight18) || defined(useAllFonts)
AileronLight18,
#endif
#if defined(useAileronLight24) || defined(useAllFonts)
AileronLight24,
#endif
#if defined(useAileronLight36) || defined(useAllFonts)
AileronLight36,
#endif
#if defined(useAileronRegular9) || defined(useAllFonts)
AileronRegular9,
#endif
#if defined(useAileronRegular12) || defined(useAllFonts)
AileronRegular12,
#endif
#if defined(useAileronRegular18) || defined(useAllFonts)
AileronRegular18,
#endif
#if defined(useAileronRegular24) || defined(useAllFonts)
AileronRegular24,
#endif
#if defined(useAileronRegular36) || defined(useAllFonts)
AileronRegular36,
#endif
#if defined(useAileronSemiBold9) || defined(useAllFonts)
AileronSemiBold9,
#endif
#if defined(useAileronSemiBold12) || defined(useAllFonts)
AileronSemiBold12,
#endif
#if defined(useAileronSemiBold18) || defined(useAllFonts)
AileronSemiBold18,
#endif
#if defined(useAileronSemiBold24) || defined(useAllFonts)
AileronSemiBold24,
#endif
#if defined(useAileronSemiBold36) || defined(useAllFonts)
AileronSemiBold36,
#endif
#if defined(useAileronSemiBoldItalic9) || defined(useAllFonts)
AileronSemiBoldItalic9,
#endif
#if defined(useAileronSemiBoldItalic12) || defined(useAllFonts)
AileronSemiBoldItalic12,
#endif
#if defined(useAileronSemiBoldItalic18) || defined(useAllFonts)
AileronSemiBoldItalic18,
#endif
#if defined(useAileronSemiBoldItalic24) || defined(useAllFonts)
AileronSemiBoldItalic24,
#endif
#if defined(useAileronSemiBoldItalic36) || defined(useAllFonts)
AileronSemiBoldItalic36,
#endif
#if defined(useAileronThin9) || defined(useAllFonts)
AileronThin9,
#endif
#if defined(useAileronThin12) || defined(useAllFonts)
AileronThin12,
#endif
#if defined(useAileronThin18) || defined(useAllFonts)
AileronThin18,
#endif

#if defined(useAileronThin24) || defined(useAllFonts)
AileronThin24,
#endif

#if defined(useAileronThin36) || defined(useAllFonts)
AileronThin36,
#endif

#if defined(useAileronThinItalic9) || defined(useAllFonts)
AileronThinItalic9,
#endif

#if defined(useAileronThinItalic12) || defined(useAllFonts)
AileronThinItalic12,
#endif

#if defined(useAileronThinItalic18) || defined(useAllFonts)
AileronThinItalic18,
#endif

#if defined(useAileronThinItalic24) || defined(useAllFonts)
AileronThinItalic24,
#endif

#if defined(useAileronThinItalic36) || defined(useAllFonts)
AileronThinItalic36,
#endif

#if defined(useAileronUltraLight9) || defined(useAllFonts)
AileronUltraLight9,
#endif

#if defined(useAileronUltraLight12) || defined(useAllFonts)
AileronUltraLight12,
#endif

#if defined(useAileronUltraLight18) || defined(useAllFonts)
AileronUltraLight18,
#endif

#if defined(useAileronUltraLight24) || defined(useAllFonts)
AileronUltraLight24,
#endif

#if defined(useAileronUltraLight36) || defined(useAllFonts)
AileronUltraLight36,
#endif

#if defined(useAileronUltraLightItalic9) || defined(useAllFonts)
AileronUltraLightItalic9,
#endif

#if defined(useAileronUltraLightItalic12) || defined(useAllFonts)
AileronUltraLightItalic12,
#endif

#if defined(useAileronUltraLightItalic18) || defined(useAllFonts)
AileronUltraLightItalic18,
#endif

#if defined(useAileronUltraLightItalic24) || defined(useAllFonts)
AileronUltraLightItalic24,
#endif

#if defined(useAileronUltraLightItalic36) || defined(useAllFonts)
AileronUltraLightItalic36,
#endif

#if defined(useCourierPrime9) || defined(useAllFonts)
CourierPrime9,
#endif

#if defined(useCourierPrime12) || defined(useAllFonts)
CourierPrime12,
#endif

#if defined(useCourierPrime18) || defined(useAllFonts)
CourierPrime18,
#endif

#if defined(useCourierPrime24) || defined(useAllFonts)
CourierPrime24,
#endif

#if defined(useCourierPrime36) || defined(useAllFonts)
CourierPrime36,
#endif

#if defined(useCourierPrimeBold9) || defined(useAllFonts)
CourierPrimeBold9,
#endif

#if defined(useCourierPrimeBold12) || defined(useAllFonts)
CourierPrimeBold12,
#endif

#if defined(useCourierPrimeBold18) || defined(useAllFonts)
CourierPrimeBold18,
#endif

#if defined(useCourierPrimeBold24) || defined(useAllFonts)
CourierPrimeBold24,
#endif

#if defined(useCourierPrimeBold36) || defined(useAllFonts)
CourierPrimeBold36,
#endif

#if defined(useCourierPrimeBoldItalic9) || defined(useAllFonts)
CourierPrimeBoldItalic9,
#endif

#if defined(useCourierPrimeBoldItalic12) || defined(useAllFonts)
CourierPrimeBoldItalic12,
#endif

#if defined(useCourierPrimeBoldItalic18) || defined(useAllFonts)
CourierPrimeBoldItalic18,
#endif

#if defined(useCourierPrimeBoldItalic24) || defined(useAllFonts)
CourierPrimeBoldItalic24,
#endif

#if defined(useCourierPrimeBoldItalic36) || defined(useAllFonts)
CourierPrimeBoldItalic36,
#endif

#if defined(useCourierPrimeItalic9) || defined(useAllFonts)
CourierPrimeItalic9,
#endif

#if defined(useCourierPrimeItalic12) || defined(useAllFonts)
CourierPrimeItalic12,
#endif

#if defined(useCourierPrimeItalic18) || defined(useAllFonts)
CourierPrimeItalic18,
#endif

#if defined(useCourierPrimeItalic24) || defined(useAllFonts)
CourierPrimeItalic24,
#endif

#if defined(useCourierPrimeItalic36) || defined(useAllFonts)
CourierPrimeItalic36,
#endif

#if defined(useCrimsonBold9) || defined(useAllFonts)
CrimsonBold9,
#endif

#if defined(useCrimsonBold12) || defined(useAllFonts)
CrimsonBold12,
#endif

#if defined(useCrimsonBold18) || defined(useAllFonts)
CrimsonBold18,
#endif

#if defined(useCrimsonBold24) || defined(useAllFonts)
CrimsonBold24,
#endif

#if defined(useCrimsonBold36) || defined(useAllFonts)
CrimsonBold36,
#endif

#if defined(useCrimsonBoldItalic9) || defined(useAllFonts)
CrimsonBoldItalic9,
#endif

#if defined(useCrimsonBoldItalic12) || defined(useAllFonts)
CrimsonBoldItalic12,
#endif

#if defined(useCrimsonBoldItalic18) || defined(useAllFonts)
CrimsonBoldItalic18,
#endif

#if defined(useCrimsonBoldItalic24) || defined(useAllFonts)
CrimsonBoldItalic24,
#endif

#if defined(useCrimsonBoldItalic36) || defined(useAllFonts)
CrimsonBoldItalic36,
#endif

#if defined(useCrimsonRoman9) || defined(useAllFonts)
CrimsonRoman9,
#endif

#if defined(useCrimsonRoman12) || defined(useAllFonts)
CrimsonRoman12,
#endif

#if defined(useCrimsonRoman18) || defined(useAllFonts)
CrimsonRoman18,
#endif

#if defined(useCrimsonRoman24) || defined(useAllFonts)
CrimsonRoman24,
#endif

#if defined(useCrimsonRoman36) || defined(useAllFonts)
CrimsonRoman36,
#endif

#if defined(useCrimsonSemiBold9) || defined(useAllFonts)
CrimsonSemiBold9,
#endif

#if defined(useCrimsonSemiBold12) || defined(useAllFonts)
CrimsonSemiBold12,
#endif

#if defined(useCrimsonSemiBold18) || defined(useAllFonts)
CrimsonSemiBold18,
#endif

#if defined(useCrimsonSemiBold24) || defined(useAllFonts)
CrimsonSemiBold24,
#endif

#if defined(useCrimsonSemiBold36) || defined(useAllFonts)
CrimsonSemiBold36,
#endif

#if defined(useCrimsonSemiBoldItalic9) || defined(useAllFonts)
CrimsonSemiBoldItalic9,
#endif

#if defined(useCrimsonSemiBoldItalic12) || defined(useAllFonts)
CrimsonSemiBoldItalic12,
#endif

#if defined(useCrimsonSemiBoldItalic18) || defined(useAllFonts)
CrimsonSemiBoldItalic18,
#endif

#if defined(useCrimsonSemiBoldItalic24) || defined(useAllFonts)
CrimsonSemiBoldItalic24,
#endif

#if defined(useCrimsonSemiBoldItalic36) || defined(useAllFonts)
CrimsonSemiBoldItalic36,
#endif
};
#endif