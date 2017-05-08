#pragma once
// define if you want debug printing to the Serial port
#define DEBUG

// Will remove logging, otherwise the logging is set to WARNING
#define NOLOGGING

#ifndef NOLOGGING
	#define DEBUG_ENABLED
#endif

#ifndef useAllFonts
// Optional fonts, if one is not selected and you arent using it you will get a compile time error
//	#define useAileronBlack9
	#define useAileronBlack12
//	#define useAileronBlack18
//	#define useAileronBlack24
//	#define useAileronBlack36
//	#define useAileronBlackItalic9
//	#define useAileronBlackItalic12
//	#define useAileronBlackItalic18
//	#define useAileronBlackItalic24
//	#define useAileronBlackItalic36
//	#define useAileronBold9
//	#define useAileronBold12
//	#define useAileronBold18
//	#define useAileronBold24
//	#define useAileronBold36
//	#define useAileronBoldItalic9
//	#define useAileronBoldItalic12
//	#define useAileronBoldItalic18
//	#define useAileronBoldItalic24
//	#define useAileronBoldItalic36
//	#define useAileronHeavyItalic9
//	#define useAileronHeavyItalic12
//	#define useAileronHeavyItalic18
//	#define useAileronHeavyItalic24
//	#define useAileronHeavyItalic36
//	#define useAileronHeavy9
//	#define useAileronHeavy12
//	#define useAileronHeavy18
//	#define useAileronHeavy24
//	#define useAileronHeavy36
//	#define useAileronLight9
//	#define useAileronLight12
//	#define useAileronLight18
//	#define useAileronLight24
//	#define useAileronLight36
//	#define useAileronRegular9
	#define useAileronRegular12
//	#define useAileronRegular18
//	#define useAileronRegular24
//	#define useAileronRegular36
//	#define useAileronSemiBold9
//	#define useAileronSemiBold12
//	#define useAileronSemiBold18
//	#define useAileronSemiBold24
//	#define useAileronSemiBold36
//	#define useAileronSemiBoldItalic9
//	#define useAileronSemiBoldItalic12
//	#define useAileronSemiBoldItalic18
//	#define useAileronSemiBoldItalic24
//	#define useAileronSemiBoldItalic36
//	#define useAileronThin9
//	#define useAileronThin12
//	#define useAileronThin18
//	#define useAileronThin24
//	#define useAileronThin36
//	#define useAileronThinItalic9
//	#define useAileronThinItalic12
//	#define useAileronThinItalic18
//	#define useAileronThinItalic24
//	#define useAileronThinItalic36
//	#define useAileronUltraLight9
//	#define useAileronUltraLight12
//	#define useAileronUltraLight18
//	#define useAileronUltraLight24
//	#define useAileronUltraLight36
//	#define useAileronUltraLightItalic9
//	#define useAileronUltraLightItalic12
//	#define useAileronUltraLightItalic18
//	#define useAileronUltraLightItalic24
//	#define useAileronUltraLightItalic36
//	#define useCourierPrime9
	#define useCourierPrime12
//	#define useCourierPrime18
//	#define useCourierPrime24
//	#define useCourierPrime36
//	#define useCourierPrimeBold9
//	#define useCourierPrimeBold12
//	#define useCourierPrimeBold18
//	#define useCourierPrimeBold24
//	#define useCourierPrimeBold36
//	#define useCourierPrimeBoldItalic9
//	#define useCourierPrimeBoldItalic12
//	#define useCourierPrimeBoldItalic18
//	#define useCourierPrimeBoldItalic24
//	#define useCourierPrimeBoldItalic36
//	#define useCourierPrimeItalic9
//	#define useCourierPrimeItalic12
//	#define useCourierPrimeItalic18
//	#define useCourierPrimeItalic24
//	#define useCourierPrimeItalic36
//	#define useCrimsonBold9
//	#define useCrimsonBold12
//	#define useCrimsonBold18
//	#define useCrimsonBold24
//	#define useCrimsonBold36
//	#define useCrimsonBoldItalic9
//	#define useCrimsonBoldItalic12
//	#define useCrimsonBoldItalic18
//	#define useCrimsonBoldItalic24
//	#define useCrimsonBoldItalic36
//	#define useCrimsonItalic9
//	#define useCrimsonItalic12
//	#define useCrimsonItalic18
//	#define useCrimsonItalic24
//	#define useCrimsonItalic36
//	#define useCrimsonRoman9
	#define useCrimsonRoman12
//	#define useCrimsonRoman18
//	#define useCrimsonRoman24
//	#define useCrimsonRoman36
//	#define useCrimsonSemiBold9
//	#define useCrimsonSemiBold12
//	#define useCrimsonSemiBold18
//	#define useCrimsonSemiBold24
//	#define useCrimsonSemiBold36
//	#define useCrimsonSemiBoldItalic9
//	#define useCrimsonSemiBoldItalic12
//	#define useCrimsonSemiBoldItalic18
//	#define useCrimsonSemiBoldItalic24
//	#define useCrimsonSemiBoldItalic36
#endif

//TODO: IFDEF enable all UIElements except windows
#define useButtons
#define useText