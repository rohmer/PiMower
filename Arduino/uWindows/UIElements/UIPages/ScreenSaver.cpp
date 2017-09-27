#include "ScreenSaver.h"

ScreenSaver::ScreenSaver(DriverBase &tft) :
	UIElement(tft,Rectangle(0,0,tft.width(), tft.height()),"Screen Saver", eElementType::Page)
{
	draw();
}

void ScreenSaver::draw()
{
	tft.clearScreen();
	uint16_t x, y, color;
	x = random(0, 400);
	y = random(0, 400);
	color = random(0, 8);
	uint32_t color32 = Color::White;
	switch (color)
	{
	case 0:
		color32 = Color::White;
		break;
	case 1:
		color32 = Color::Aqua;
		break;
	case 2:
		color32 = Color::Beige;
		break;
	case 3:
		color32 = Color::Blue;
		break;
	case 4:
		color32 = Color::BlueViolet;
		break;
	case 5:
		color32 = Color::Crimson;
		break;
	case 6:
		color32 = Color::Green;
		break;
	case 7:
		color32 = Color::GreenYellow;
		break;
	case 8:
		color32 = Color::Yellow;
		break;
	}
	GD.ColorA(255);
	GD.ColorRGB(color32);
	GD.cmd_text(x, y, eUITextFont::AntiAliasFont31, 0, "PiMower V1.0");	
	tft.swapDisplay();
	updateTime = millis() + 5000;
}

void ScreenSaver::Update()
{
	if (millis() > updateTime)
		draw();
}

sTouchResponse ScreenSaver::ProcessTouch(Point touchPoint)
{
	return sTouchResponse(this->elementID, eTouchResponse::CloseControl);
}