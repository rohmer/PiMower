#pragma once
// define if you want debug printing to the Serial port
#define DEBUG

// Define which controller you are going to use.  Uncomment one of these
//#define FT_800
//#define FT_801
//#define FT_810
//#define FT_811
#define FT_812
//#define FT_813
//#define RA8875

#ifdef FT_800
#define FT_800_ENABLE		1
#define FT8XX
#else
#define FT_800_ENABLE		0
#endif
#ifdef FT_801
#define FT_801_ENABLE		1
#define FT8XX
#else
#define FT8XX
#endif
#ifdef FT_810
#define FT8XX
#define FT_810_ENABLE		1
#else
#define FT_810_ENABLE		0
#endif
#ifdef FT_811
#define FT8XX
#define FT_811_ENABLE		1
#else
#define FT_811_ENABLE		0
#endif
#ifdef FT_812
#define FT8XX
#define FT_812_ENABLE		1
#else
#define FT_812_ENABLE		0
#endif
#ifdef FT_813
#define FT8XX
#define FT_813_ENABLE		1
#else
#define FT_813_ENABLE		0
#endif

#if defined(FT_810) || defined(FT_811) || defined(FT_812) || defined(FT_813)
#define FT81X
#endif

// ATM this is the same as ifndef FT81X, but who knows if/when there will be a FT820
#if defined(FT_800) || defined(FT_801)
#define FT80X
#endif

#ifdef RA8875
#define USE_RA8875_TOUCH
#endif

// Will remove logging, otherwise the logging is set to WARNING
#define NOLOGGING

#ifndef NOLOGGING
	#define DEBUG_ENABLED
#endif

// Will include code for reading off SD card, right now for images
//#define SDENABLED

// The following defines will use all fonts from a specific pt size
// Using a smaller point size saves memory, you can expand them but it can get blocky
//#define use9PtFonts
//#define use12PtFonts
//#define use18PtFonts
//#define use24PtFonts
//#define use36PtFonts

// This is the default font, you really shouldnt remove this
#define useAileronRegular12

#ifdef use9PtFonts
#define useAileronBlack9
#define useAileronBlackItalic9
#define useAileronBold9
#define useAileronBoldItalic9
#define useAileronHeavyItalic9
#define useAileronHeavy9
#define useAileronLight9
#define useAileronRegular9
#define useAileronSemiBold9
#define useAileronSemiBoldItalic9
#define useAileronThin9
#define useAileronThinItalic9
#define useAileronUltraLight9
#define useAileronUltraLightItalic9
#define useCourierPrime9
#define useCourierPrimeBold9
#define useCourierPrimeBoldItalic9
#define useCrimsonItalic9
#define useCrimsonRoman9
#define useCrimsonSemiBold9
#define useCrimsonSemiBoldItalic9
#endif

#ifdef use12PtFonts
#define useAileronBlack12
#define useAileronBlackItalic12
#define useAileronBold12
#define useAileronBoldItalic12
#define useAileronHeavyItalic12
#define useAileronHeavy12
#define useAileronLight12
#define useAileronRegular12
#define useAileronSemiBold12
#define useAileronSemiBoldItalic12
#define useAileronThin12
#define useAileronThinItalic12
#define useAileronUltraLight12
#define useAileronUltraLightItalic12
#define useCourierPrime12
#define useCourierPrimeBold12
#define useCourierPrimeBoldItalic12
#define useCrimsonItalic12
#define useCrimsonRoman12
#define useCrimsonSemiBold12
#define useCrimsonSemiBoldItalic12
#endif

#ifdef use18PtFonts
#define useAileronBlack18
#define useAileronBlackItalic18
#define useAileronBold18
#define useAileronBoldItalic18
#define useAileronHeavyItalic18
#define useAileronHeavy18
#define useAileronLight18
#define useAileronRegular18
#define useAileronSemiBold18
#define useAileronSemiBoldItalic18
#define useAileronThin18
#define useAileronThinItalic18
#define useAileronUltraLight18
#define useAileronUltraLightItalic18
#define useCourierPrime18
#define useCourierPrimeBold18
#define useCourierPrimeBoldItalic18
#define useCrimsonItalic18
#define useCrimsonRoman18
#define useCrimsonSemiBold18
#define useCrimsonSemiBoldItalic18
#endif

#ifdef use24PtFonts
#define useAileronBlack24
#define useAileronBlackItalic24
#define useAileronBold24
#define useAileronBoldItalic24
#define useAileronHeavyItalic24
#define useAileronHeavy24
#define useAileronLight24
#define useAileronRegular24
#define useAileronSemiBold24
#define useAileronSemiBoldItalic24
#define useAileronThin24
#define useAileronThinItalic24
#define useAileronUltraLight24
#define useAileronUltraLightItalic24
#define useCourierPrime24
#define useCourierPrimeBold24
#define useCourierPrimeBoldItalic24
#define useCrimsonItalic24
#define useCrimsonRoman24
#define useCrimsonSemiBold24
#define useCrimsonSemiBoldItalic24
#endif

#ifdef use36PtFonts
#define useAileronBlack36
#define useAileronBlackItalic36
#define useAileronBold36
#define useAileronBoldItalic36
#define useAileronHeavyItalic36
#define useAileronHeavy36
#define useAileronLight36
#define useAileronRegular36
#define useAileronSemiBold36
#define useAileronSemiBoldItalic36
#define useAileronThin36
#define useAileronThinItalic36
#define useAileronUltraLight36
#define useAileronUltraLightItalic36
#define useCourierPrime36
#define useCourierPrimeBold36
#define useCourierPrimeBoldItalic36
#define useCrimsonItalic36
#define useCrimsonRoman36
#define useCrimsonSemiBold36
#define useCrimsonSemiBoldItalic36
#endif

#ifndef useAllFonts
// Optional fonts, if one is not selected and you arent using it you will get a compile time error
//	#define useAileronBlack9
//	#define useAileronBlack12
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
//	#define useAileronRegular12
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
//	#define useCourierPrime12
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
//	#define useCrimsonRoman12
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

#undef abs