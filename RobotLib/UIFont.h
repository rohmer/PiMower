#pragma once

class UIFont 
{
	public:
		enum eFontName
		{
			u8g_font_4x6,
			u8g_font_6x10,
			u8g_font_9x18B,
			u8g_font_osr18,
			u8g_font_gdr20,
			u8g_font_osr35n,
			u8g_font_unifont
		};
	
		static int getFontNum(eFontName font);
		static int getFontWidth(eFontName font);
		static int getFontHeight(eFontName font);
};