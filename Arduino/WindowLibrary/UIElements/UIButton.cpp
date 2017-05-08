#include "UIButton.h"

UIButton::UIButton(DriverBase &tft, Rectangle location, std::string boxText,
	Theme &elementTheme, eThemeObjState state) :
	UIElement(tft, location, state)
{
	this->location.update();
	this->buttonText = buttonText;
	defaultTheme = elementTheme.LoadTheme(eThemeObjType::clickable, eThemeObjState::defaultState);
	activeTheme = elementTheme.LoadTheme(eThemeObjType::clickable, eThemeObjState::activeState);	
	loadThemeSettings();
#ifdef DEBUG
	Logger::Trace("UIButton(TFT,(%d,%d,%d,%d),%s,THEME,%d) initalized", location.x1, location.y1,
		location.x2, location.y2, buttonText.c_str(), (int)state);
#endif
}

UIButton::UIButton(DriverBase &tft, Rectangle location, std::string buttonText,
	eUITextFont textFont, uint16_t textColor, uint8_t textScale, uint16_t buttonColor,
	int16_t buttonBorderColor, uint8_t buttonBorderSize, uint16_t buttonActiveColor,
	uint16_t buttonActiveTextColor, uint16_t buttonShadowColor, uint8_t buttonShadowSize,
	uint16_t buttonActiveShadowColor, uint8_t buttonactiveShadowSize, bool buttonPressedOnRelease,
	bool hasRoundCorners, uint8_t cornerRadius) :
	UIElement(tft, location, eThemeObjState::defaultState)
{
	this->location.update();
	this->buttonText = buttonText;
	this->textFont = textFont;
	this->textColor = textColor;	
	this->buttonColor = buttonColor;
	this->buttonBorderColor = buttonBorderColor;
	this->buttonBorderSize = buttonBorderSize;
	this->buttonPressedOnRelease = buttonPressedOnRelease;
	this->buttonActiveColor = buttonActiveColor;
	this->buttonShadowSize = buttonShadowSize;
	this->buttonActiveTextColor = buttonActiveTextColor;
	this->buttonActiveShadowColor = buttonActiveShadowColor;
	this->buttonActiveShadowSize = buttonActiveShadowSize;
	this->cornerRadius = cornerRadius;
	this->hasRoundCorners = hasRoundCorners;
	this->textScale = textScale;
#ifdef DEBUG
	Logger::Trace("UIButton(TFT,(%d,%d,%d,%d),%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%d) initalized",
		location.x1, location.y1, location.x2, location.y2, buttonText.c_str(), (int)textFont,
		textColor, buttonColor, buttonBorderColor, buttonBorderSize, buttonActiveColor, buttonActiveTextColor,
		buttonShadowColor, buttonShadowSize, buttonActiveShadowColor, buttonActiveShadowSize, Logger::BoolToStr(buttonPressedOnRelease).c_str(),
		Logger::BoolToStr(hasRoundCorners).c_str(),cornerRadius);
	Logger::Trace("Active Shadow Size: %d, Shadow Size: %d", buttonActiveShadowSize, buttonShadowSize);
#endif
}

void UIButton::loadThemeSettings()
{
	textFont = defaultTheme.textFont;
	textColor = defaultTheme.textColor;
	buttonColor = defaultTheme.bgColor;
	buttonBorderColor = defaultTheme.borderColor;
	buttonBorderSize = defaultTheme.borderSize;
	buttonPressedOnRelease = defaultTheme.activeOnRelease;
	buttonActiveColor = activeTheme.bgColor;
	buttonActiveTextColor = activeTheme.bgColor;
	buttonShadowColor = defaultTheme.shadowColor;
	buttonShadowSize = defaultTheme.shadowThickness;
	buttonActiveShadowColor = activeTheme.shadowColor;
	buttonActiveShadowSize = activeTheme.shadowThickness;
	textScale = activeTheme.textScale;
	if (defaultTheme.cornerType == eCornerType::Rounded)
		hasRoundCorners = true;
	else
		hasRoundCorners = false;
	cornerRadius = defaultTheme.cornerRadius;
}

void UIButton::Update()
{
	if (!updatePending)
	{
#ifdef DEBUG
		Logger::Trace("No update pending, exiting");
#endif
		return;
	}
	tft.setTextSize(textScale);
	// Draw shadow
	uint16_t shadowColor = buttonShadowColor;
	uint8_t shadowSize = buttonShadowSize;
	if (objectThemeState == eThemeObjState::activeState)
	{
		shadowColor = buttonActiveShadowColor;
		shadowSize = buttonActiveShadowSize;
	}
#ifdef DEBUG
	Logger::Trace("Drawing UIButton.  Location(%d,%d,%d,%d)", location.x1, location.y1, location.x2, location.y2);
	Logger::Trace("Shadow Color: %d, Shadow Size: %d, borderSize: %d", shadowColor, shadowSize, buttonBorderSize);
#endif

	int x1 = location.x1 + shadowSize;
	int y1 = location.y1 + shadowSize;
	int x2 = location.width;
	int y2 = location.height;
	
#ifdef DEBUG
	Logger::Trace("Drawing shadow box: (%d,%d,%d,%d)", x1, y1, x2, y2);
#endif
	if (hasRoundCorners)
	{	
		tft.fillRoundRect(x1,y1,x2,y2,cornerRadius, shadowColor);
	}
	else
	{
		tft.fillRect(x1,y1,x2,y2,shadowColor);
	}
	// Next draw bg color
	uint16_t color = buttonColor;
	if (objectThemeState == eThemeObjState::activeState)
		color = buttonActiveColor;

	if (hasRoundCorners)
	{
		tft.fillRoundRect(location.x1, location.y1 ,
			location.width, location.height,
			cornerRadius, color);
	}
	else
	{
		tft.fillRect(location.x1, location.y1,
			location.width, location.height,
			color);
	}
	// Draw border
	x1 = location.x1;
	y1 = location.y1;
	y2 = location.height;
	x2 = location.width;

	if (hasRoundCorners)
	{
		for (int a = 0; a < borderSize; a++)
		{
			tft.drawRoundRect(x1+a, y1+a,
				x2-a*2, y2-a*2,
				cornerRadius, buttonBorderColor);
		}
	} else
	{ 
		for (int a = 0; a < borderSize; a++)
		{
			tft.drawRect(x1 + a, y1 + a,
				x2 - a*2, y2 - a*2,
				buttonBorderColor);
		}
	}

	// Finally draw the text
	color = textColor;
	if (objectThemeState == eThemeObjState::activeState)
		color = buttonActiveTextColor;

	if (textLocation == NULL)
	{
		Rectangle r = FontHelper::GetTextRect(tft, buttonText, textFont, Point(0, 0));
#ifdef DEBUG
		Logger::Trace("Text Rect (%d,%d,%d,%d)", r.x1, r.y1, r.x2, r.y2);
		Logger::Trace("Location Rect (%d,%d,%d,%d)", location.x1, location.y1, location.x2, location.y2);
		Logger::Trace("Location Center(%d,%d)", location.center.x, location.center.y);
#endif
		uint16_t startX = location.center.x-(r.width/2);
		uint16_t startY = location.center.y-(r.height/2);
textLocation = new Point(startX, startY);
#ifdef DEBUG
		Logger::Trace("Text Location (%d,%d)", textLocation->x, textLocation->y);
#endif
	}
	tft.textWrite(textLocation->x, textLocation->y, textFont, textColor, 0, buttonText);
	updatePending = false;
}

void UIButton::SetButtonText(std::string buttonText)
{
	this->buttonText = buttonText;
	if (textLocation != NULL)
		delete textLocation;
	Invalidate();
}

sTouchResponse UIButton::ProcessTouch(Point touchPoint)
{
	if (!this->enabled)
		return sTouchResponse(this->elementID, eTouchResponse::NoOp);
	if (!location.contains(touchPoint))
		return sTouchResponse(this->elementID, eTouchResponse::NoOp);
	if (!buttonPressedOnRelease)
	{
		return sTouchResponse(this->elementID, eTouchResponse::ControlTouched);
	}
	SetObjectState(eThemeObjState::activeState);
	uint8_t counter=0;
	uint16_t x, y;
	while (location.contains(touchPoint) && counter < 50)
	{
		delay(5);
		if (tft.touched())
		{
			tft.touchRead(&x, &y);
			touchPoint.x = x;
			touchPoint.y = y;
		}
		else
		{
			return sTouchResponse(this->elementID, eTouchResponse::ControlTouched);
		}
		counter++;
	}
	return sTouchResponse(this->elementID, eTouchResponse::ControlTouched);
}

UIButton::~UIButton()
{
	if (textLocation != NULL)
		delete(textLocation);
}
