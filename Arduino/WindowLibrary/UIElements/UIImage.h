#pragma once
#include <string>
#include <map>
#include <vector>
#include "../Utility/Color.h"
#include "UIElement.h"
#include "../WindowManager/Theme.h"
#include <SPI.h>
#ifdef RA8875 
#include "../External/Adafruit_RA8875/Adafruit_RA8875.h"
#include "RA8875/Fonts.h"
#endif
#ifdef FT8XX
#include "../External/GD3/GD3.h"
#include "FT8XX/Fonts.h"
#endif
#include "../Utility/FontHelper.h"
#include "../Utility/Rectangle.h"
#include "../Images/Image.h"

#ifdef SDENABLED
#include <limits.h>
#include "../External/SDFat/SdFat.h"
#endif

class UIImage : public UIElement
{
public:
	// Define for reading a file from an SD Card
#ifdef SDENABLED
	UIImage(DriverBase &tft, Rectangle location, std::string filename);
#endif
	UIImage(DriverBase &tft, Rectangle locaiton, tImage image);
	void Update() override;
	void SetImage(tImage image)
	{
		imageStruct = image;
		Invalidate();
	}
#ifdef SDENABLED
	void SetImageFilename(std::string imageFilename)
	{
		this->filename = imageFilename;
		Invalidate();
	}
#endif

	sTouchResponse ProcessTouch(Point pt);

private:
#ifdef SDENABLED
	std::string filename;
#endif

	bool isClickable;
	bool errorState = false;		// If we fail to read a file or parse a struct
									// we will put a red x in a box
	uint16_t width, height;
    uint16_t byteToColor(uint8_t bytes[]);
	void displayImgStruct();
	void displayError();
#ifdef SDENABLED
	void displayImgFile();
#endif
	uint16_t Color24To565(int32_t color_) { return ((((color_ >> 16) & 0xFF) / 8) << 11) | ((((color_ >> 8) & 0xFF) / 4) << 5) | (((color_) & 0xFF) / 8); }
	tImage imageStruct;
};
