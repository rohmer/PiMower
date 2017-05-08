#include "../../Options.h"
#ifdef RA8875
#include "UIAlphaNumericEditor.h"

UIAlphaNumericEditor::UIAlphaNumericEditor(DriverBase &tft, Theme &elementTheme, std::string editorText) :
	UIElement(tft, Rectangle(0, 0, 0, 0), eThemeObjState::defaultState)
{
	this->editorText = editorText;
	sThemeSettings theme = elementTheme.LoadTheme(eThemeObjType::clickable, eThemeObjState::defaultState);

	this->textFont = theme.textFont;
	this->textColor = theme.textColor;
	this->buttonBGColor = theme.bgColor;
	this->chromeColor = theme.borderColor;
	this->borderSize = theme.borderSize;
	this->shadowColor = theme.shadowColor;
	this->shadowSize = theme.shadowThickness;

	tftWidth = tft.width();
	tftHeight = tft.height();
	tftRotation = tft.getRotation();

#ifdef DEBUG
	Logger::Trace("UIAlphaNumeric(%s): textFont: %d, textColor: %d, buttonBGColor: %d, chromeColor: %d, borderSize: %d, shadowColor: %d, shadowSize: %d",
		editorText.c_str(), textFont, textColor, buttonBGColor, chromeColor, borderSize, shadowColor, shadowSize);
#endif
	location.x1 = 0;
	location.y1 = tftHeight / 2;
	location.x2 = tftWidth;
	location.y2 = tftHeight;
#ifdef DEBUG
	Logger::Trace("Location (%d,%d,%d,%d)", location.x1, location.y1, location.x2, location.y2);
#endif
	Invalidate();
	setupScreenKeys();
}

UIAlphaNumericEditor::UIAlphaNumericEditor(Adafruit_RA8875 &tft, std::string editorText, eUITextFont textFont,
	uint16_t textColor, uint16_t buttonBGColor, uint16_t chromeColor, uint8_t borderSize,
	uint16_t shadowColor, uint8_t shadowSize, uint8_t textScale) :
	UIElement(tft, Rectangle(0, 0, 0, 0), eThemeObjState::defaultState)
{
	this->textFont = textFont;
	this->textColor = textColor;
	this->buttonBGColor = buttonBGColor;
	this->chromeColor = chromeColor;
	this->borderSize = borderSize;
	this->shadowColor = shadowColor;
	this->shadowSize = shadowSize;
	this->textScale = textScale;

	tftWidth = tft.width();
	tftHeight = tft.height();
	tftRotation = tft.getRotation();
#ifdef DEBUG
	Logger::Trace("UIAlphaNumeric(%s): textFont: %d, textColor: %d, buttonBGColor: %d, chromeColor: %d, borderSize: %d, shadowColor: %d, shadowSize: %d",
		editorText.c_str(), textFont, textColor, buttonBGColor, chromeColor, borderSize, shadowColor, shadowSize);
#endif
	location.x1 = 0;
	location.y1 = tftHeight / 2;
	location.x2 = tftWidth;
	location.y2 = tftHeight;
#ifdef DEBUG
	Logger::Trace("Location (%d,%d,%d,%d)", location.x1, location.y1, location.x2, location.y2);
#endif
	Invalidate();
	setupScreenKeys();
}

void UIAlphaNumericEditor::Update()
{
	if (!updatePending)
	{
#ifdef DEBUG
		Logger::Trace("Update not needed");
#endif
		return;
	}

	sKeyboard displayKeyboard;
	switch(currentKeyboard)
	{
		case(eKeyboards::normal):
			displayKeyboard = keyboards[0];
			break;
		case(eKeyboards::shifted):
			displayKeyboard = keyboards[1];
			break;
		case(eKeyboards::symbol):
			displayKeyboard = keyboards[2];
			break;
	}

	uint8_t keyboardRows = displayKeyboard.keys.size();

	Rectangle charRect = FontHelper::GetTextRect(tft, "X", textFont, Point(0, 0));
	charRect.update();

	// Now calculate the standard key size
	uint8_t keySize = tftWidth / 10;

	// Keysize is the standard X dimension, height will be the same
	location.x1 = 0;
	location.x2 = tft.width();
	location.y1 = tft.height() - (keySize*keyboardRows);
	location.y2 = tft.height();
	for (int y = 0; y < keyboardRows; y++)
	{
		uint16_t yStart = location.y1 + (y*keySize);
		uint16_t xStart = 0;
		std::vector <sKeys> keyRow = displayKeyboard.keys[y];
		for (int x = 0; x < keyRow.size(); x++)
		{			
			uint8_t keyWidth = keySize*(keyRow[x].keyWidth / 8);
			// First draw the box
			tft.fillRect(xStart, yStart, keyWidth, keySize, bgColor);
			tft.drawRect(xStart, yStart, keyWidth, keySize, chromeColor);
			tft.setCursor(xStart + keyWidth / 2, yStart + keyWidth / 2);
			tft.print(keyRow[x].character);
			xStart += keyWidth;
		}
		yStart += keySize;
	}

	updatePending = false;
}

sTouchResponse UIAlphaNumericEditor::ProcessTouch(Point pt)
{

}

void UIAlphaNumericEditor::setupScreenKeys()
{
	sKeyboard keyboard;
	keyboard.keyBoardType = eKeyboards::normal;

	keyboards.clear();
	std::vector<sKeys> keys;
	keys.push_back(sKeys('1', 8));
	keys.push_back(sKeys('2', 8));
	keys.push_back(sKeys('3', 8));
	keys.push_back(sKeys('4', 8));
	keys.push_back(sKeys('5', 8));
	keys.push_back(sKeys('6', 8));
	keys.push_back(sKeys('7', 8));
	keys.push_back(sKeys('8', 8));
	keys.push_back(sKeys('9', 8));
	keys.push_back(sKeys('0', 8));
	keyboard.keys.push_back(keys);
	keys.clear();
	keys.push_back(sKeys('q', 8));
	keys.push_back(sKeys('w', 8));
	keys.push_back(sKeys('e', 8));
	keys.push_back(sKeys('r', 8));
	keys.push_back(sKeys('t', 8));
	keys.push_back(sKeys('y', 8));
	keys.push_back(sKeys('u', 8));
	keys.push_back(sKeys('i', 8));
	keys.push_back(sKeys('o', 8));
	keys.push_back(sKeys('p', 8));
	keyboard.keys.push_back(keys);
	keys.clear();
	keys.push_back(sKeys(' ', 4, eSpecialKeys::nullKey));
	keys.push_back(sKeys('a', 8));
	keys.push_back(sKeys('s', 8));
	keys.push_back(sKeys('d', 8));
	keys.push_back(sKeys('f', 8));
	keys.push_back(sKeys('g', 8));
	keys.push_back(sKeys('h', 8));
	keys.push_back(sKeys('j', 8));
	keys.push_back(sKeys('k', 8));
	keys.push_back(sKeys('l', 8));
	keyboard.keys.push_back(keys);
	keys.push_back(sKeys(' ', 12, eSpecialKeys::shift));
	keys.push_back(sKeys('z', 8));
	keys.push_back(sKeys('x', 8));
	keys.push_back(sKeys('c', 8));
	keys.push_back(sKeys('v', 8));
	keys.push_back(sKeys('b', 8));
	keys.push_back(sKeys('n', 8));
	keys.push_back(sKeys('m', 8));
	keys.push_back(sKeys(' ', 12, eSpecialKeys::backspace));
	keyboard.keys.push_back(keys);
	keys.push_back(sKeys(' ', 12, eSpecialKeys::symbolKeys));
	keys.push_back(sKeys(',', 8));
	keys.push_back(sKeys(' ', 48,eSpecialKeys::space));
	keys.push_back(sKeys('.', 8));
	keys.push_back(sKeys(' ', 12,eSpecialKeys::enter));
	keyboard.keys.push_back(keys);
	keyboards.push_back(keyboard);

	keys.clear();
	keyboard.keys.clear();
	keyboard.keyBoardType == eKeyboards::shifted;
	keys.push_back(sKeys('1', 8));
	keys.push_back(sKeys('2', 8));
	keys.push_back(sKeys('3', 8));
	keys.push_back(sKeys('4', 8));
	keys.push_back(sKeys('5', 8));
	keys.push_back(sKeys('6', 8));
	keys.push_back(sKeys('7', 8));
	keys.push_back(sKeys('8', 8));
	keys.push_back(sKeys('9', 8));
	keys.push_back(sKeys('0', 8));
	keyboard.keys.push_back(keys);
	keys.clear();
	keys.push_back(sKeys('q', 8));
	keys.push_back(sKeys('w', 8));
	keys.push_back(sKeys('e', 8));
	keys.push_back(sKeys('r', 8));
	keys.push_back(sKeys('t', 8));
	keys.push_back(sKeys('y', 8));
	keys.push_back(sKeys('u', 8));
	keys.push_back(sKeys('i', 8));
	keys.push_back(sKeys('o', 8));
	keys.push_back(sKeys('p', 8));
	keyboard.keys.push_back(keys);
	keys.clear();
	keys.push_back(sKeys(' ', 4, eSpecialKeys::nullKey));
	keys.push_back(sKeys('a', 8));
	keys.push_back(sKeys('s', 8));
	keys.push_back(sKeys('d', 8));
	keys.push_back(sKeys('f', 8));
	keys.push_back(sKeys('g', 8));
	keys.push_back(sKeys('h', 8));
	keys.push_back(sKeys('j', 8));
	keys.push_back(sKeys('k', 8));
	keys.push_back(sKeys('l', 8));
	keyboard.keys.push_back(keys);
	keys.push_back(sKeys(' ', 12, eSpecialKeys::shift));
	keys.push_back(sKeys('z', 8));
	keys.push_back(sKeys('x', 8));
	keys.push_back(sKeys('c', 8));
	keys.push_back(sKeys('v', 8));
	keys.push_back(sKeys('b', 8));
	keys.push_back(sKeys('n', 8));
	keys.push_back(sKeys('m', 8));
	keys.push_back(sKeys(' ', 12, eSpecialKeys::backspace));
	keyboard.keys.push_back(keys);
	keys.push_back(sKeys(' ', 12, eSpecialKeys::symbolKeys));
	keys.push_back(sKeys(',', 8));
	keys.push_back(sKeys(' ', 48, eSpecialKeys::space));
	keys.push_back(sKeys('.', 8));
	keys.push_back(sKeys(' ', 12, eSpecialKeys::enter));
	keyboard.keys.push_back(keys);
	keyboards.push_back(keyboard); 
	
	keyboard.keys.clear();
	keys.clear();
	keys.push_back(sKeys('1', 8));
	keys.push_back(sKeys('2', 8));
	keys.push_back(sKeys('3', 8));
	keys.push_back(sKeys('4', 8));
	keys.push_back(sKeys('5', 8));
	keys.push_back(sKeys('6', 8));
	keys.push_back(sKeys('7', 8));
	keys.push_back(sKeys('8', 8));
	keys.push_back(sKeys('9', 8));
	keys.push_back(sKeys('0', 8));
	keyboard.keys.push_back(keys);
	keys.clear();
	keys.push_back(sKeys('Q', 8));
	keys.push_back(sKeys('W', 8));
	keys.push_back(sKeys('E', 8));
	keys.push_back(sKeys('R', 8));
	keys.push_back(sKeys('T', 8));
	keys.push_back(sKeys('Y', 8));
	keys.push_back(sKeys('U', 8));
	keys.push_back(sKeys('I', 8));
	keys.push_back(sKeys('O', 8));
	keys.push_back(sKeys('P', 8));
	keyboard.keys.push_back(keys);
	keys.clear();
	keys.push_back(sKeys(' ', 4, eSpecialKeys::nullKey));
	keys.push_back(sKeys('A', 8));
	keys.push_back(sKeys('S', 8));
	keys.push_back(sKeys('D', 8));
	keys.push_back(sKeys('F', 8));
	keys.push_back(sKeys('G', 8));
	keys.push_back(sKeys('H', 8));
	keys.push_back(sKeys('J', 8));
	keys.push_back(sKeys('K', 8));
	keys.push_back(sKeys('L', 8));
	keyboard.keys.push_back(keys);
	keys.push_back(sKeys(' ', 12, eSpecialKeys::shift));
	keys.push_back(sKeys('Z', 8));
	keys.push_back(sKeys('X', 8));
	keys.push_back(sKeys('C', 8));
	keys.push_back(sKeys('V', 8));
	keys.push_back(sKeys('B', 8));
	keys.push_back(sKeys('N', 8));
	keys.push_back(sKeys('M', 8));
	keys.push_back(sKeys(' ', 12, eSpecialKeys::backspace));
	keyboard.keys.push_back(keys);
	keys.push_back(sKeys(' ', 12, eSpecialKeys::symbolKeys));
	keys.push_back(sKeys(',', 8));
	keys.push_back(sKeys(' ', 48, eSpecialKeys::space));
	keys.push_back(sKeys('.', 8));
	keys.push_back(sKeys(' ', 12, eSpecialKeys::enter));
	keyboard.keys.push_back(keys);
	keyboard.keyBoardType = eKeyboards::shifted;
	keyboards.push_back(keyboard);

	keyboard.keys.clear();
	keys.clear();
	keys.push_back(sKeys('!', 8));
	keys.push_back(sKeys('@', 8));
	keys.push_back(sKeys('#', 8));
	keys.push_back(sKeys('$', 8));
	keys.push_back(sKeys('%', 8));
	keys.push_back(sKeys('^', 8));
	keys.push_back(sKeys('&', 8));
	keys.push_back(sKeys('*', 8));
	keys.push_back(sKeys('(', 8));
	keys.push_back(sKeys(')', 8));

	keyboard.keys.push_back(keys);
	keys.clear();
	keys.push_back(sKeys('~', 8));
	keys.push_back(sKeys('`', 8));
	keys.push_back(sKeys('-', 8));
	keys.push_back(sKeys('_', 8));
	keys.push_back(sKeys('=', 8));
	keys.push_back(sKeys('+', 8));
	keys.push_back(sKeys('[', 8));
	keys.push_back(sKeys(']', 8));
	keys.push_back(sKeys('{', 8));
	keys.push_back(sKeys('}', 8));
	keyboard.keys.push_back(keys);
	keys.clear();
	keys.push_back(sKeys(';', 8));
	keys.push_back(sKeys('\'', 8));
	keys.push_back(sKeys(':', 8));
	keys.push_back(sKeys('"', 8));
	keys.push_back(sKeys(',', 8));
	keys.push_back(sKeys('.', 8));
	keys.push_back(sKeys('<', 8));
	keys.push_back(sKeys('>', 8));
	keys.push_back(sKeys('/', 8));
	keys.push_back(sKeys('?', 8));

	keyboard.keys.push_back(keys);
	keys.push_back(sKeys(' ', 12, eSpecialKeys::alpha));
	keys.push_back(sKeys(',', 8));
	keys.push_back(sKeys(' ', 40, eSpecialKeys::space));
	keys.push_back(sKeys('.', 8));
	keys.push_back(sKeys(' ', 12, eSpecialKeys::backspace));
	keys.push_back(sKeys(' ', 12, eSpecialKeys::enter));

	keyboard.keyBoardType = eKeyboards::symbol;
	keyboards.push_back(keyboard);
#ifdef DEBUG
	Logger::Trace("Keyboards Initalized.");
#endif
}
#endif