#include "../../Options.h"
#ifdef RA8875

#include "UIText.h"

UIText::UIText(Adafruit_RA8875 &tft, Rectangle location, std::string text, 
	Theme &elementTheme, eThemeObjState state) :
	UIElement(tft, location, state)
{
	this->theme = elementTheme;
	this->text = text;	
	themeSettings = elementTheme.LoadTheme(eThemeObjType::clickable, state);
	textScale = themeSettings.textScale;
	textColor = themeSettings.textColor;
	textFont = themeSettings.textFont;
	setButtonLines();
	Logger::Trace("UIText((%d,%d,%d,%d),%s) created", location.x1, location.y1,
		location.x2, location.y2, text.c_str());
	updatePending = true;
}

UIText::UIText(Adafruit_RA8875 &tft, Rectangle location, std::string text, eThemeObjState state,
	eUITextFont textFont, uint8_t textScale, uint16_t textColor) :
	UIElement(tft,location,state)
{
	this->text = text;
	this->textScale = textScale;
	this->textColor = textColor;
	this->textFont = textFont;
	setButtonLines();
	Logger::Trace("UIText((%d,%d,%d,%d),%s,%d,%d,%d,%d) created", location.x1, location.y1,
		location.x2, location.y2, text.c_str(),state,textFont,textScale,textColor);
	updatePending = true;
}

void UIText::setButtonLines()
{
	textLines.clear();	
	std::string::size_type pos = 0;
	std::string::size_type prev = 0;
	while((pos=text.find('\n',prev))!=std::string::npos)
	{
		std::string token = text.substr(prev, pos - prev);
#ifdef DEBUG
		Logger::Trace("Adding: %s to line list", token.c_str());
#endif
		textLines.push_back(token);
	}
	
	textLines.push_back(text.substr(prev));
#ifdef DEBUG
	std::string s = text.substr(prev);
	Logger::Trace("Adding: %s to line list", s.c_str());
#endif

}

void UIText::Update()
{
	if (!updatePending)
		return;
	tft.setTextSize(this->textScale);	
#ifdef DEBUG
	Logger::Trace("Writing text: %s to (%d,%d)", text.c_str(), 
		location.x1, location.y1);
	Logger::Trace("Text Scale: %d", this->textScale);
	Logger::Trace("Text Color: %d", this->textColor);
#endif
	FontHelper::setLCDFont(tft, this->textFont);
	tft.setTextColor(this->textColor);
	tft.setCursor(location.x1, location.y1);
	tft.print(text.c_str());
	Logger::Trace("Writing \"%s\" at (%d,%d)", text.c_str(), location.x1, location.y1);
	
	updatePending= false;
}

void UIText::SetText(std::string text)
{
	this->text = text;
	setButtonLines();
	location = FontHelper::GetTextRect(tft, text, themeSettings.textFont, Point(location.x1, location.y1));
}


uint8_t UIText::getFontHeight()
{
	uint8_t c;
	char *testStr = "ABCDEFG";
	uint16_t _width = tft.width();
	uint16_t _height = tft.height();
	GFXfont *font=tft.getFont();
	GFXglyph *glyph;
	uint8_t   first = pgm_read_byte(&font->first),
		last = pgm_read_byte(&font->last),
		gw, gh, xa;
	int x = 0, y = 0;
	int8_t    xo, yo;
	int16_t   minx = _width, miny = _height, maxx = -1, maxy = -1,
		gx1, gy1, gx2, gy2, ts = tft.getTextSize(),
		ya = ts * (uint8_t)pgm_read_byte(&font->yAdvance);

	while ((c = *testStr++)) {
		if (c != '\n') { // Not a newline
			if (c != '\r') { // Not a carriage return, is normal char
				if ((c >= first) && (c <= last)) { // Char present in current font
					c -= first;
					glyph = &(((GFXglyph *)pgm_read_pointer(&font->glyph))[c]);
					gw = pgm_read_byte(&glyph->width);
					gh = pgm_read_byte(&glyph->height);
					xa = pgm_read_byte(&glyph->xAdvance);
					xo = pgm_read_byte(&glyph->xOffset);
					yo = pgm_read_byte(&glyph->yOffset);
					gx1 = x + xo * ts;
					gy1 = y + yo * ts;
					gx2 = gx1 + gw * ts - 1;
					gy2 = gy1 + gh * ts - 1;
					if (gx1 < minx) minx = gx1;
					if (gy1 < miny) miny = gy1;
					if (gx2 > maxx) maxx = gx2;
					if (gy2 > maxy) maxy = gy2;
					x += xa * ts;
				}
			} // Carriage return = do nothing
		}
		else { // Newline
			x = 0;  // Reset x
			y += ya; // Advance y by 1 line
		}
	}

	return maxy;
}

sTouchResponse UIText::ProcessTouch(Point touchPoint)
{
	// Text cannot be interacted with, so this is an automatic NoOp
	return sTouchResponse(this->elementID, eTouchResponse::NoOp);
}

#endif