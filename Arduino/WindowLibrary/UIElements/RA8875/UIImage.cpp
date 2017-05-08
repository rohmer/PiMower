#include "UIImage.h"
#include "../../Options.h"
#ifdef RA8875

#ifdef SDENABLED
UIImage::UIImage(Adafruit_RA8875 &tft, Rectangle location, std::string filename)
	: UIElement(tft, location, eThemeObjState::defaultState)
{
	this->filename = filename;
	this->isClickable = false;
	this->width = location.width;
	this->height = location.height;
}
#endif

UIImage::UIImage(Adafruit_RA8875 &tft, Rectangle location, tImage image)
	: UIElement(tft, location, eThemeObjState::defaultState)
{
	this->filename = "";
	this->isClickable = false;
	this->width = location.width;
	this->height = location.height;
	imageStruct = image;
}

void UIImage::Update()
{
	if (!updatePending)
	{
#ifdef DEBUG
		Logger::Trace("No update pending");
#endif
		return;
	}

	displayImgStruct();
	
}

sTouchResponse UIImage::ProcessTouch(Point pt)
{
	if (!isClickable)
		return sTouchResponse(this->elementID, eTouchResponse::NoOp);
	if (this->location.contains(pt))
		return sTouchResponse(this->elementID, eTouchResponse::ControlTouched);
	return sTouchResponse(this->elementID, eTouchResponse::NoOp);
}

void UIImage::displayImgStruct()
{	
	uint8_t bytes[2];	
	uint16_t color;
	for (int y = 0; y < this->height; y++)
	{
		for (int x = 0; x < this->width; x++)
		{			
			color = Color24To565(imageStruct.data[y*width+x]);		
			tft.drawPixel(x+location.x1, y+location.y1, color);
		}
	}
}

void UIImage::displayImgFile()
{
	//TODO: Actually write this :)
}

void UIImage::displayError()
{
	// Draw black background
	tft.fillRect(location.x1, location.y1, location.width, location.height, Color::Black);
	// Draw box
	for (int i = 0; i < 5; i++)
	{
		tft.drawRect(location.x1 + i, location.y1 + i, location.width - i, location.height - i, Color::Red);
	}

	// Draw Lines
	for (int i = 0; i < 3; i++)
	{
		tft.drawLine(location.x1 + i, location.y1, location.x2, location.y2 - i, Color::Red);
		tft.drawLine(location.x1, location.y1 - i, location.x2 - i, location.y2, Color::Red);
		tft.drawLine(location.x2 - i, location.y1, location.x1, location.y2 - i, Color::Red);
		tft.drawLine(location.x2, location.y1 + i, location.x1 + i, location.y2, Color::Red);
	}
}

uint16_t UIImage::byteToColor(uint8_t bytes[])
{
	return ((uint16_t)bytes[0] | bytes[1]<<8);	
}

#endif