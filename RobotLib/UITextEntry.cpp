#include "UITextEntry.h"

/* Text window is:
	Landscape orientation - 10x4 rows of keys (Each key is 30x30) with the text input window across the top
	portrait orientation - 7x7 rows of keys, input window again across the top
*/

void UITextEntry::update(DigoleLCD* lcd)
{
	if (!isDirty)
		return;
	// First we should draw the background window
	
	
	if (lcd->getOrientation() == DigoleLCD::Landscape)
	{
		drawLandscape(lcd);
	}
	else
	{
		drawPortrait(lcd);
	}
}

void UITextEntry::drawPortrait(DigoleLCD* lcd)
{
}

/*
	char:
	0 0123456789
	10 abcdefghij
	20 klmnopqrst
	30 ^uvw**xyz#
	
	non-char
	-=`~!@#$%^
	&*()_+<>,.
	^;:(sc)'"#
*/

void UITextEntry::drawLandscape(DigoleLCD* lcd)
{	
	int rowTerm = 2;
	if (keyboardShown == eKeyboardShown::Normal)
		rowTerm++;
	// First 2 rows are similar in design
	for (int y = 0; y < rowTerm; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			// Draw Key
			int pushDown = 0;
			if (keyboardShown == eKeyboardShown::SpecialChars)
				pushDown++;
			lcd->drawBox((x * 31) + (x * 2), 110 + ((pushDown + y) * 31) + (y * 2), 31, 31);
			// put letter in key
			
			std::string c;
			if (keyboardShown == eKeyboardShown::Normal)
			{
				c = keys[(y * 10) + x];
				if (shiftedKeys)
				{
					std::transform(c.begin(), c.end(), c.begin(), ::toupper);
				}
			}
			else
			{
				c = specialChars[(y * 10) + x];
			}
			lcd->printxy_abs(
				(x * 31)+(x * 2)+12,
				110+y*((pushDown + y) * 31)+y*2+12,
				c);
			keyTargets.insert(std::pair<std::string,
				Rectangle>(c,
					Rectangle((x * 31) + (x * 2), 
						110 + ((pushDown + y) * 31) + (y * 2),
						(x * 31) + (x * 2)+31, 
						110 + ((pushDown + y) * 31) + (y * 2)+31)));
		}
	}
	
	// Now we draw the last row
	if (keyboardShown == eKeyboardShown::Normal)
	{
		// Normal keys
		// First is the shift key
		int y = 3, x = 0;
		lcd->drawBox((x * 31) + (x * 2), 110 + (y * 31) + (y * 2), 31, 31);
		lcd->drawBitmap((x * 31) + (x * 2) + 5, 110 + (y * 31) + (y * 2) + 5, 20, 20, shiftIcon);
		keyTargets.insert(std::pair<std::string,
			Rectangle>("SHIFT",
				Rectangle((x * 31) + (x * 2), 
					110 + (y * 31) + (y * 2),
					(x * 31) + (x * 2)+31, 
					110 + (y * 31) + (y * 2)+31)));
		// Then uvw
		for (int x = 1; x <= 3; x++)
		{
			std::string c;
			c = keys[(y * 10) + x];
			lcd->drawBox((x * 31) + (x * 2), 110 + (y * 31) + (y * 2), 31, 31);
			lcd->printxy_abs(
				(x * 31)+(x * 2)+12,
				110+y*(y * 31)+y*2+12,
				c);
			keyTargets.insert(std::pair<std::string,
				Rectangle>(c,
					Rectangle((x * 31) + (x * 2), 
						110 + (y * 31) + (y * 2),
						(x * 31) + (x * 2)+31, 
						110 + (y * 31) + (y * 2)+31)));				
		}
		// Then 2 char wide space
		y = 3, x = 4;
		lcd->drawBox((x * 31) + (x * 2), 110 + (y * 31) + (y * 2), 63, 31);
		lcd->drawBitmap((x * 31) + (x * 2) + 5, 110 + (y * 31) + (y * 2) + 5, 20, 20, spaceBarIcon);
		std::string space("space");
		keyTargets.insert(std::pair<std::string,
			Rectangle>(space,
				Rectangle((x * 31) + (x * 2), 
					110 + (y * 31) + (y * 2),
					(x * 31) + (x * 2)+63, 
					110 + (y * 31) + (y * 2)+31)));
		// Then xyz
		
		for (int x = 4; x <= 6; x++)
		{
			std::string c;
			c = keys[(y * 10) + x];
			lcd->drawBox(((x+2) * 31) + (x * 2), 110 + (y * 31) + (y * 2), 31, 31);
			lcd->printxy_abs(
				((x+2) * 31)+(x * 2)+12,
				110+y*(y * 31)+y*2+12,
				c);
			keyTargets.insert(std::pair<std::string,
				Rectangle>(c,
					Rectangle(((x+2) * 31) + (x * 2), 
						110 + (y * 31) + (y * 2),
						((x+2) * 31) + (x * 2)+31, 
						110 + (y * 31) + (y * 2)+31)));				
		}
		// Finally Char Screen Key
		x = 9;
		lcd->drawBox(((x + 2) * 31) + (x * 2), 110 + (y * 31) + (y * 2), 31, 31);
		lcd->printxy_abs(
			((x + 2) * 31)+(x * 2)+12,
			110+y*(y * 31)+y*2+12,
			"#");
		std::string c("CHARSCREEN");
		keyTargets.insert(std::pair<std::string,Rectangle>(c,
				Rectangle(((x + 2) * 31) + (x * 2), 
					110 + (y * 31) + (y * 2),
					((x + 2) * 31) + (x * 2)+31, 
					110 + (y * 31) + (y * 2)+31)));				
	}
}
		