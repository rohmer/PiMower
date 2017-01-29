#include "UIFont.h"

int UIFont::getFontNum(eFontName font)
{
	switch (font)
	{
		case(eFontName::u8g_font_4x6):
			return 6;
			break;
		case(eFontName::u8g_font_6x10):
			return 10;
			break;
		case(eFontName::u8g_font_9x18B):
			return 18;
			break;
		case(eFontName::u8g_font_gdr20):
			return 120;
			break;
		case(eFontName::u8g_font_osr18):
			return 51;
			break;
		case(eFontName::u8g_font_osr35n):
			return 123;
			break;
		case(eFontName::u8g_font_unifont):
			return 0;
			break;
		case(eFontName::defaultFont):
			return 0;
			break;
	}
	return 0;
}

int UIFont::getFontHeight(eFontName font)
{
	switch (font)
	{
		case(eFontName::u8g_font_4x6):
			return 6;
			break;
		case(eFontName::u8g_font_6x10):
			return 10;
			break;
		case(eFontName::u8g_font_9x18B):
			return 14;
			break;
		case(eFontName::u8g_font_gdr20):
			return 27;
			break;
		case(eFontName::u8g_font_osr18):
			return 24;
			break;
		case(eFontName::u8g_font_osr35n):
			return 46;
			break;
		case(eFontName::u8g_font_unifont):
			return 10;
			break;
		case(eFontName::defaultFont):
			return 10;
			break;
	}
	return 16;
}

int UIFont::getFontWidth(eFontName font)
{
	switch (font)
	{
	case(eFontName::u8g_font_4x6):
		return 4;
		break;
	case(eFontName::u8g_font_6x10):
		return 6;
		break;
	case(eFontName::u8g_font_9x18B):
		return 9;
		break;
	case(eFontName::u8g_font_gdr20):
		return 27;
		break;
	case(eFontName::u8g_font_osr18):
		return 26;
		break;
	case(eFontName::u8g_font_osr35n):
		return 41;
		break;
	case(eFontName::u8g_font_unifont):
		return 16;
		break;
	case(eFontName::defaultFont):
		return 16;
		break;
	}
	return 16;
}