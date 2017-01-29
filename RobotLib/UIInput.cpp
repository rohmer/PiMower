#include "UIInput.h"

UIInput::UIInput() 
	: UIElement(Point(0, 0), false, true)
{
}

void UIInput::update(DigoleLCD *lcd, RobotLib *robotLib)
{
	if (lcd->getOrientation() == DigoleLCD::Portrait)
	{
		drawPortrait(lcd,robotLib);
	}
}

// Keyboard is bottom 5 rows of 53x30 keys
void UIInput::drawPortrait(DigoleLCD *lcd, RobotLib *robotLib)
{
	lcd->setColor(DigoleLCD::WHITE);
	lcd->setBackgroundColor(DigoleLCD::BLACK);
	int height = 320;
	int width = 240;	
	int keyWidth = 53;
	int keyHeight = 24;
	int keyStartY = height - (30 * 5);
	
	// Draw grid for keys
	int x = 0;
	for (int i = 0; i < 6; i++)
	{		
		lcd->drawLine(x, keyStartY, x, 319);
		x += 40;
	}
	lcd->drawLine(239, keyStartY, 239, 319);
	
	int y = 0;
	for (int i = 0; i <= 5; i++)
	{
		lcd->drawLine(0, keyStartY + y, width - 1, keyStartY + y);
		y += 30;
	}
	lcd->drawLine(0, 319, width - 1, 319);
	
	shiftedKeys = true;
	char keys[5][6];
	// Put glyphs on keys
	touchTargets.clear();
	switch (currentKeyboard)
	{
		case(eKeyboardShown::alpha):
		for (int a = 0; a < 5; a++)
			for (int b = 0; b < 6; b++)
			{
				if (!shiftedKeys)
				{
					keys[a][b] = alphaPort[a][b];
				}
				else
				{
					if (alphaPort[a][b] != 'c' && 
						alphaPort[a][b] != 'p' &&
						alphaPort[a][b] != 'b' &&
						alphaPort[a][b] != 's')
					{
						keys[a][b] = toupper(alphaPort[a][b]);
					}
				}
				touchTargets.push_back(keyTarget_s(Rectangle(b * 40 + 1, keyStartY + (y * 30) + 1, (b + 1) * 40 - 1, keyStartY + (y + 1) * 40 - 1), keys[a][b]));
			}
		break;
	case(eKeyboardShown::symbol1):
		break;
	case(eKeyboardShown::symbol2):
		break;
			
	}
	lcd->setFont(UIFont::u8g_font_gdr20);
	int glyphX = 15;
	int glyphY = keyStartY + 18;
	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 6; x++)
		{
			if (redraw)
			{
				lcd->setColor(DigoleLCD::BLACK);
				lcd->drawBoxFill(x * 40 + 1, y * 30 + 1, 38, 28);
				lcd->setColor(DigoleLCD::WHITE);
			}
			char keyGlyph = keys[y][x];
			if (currentKeyboard == eKeyboardShown::alpha)
			{
				switch (keyGlyph)
				{
				case 'S':
					{
						// Shift Key
						lcd->drawBitmap(glyphX + (x * 40)-3, glyphY -12 + (y * 30), 15, 18, shift_icon, DigoleLCD::WHITE);
						break;
					}
				case 'C':
					{
						// Change Page
						lcd->drawBitmap(glyphX + (x * 40) - 5, glyphY - 13 + (y * 30), 20, 20, symbol_icon, DigoleLCD::WHITE); 
						break;
					}
				case 'P':
					{
						// Space Bar
						lcd->drawBitmap(glyphX + (x * 40) - 7, glyphY - 12 + (y * 30), 24,18, spacebar_icon, DigoleLCD::WHITE); 
						break;
					}
				case 'B':
					{
						// Backspace
						lcd->drawBitmap(glyphX + (x * 40) - 7, glyphY - 11 + (y * 30), 24, 18, backspace_icon, DigoleLCD::WHITE); 
						break;
					}
				default:
					{
						if (shiftedKeys)
							keyGlyph = toupper(keyGlyph);
						std::stringstream s;
						s << keyGlyph;
						lcd->printxy_abs(glyphX + (x * 40), glyphY + (y * 30), s.str());
					}					
				}
			}
		}
	}	
	
	redraw = true;
}