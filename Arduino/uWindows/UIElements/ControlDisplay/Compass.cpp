#include "Compass.h"

Rectangle Compass::Draw(DriverBase &tft, Rectangle location, float direction,
	tColor controlColor, tColor pointerColor, eUITextFont controlFont,
	bool showDegrees, eUITextFont degreeFont, tColor degreeColor, tColor degreeBGColor,
	bool showNSEW = true, tColor textColor=Color::White)
{	
	uint16_t shownDirection = angleMath(direction, -15);	

	// We need to draw the compass control static part first
	// We start with a square that is the smaller of the width/height
	uint16_t cSize = Min(location.width, location.height);
	Point centerPoint = location.center();
	uint8_t lineWidth = Max(cSize / 20, 2);
	uint8_t centerCircle = Max(cSize / 12, 5);
	tColor controlColor2 = Color::ContrastingColor(controlColor);
	uint16_t starLength = location.width / 2 - centerCircle / 2;

	if (showNSEW)
	{
		uint8_t fontSize = FontHelper::GetTextRect(tft, "NSEW", controlFont, Point(0, 0)).height;
		starLength -= fontSize;
		UIPrimitives::Text(tft, textColor, 255, centerPoint.x, location.y1 + fontSize/2, controlFont, true, "N");
		UIPrimitives::Text(tft, textColor, 255, centerPoint.x, location.y2 - fontSize*1.5, controlFont, true, "S");
		UIPrimitives::Text(tft, textColor, 255, location.x1 + fontSize, centerPoint.y-fontSize/2, controlFont, true, "W");
		UIPrimitives::Text(tft, textColor, 255, location.x2 - fontSize, centerPoint.y-fontSize/2, controlFont, true, "E");
	}
	Logger::Trace("Angle: %d", direction);
	UIPrimitives::CircleFlat(tft, controlColor, 255, centerPoint.x, centerPoint.y, centerCircle);
	UIPrimitives::CircleFlat(tft, controlColor2, 255, centerPoint.x, centerPoint.y, centerCircle/2);
	for(int a=0; a<=7; a++)
		DrawCompassTriangle(tft, static_cast<eAngle>(a), centerPoint, starLength, centerCircle, controlColor, controlColor2);

	// Now draw the pointer
	std::vector<Point> pts;
	pts.push_back(centerPoint);
	
	Point pt;
	uint16_t l1 = starLength*0.2;
	uint16_t l2 = starLength*1.15;
	direction = angleMath(shownDirection, -90);
	pt.x = centerPoint.x + cos(degrees_to_radian(angleMath(direction, 45)))*l1;
	pt.y = centerPoint.y + sin(degrees_to_radian(angleMath(direction, 45)))*l1;
	pts.push_back(pt);

	pt.x = centerPoint.x + cos(degrees_to_radian(direction))*l2;
	pt.y = centerPoint.x + sin(degrees_to_radian(direction))*l2;
	pts.push_back(pt);

	pt.x = centerPoint.x + cos(degrees_to_radian(angleMath(direction, -45)))*l1;
	pt.y = centerPoint.y + sin(degrees_to_radian(angleMath(direction, -45)))*l1;
	pts.push_back(pt);
	UIPrimitives::Polygon(tft, pts, pointerColor, 255);

	// Show degrees 
	if (showDegrees)
	{
		Rectangle textBox = FontHelper::GetTextRect(tft, "999", degreeFont, Point(0, 0));
		Logger::Trace("Textbox, width: %d, height: %d", textBox.width, textBox.height);
		uint16_t panelX, panelY, panelWidth, panelHeight;
		panelX = location.center().x - textBox.width / 1.5;
		panelY = location.center().y - textBox.height / 1.5;
		panelHeight = textBox.height * 2;
		panelWidth = textBox.width * 2;
		Logger::Trace("(%d,%d), Width: %d, Height: %d", panelX, panelY,
			panelWidth, panelHeight);

		GD.Begin(RECTS);
		GD.LineWidth(2 * 16);
		GD.ColorRGB(degreeBGColor);
		GD.Vertex2f(panelX * 16, panelY * 16);
		GD.Vertex2f((panelX + panelWidth) * 16, (panelY + panelHeight) * 16);

		//UIPrimitives::FlatPanel(tft, panelX,panelY,panelWidth,panelHeight, 2, degreeBGColor,255);
		std::stringstream degrees;
		degrees << direction;
		UIPrimitives::Text(tft, degreeColor, 255, centerPoint.x - textBox.width / 1.5, centerPoint.y - textBox.height / 1.5, degreeFont, true, degrees.str());
	}
}

void Compass::DrawCompassTriangle(DriverBase &tft, eAngle angle, Point centerPoint, 
	uint16_t length, uint16_t centerRadius, tColor color1, tColor color2)
{
	uint16_t centerAngle;
	switch(angle)
	{ 
	case(eAngle::N):
		centerAngle = 0;
		break;
	case(eAngle::E):
		centerAngle = 90;
		break;
	case(eAngle::S):
		centerAngle = 180;
		break;
	case(eAngle::W):
		centerAngle = 270;
		break;
	case(eAngle::NE):
		centerAngle = 45;
		break;
	case(eAngle::SE):
		centerAngle = 135;
		break;
	case(eAngle::SW):
		centerAngle = 225;
		break;
	case(eAngle::NW):
		centerAngle = 315;
		break;
	}
	Point pt2, pt2a, pt3;
	Point pt1(centerPoint.x + cos(degrees_to_radian(centerAngle))*centerRadius, centerPoint.y + sin(degrees_to_radian(centerAngle))*centerRadius);
	if (angle == eAngle::E || angle == eAngle::S ||
		angle == eAngle::W || angle == eAngle::N)
	{
		uint16_t l1 = length*0.25;
		pt2.x = pt1.x + cos(degrees_to_radian(angleMath(centerAngle, 45)))*l1;
		pt2.y = pt1.y + sin(degrees_to_radian(angleMath(centerAngle, 45)))*l1;
		pt2a.x = pt1.x + cos(degrees_to_radian(angleMath(centerAngle, -45)))*l1;
		pt2a.y=pt1.y + sin(degrees_to_radian(angleMath(centerAngle, -45)))*l1;
		pt3.x = pt1.x + cos(degrees_to_radian(centerAngle))*(length - l1);
		pt3.y=pt1.y + sin(degrees_to_radian(centerAngle))*(length - l1);
	}
	else
	{
		// The midpoints are a smaller star
		uint16_t l1 = length*0.15;
		pt2.x = pt1.x + cos(degrees_to_radian(angleMath(centerAngle, 45)))*l1;
		pt2.y = pt1.y + sin(degrees_to_radian(angleMath(centerAngle, 45)))*l1;
		pt2a.x = pt1.x + cos(degrees_to_radian(angleMath(centerAngle, -45)))*l1;
		pt2a.y = pt1.y + sin(degrees_to_radian(angleMath(centerAngle, -45)))*l1;
		pt3.x = pt1.x + cos(degrees_to_radian(centerAngle))*l1*3;
		pt3.y = pt1.y + sin(degrees_to_radian(centerAngle))*l1*3;
	}
	std::vector<Point> pts;
	pts.push_back(pt1);
	pts.push_back(pt2);
	pts.push_back(pt3);	
	UIPrimitives::Polygon(tft, pts, color1, 255);	
	pts.clear();
	pts.push_back(pt1);
	pts.push_back(pt2a);
	pts.push_back(pt3);
	UIPrimitives::Polygon(tft, pts, color2, 255);

}

uint16_t Compass::angleMath(uint16_t startAngle, int adjustment)
{
	startAngle += adjustment;
	if (startAngle < 0)
		startAngle += 360;
	if (startAngle > 360)
		startAngle -= 360;
	return startAngle;
}