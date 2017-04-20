#pragma once
#include "../Options.h"
#include <SPI.h>
#include <RA8875.h>

#ifdef useCourier10
#include "Fonts/Courier_10.c"
#endif
#ifdef useCourier14
#include "Fonts/Courier_14.c"
#endif
#ifdef useCourier24
#include "Fonts/Courier_24.c"
#endif
#ifdef useCourier36
#include "Fonts/Courier_36.c"
#endif

#ifdef useCourierB10
#include "Fonts/CourierBold_10.c"
#endif
#ifdef useCourierB14
#include "Fonts/CourierBold_14.c"
#endif
#ifdef useCourierB24
#include "Fonts/CourierBold_24.c"
#endif
#ifdef useCourierB36
#include "Fonts/CourierBold_36.c"
#endif

#ifdef useAlef10
#include "Fonts/Alef_10.c"
#endif
#ifdef useAlef14
#include "Fonts/Alef_14.c"
#endif
#ifdef useAlef24
#include "Fonts/Alef_24.c"
#endif
#ifdef useAlef36
#include "Fonts/Alef_36.c"
#endif

#ifdef useAlefB10
#include "Fonts/AlefB_10.c"
#endif
#ifdef useAlefB14
#include "Fonts/AlefB_14.c"
#endif
#ifdef useAlefB24
#include "Fonts/AlefB_24.c"
#endif
#ifdef useAlefB36
#include "Fonts/AlefB_36.c"
#endif

#ifdef useQuivira10
#include "Fonts/Quivira_10.c"
#endif
#ifdef useQuivira14
#include "Fonts/Quivira_14.c"
#endif
#ifdef useQuivira24
#include "Fonts/Quivira_24.c"
#endif
#ifdef useQuivira36
#include "Fonts/Quivira_36.c"
#endif

#ifdef useQuiviraB10
#include "Fonts/QuiviraB_10.c"
#endif
#ifdef useQuiviraB14
#include "Fonts/QuiviraB_14.c"
#endif
#ifdef useQuiviraB24
#include "Fonts/QuiviraB_24.c"
#endif
#ifdef useQuiviraB36
#include "Fonts/QuiviraB_36.c"
#endif

enum eUITextFont
{
#ifdef useAlef10
	Alef10 = 0,
#endif
#ifdef useAlef14
	Alef14 = 1,
#endif
#ifdef useAlef24
	Alef24 = 2,
#endif
#ifdef useAlef36
	Alef36 = 3,
#endif
#ifdef useAlefB10
	AlefB10 = 4,
#endif
#ifdef useAlefB14
	AlefB14 = 5,
#endif
#ifdef useAlefB24
	AlefB24 = 6,
#endif
#ifdef useAlefB36
	AlefB36 = 7,
#endif
#ifdef useQuivira10
	Quivira10 = 8,
#endif
#ifdef useQuivira14
	Quivira14 = 9,
#endif
#ifdef useQuivira24
	Quivira24 = 10,
#endif
#ifdef useQuivira36
	Quivira36 = 11,
#endif
#ifdef useQuiviraB10
	QuiviraB10 = 12,
#endif
#ifdef useQuiviraB14
	QuiviraB14 = 13,
#endif
#ifdef useQuiviraB24
	QuiviraB24 = 14,
#endif
#ifdef useQuiviraB36
	QuiviraB36 = 15,
#endif
#ifdef useCourier10
	Courier10 = 16,
#endif
#ifdef useCourier14
	Courier14 = 17,
#endif
#ifdef useCourier24
	Courier24 = 18,
#endif
#ifdef useCourier36
	Courier36 = 19,
#endif
#ifdef useCourierB10
	CourierB10 = 20,
#endif
#ifdef useCourierB14
	CourierB14 = 21,
#endif
#ifdef useCourierB24
	CourierB24 = 22,
#endif
#ifdef useCourier36
	CourierB36 = 23,
#endif
#ifdef useDejaVu18
	DejaVu18 = 24,
	DEFAULTFONT = 100
#endif
};

class FontHelper
{
public:
	static void setLCDFont(RA8875 *lcd, eUITextFont font)
	{
		switch (font)
		{
#ifdef useAlef10
		case(Alef10):
			lcd->setFont(&Alef_10);
			return;
#endif
#ifdef useAlef14
		case(Alef14):
			lcd->setFont(&Alef_14);
			return;
#endif
#ifdef useAlef24
		case(Alef24):
			lcd->setFont(&Alef_24);
			return;
#endif
#ifdef useAlef36
		case(Alef36):
			lcd->setFont(&Alef_36);
			return;
#endif
#ifdef useAlefB10
		case(AlefB10):
			lcd->setFont(&AlefB_10);
			return;
#endif
#ifdef useAlefB14
		case(AlefB14):
			lcd->setFont(&AlefB_14);
			return;
#endif
#ifdef useAlefB24
		case(AlefB24):
			lcd->setFont(&AlefB_24);
			return;
#endif
#ifdef useAlefB36
		case(AlefB36):
			lcd->setFont(&AlefB_36);
			return;
#endif
#ifdef useQuivira10
		case(Quivira10):
			lcd->setFont(&Quivira_10);
			return;
#endif
#ifdef useQuivira14
		case(Quivira14):
			lcd->setFont(&Quivira_14);
			return;
#endif
#ifdef useQuivira24
		case(Quivira24):
			lcd->setFont(&Quivira_24);
			return;
#endif
#ifdef useQuivira36
		case(Quivira36):
			lcd->setFont(&Quivira_36);
			return;
#endif
#ifdef useQuiviraB10
		case(QuiviraB10):
			lcd->setFont(&QuiviraB_10);
			return;
#endif
#ifdef useQuiviraB14
		case(QuiviraB14):
			lcd->setFont(&Quivira_14);
			return;
#endif
#ifdef useQuiviraB24
		case(QuiviraB24):
			lcd->setFont(&QuiviraB_24);
			return;
#endif
#ifdef useQuiviraB36
		case(QuiviraB36):
			lcd->setFont(&QuiviraB_36);
			return;
#endif
#ifdef useCourier10
		case(Courier10):
			lcd->setFont(&Courier_10);
			return;
#endif
#ifdef useCourier14
		case(Courier14):
			lcd->setFont(&Courier_14);
			return;
#endif
#ifdef useCourier24
		case(Courier24):
			lcd->setFont(&Courier_24);
			return;
#endif
#ifdef useCourier36
		case(Courier36):
			lcd->setFont(&Courier_36);
			return;
#endif
#ifdef useCourierB10
		case(CourierB10):
			lcd->setFont(&CourierBold_10);
			return;
#endif
#ifdef useCourierB14
		case(CourierB14):
			lcd->setFont(&CourierBold_14);
			return;
#endif
#ifdef useCourierB24
		case(CourierB24):
			lcd->setFont(&CourierBold_24);
			return;
#endif
#ifdef useCourierB36
		case(CourierB36):
			lcd->setFont(&CourierBold_36);
			return;
#endif

		}
	}
};
