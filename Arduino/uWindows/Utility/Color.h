#pragma once
#include <stdint.h>
#include "../Options.h"
#include "Logger.h"

///Implements definition and operations with color
class Color
{
public:
	/// Common color constants
#ifdef RA8875
	enum ColorDefs
	{
		Black = 0x0000,
		White = 0xFFFF,
		BrightRed = 0xF800,
		BrightGreen = 0x07E0,
		BrightBlue = 0x001F,
		BrightCyan = 0x07FF,
		BrightMagenta = 0xF81F,
		Yellow = 0xFFF0,
		BrightYellow = 0xFFE0,
		LightYellow = 0xFFF2,
		Gold = 0xFEA0,
		Blue = 0x0010,
		Green = 0x0400,
		Cyan = 0x0410,
		Red = 0x8000,
		Magenta = 0x8010,
		Brown = 0xFC00,
		LightGray = 0x8410,
		DarkGray = 0x4208,
		LightBlue = 0x841F,
		LightGreen = 0x87F0,
		LightCyan = 0x87FF,
		LightRed = 0xFC10,
		LightMagenta = 0xFC1F,
		SaddleBrown = 0x8A22,
		Sienna = 0xA285,
		Peru = 0xCC27,
		Burlywood = 0xDDD0,
		Wheat = 0xF7BB,
		Tan = 0xD5B1,
		Orange = 0xFDC9,
		DarkOrange = 0xFC60,
		LightOrange = 0xFE40,
		Gray242 = 0xF79E,
		Gray229 = 0xE73C,
		Gray204 = 0xCE79,
		Gray192 = 0xC618,
		Gray160 = 0xA514,
		Gray128 = 0x8410,
		Gray96 = 0x630C,
		Gray32 = 0x2104,
		Gray10 = 0x0841
	};
#endif
#ifdef FT8XX
	enum ColorDefs
	{
		AliceBlue = 0xFFF0F8FF,
		AntiqueWhite = 0xFFFAEBD7,
		Aqua = 0xFF00FFFF,
		Aquamarine = 0xFF7FFFD4,
		Azure = 0xFFF0FFFF,
		Beige = 0xFFF5F5DC,
		Bisque = 0xFFFFE4C4,
		Black = 0xFF000000,
		BlanchedAlmond = 0xFFFFEBCD,
		Blue = 0xFF0000FF,
		BlueViolet = 0xFF8A2BE2,
		Brown = 0xFFA52A2A,
		BurlyWood = 0xFFDEB887,
		CadetBlue = 0xFF5F9EA0,
		Chartreuse = 0xFF7FFF00,
		Chocolate = 0xFFD2691E,
		Coral = 0xFFFF7F50,
		CornflowerBlue = 0xFF6495ED,
		Cornsilk = 0xFFFFF8DC,
		Crimson = 0xFFDC143C,
		Cyan = 0xFF00FFFF,
		DarkBlue = 0xFF00008B,
		DarkCyan = 0xFF008B8B,
		DarkGoldenrod = 0xFFB8860B,
		DarkGray = 0xFFA9A9A9,
		DarkGreen = 0xFF006400,
		DarkKhaki = 0xFFBDB76B,
		DarkMagenta = 0xFF8B008B,
		DarkOliveGreen = 0xFF556B2F,
		DarkOrange = 0xFFFF8C00,
		DarkOrchid = 0xFF9932CC,
		DarkRed = 0xFF8B0000,
		DarkSalmon = 0xFFE9967A,
		DarkSeaGreen = 0xFF8FBC8B,
		DarkSlateBlue = 0xFF483D8B,
		DarkSlateGray = 0xFF2F4F4F,
		DarkTurquoise = 0xFF00CED1,
		DarkViolet = 0xFF9400D3,
		DeepPink = 0xFFFF1493,
		DeepSkyBlue = 0xFF00BFFF,
		DimGray = 0xFF696969,
		DodgerBlue = 0xFF1E90FF,
		Firebrick = 0xFFB22222,
		FloralWhite = 0xFFFFFAF0,
		ForestGreen = 0xFF228B22,
		Fuchsia = 0xFFFF00FF,
		Gainsboro = 0xFFDCDCDC,
		GhostWhite = 0xFFF8F8FF,
		Gold = 0xFFFFD700,
		Goldenrod = 0xFFDAA520,
		Gray = 0xFF808080,
		Green = 0xFF008000,
		GreenYellow = 0xFFADFF2F,
		Honeydew = 0xFFF0FFF0,
		HotPink = 0xFFFF69B4,
		IndianRed = 0xFFCD5C5C,
		Indigo = 0xFF4B0082,
		Ivory = 0xFFFFFFF0,
		Khaki = 0xFFF0E68C,
		Lavender = 0xFFE6E6FA,
		LavenderBlush = 0xFFFFF0F5,
		LawnGreen = 0xFF7CFC00,
		LemonChiffon = 0xFFFFFACD,
		LightBlue = 0xFFADD8E6,
		LightCoral = 0xFFF08080,
		LightCyan = 0xFFE0FFFF,
		LightGoldenrodYellow = 0xFFFAFAD2,
		LightGray = 0xFFD3D3D3,
		LightGreen = 0xFF90EE90,
		LightPink = 0xFFFFB6C1,
		LightSalmon = 0xFFFFA07A,
		LightSeaGreen = 0xFF20B2AA,
		LightSkyBlue = 0xFF87CEFA,
		LightSlateGray = 0xFF778899,
		LightSteelBlue = 0xFFB0C4DE,
		LightYellow = 0xFFFFFFE0,
		Lime = 0xFF00FF00,
		LimeGreen = 0xFF32CD32,
		Linen = 0xFFFAF0E6,
		Magenta = 0xFFFF00FF,
		Maroon = 0xFF800000,
		MediumAquamarine = 0xFF66CDAA,
		MediumBlue = 0xFF0000CD,
		MediumOrchid = 0xFFBA55D3,
		MediumPurple = 0xFF9370DB,
		MediumSeaGreen = 0xFF3CB371,
		MediumSlateBlue = 0xFF7B68EE,
		MediumSpringGreen = 0xFF00FA9A,
		MediumTurquoise = 0xFF48D1CC,
		MediumVioletRed = 0xFFC71585,
		MidnightBlue = 0xFF191970,
		MintCream = 0xFFF5FFFA,
		MistyRose = 0xFFFFE4E1,
		Moccasin = 0xFFFFE4B5,
		NavajoWhite = 0xFFFFDEAD,
		Navy = 0xFF000080,
		OldLace = 0xFFFDF5E6,
		Olive = 0xFF808000,
		OliveDrab = 0xFF6B8E23,
		Orange = 0xFFFFA500,
		OrangeRed = 0xFFFF4500,
		Orchid = 0xFFDA70D6,
		PaleGoldenrod = 0xFFEEE8AA,
		PaleGreen = 0xFF98FB98,
		PaleTurquoise = 0xFFAFEEEE,
		PaleVioletRed = 0xFFDB7093,
		PapayaWhip = 0xFFFFEFD5,
		PeachPuff = 0xFFFFDAB9,
		Peru = 0xFFCD853F,
		Pink = 0xFFFFC0CB,
		Plum = 0xFFDDA0DD,
		PowderBlue = 0xFFB0E0E6,
		Purple = 0xFF800080,
		Red = 0xFFFF0000,
		RosyBrown = 0xFFBC8F8F,
		RoyalBlue = 0xFF4169E1,
		SaddleBrown = 0xFF8B4513,
		Salmon = 0xFFFA8072,
		SandyBrown = 0xFFF4A460,
		SeaGreen = 0xFF2E8B57,
		SeaShell = 0xFFFFF5EE,
		Sienna = 0xFFA0522D,
		Silver = 0xFFC0C0C0,
		SkyBlue = 0xFF87CEEB,
		SlateBlue = 0xFF6A5ACD,
		SlateGray = 0xFF708090,
		Snow = 0xFFFFFAFA,
		SpringGreen = 0xFF00FF7F,
		SteelBlue = 0xFF4682B4,
		Tan = 0xFFD2B48C,
		Teal = 0xFF008080,
		Thistle = 0xFFD8BFD8,
		Tomato = 0xFFFF6347,
		Transparent = 0x00FFFFFF,
		Turquoise = 0xFF40E0D0,
		Violet = 0xFFEE82EE,
		Wheat = 0xFFF5DEB3,
		White = 0xFFFFFFFF,
		WhiteSmoke = 0xFFF5F5F5,
		Yellow = 0xFFFFFF00,
		YellowGreen = 0xFF9ACD32
	};
#endif

	inline static uint16_t Color565(uint8_t r, uint8_t g, uint8_t b) { return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3); }
	static uint16_t GetColor565(ColorDefs color);
	static uint16_t Color32To565(int32_t color);
	inline static  void 	Color565ToRGB(uint16_t color, uint8_t &r, uint8_t &g, uint8_t &b) { r = (((color & 0xF800) >> 11) * 527 + 23) >> 6; g = (((color & 0x07E0) >> 5) * 259 + 33) >> 6; b = ((color & 0x001F) * 527 + 23) >> 6; }
	static ColorDefs GetColor(ColorDefs color)
	{
#ifdef FT8XX
		return color;
#endif
		return(GetColor565(color));
	}

	inline static uint32_t Color565To32(uint16_t inputColor)
	{
		unsigned long r = (inputColor & 0xF800) > 11;
		unsigned long g = (inputColor & 0x07E0) > 5;
		unsigned long b = (inputColor & 0x001F);
		r = r * 255 / 31;
		g = g * 255 / 63;
		b = b * 255 / 31;
		return ((r << 16) | (g << 8) | b);
	}

	inline static uint16_t ColorToGrayscale(int16_t color)
	{
		uint8_t r, g, b;
		Color565ToRGB(color, r, g, b);
		uint8_t grayVal = (r + g + b) / 3;
		return (Color565(grayVal, grayVal, grayVal));
	}
	inline static uint8_t ColorToGrayscaleValue(int16_t color)
	{
		uint8_t r, g, b;
		Color565ToRGB(color, r, g, b);
		uint8_t grayVal = (r + g + b) / 3;
		return grayVal;
	}
	inline static int16_t CombineColor(uint16_t foreground, uint16_t background, uint8_t foregroundOpacity)
	{
		uint16_t bgColorGray = ColorToGrayscaleValue(background);
		uint8_t r, g, b;
		Color::Color565ToRGB(foreground, r, g, b);
		r -= bgColorGray*(100 / foregroundOpacity);
		g -= bgColorGray*(100 / foregroundOpacity);;
		b -= bgColorGray*(100 / foregroundOpacity);;
		return(Color::Color565(r, g, b));
	}

	inline static tColor ContrastingColor(tColor inputColor)
	{
#ifdef RA8875
		int32_t iColor = Color565to32(inputColor);
#endif
#ifdef FT8XX
		int32_t iColor = inputColor;
#endif
		if (
			abs(((iColor) & 0xFF) - 0x80) <= 0x40 &&
			abs(((iColor >> 8) & 0xFF) - 0x80) <= 0x40 &&
			abs(((iColor >> 16) & 0xFF) - 0x80) <= 0x40

			) 
			return (0x7F7F7F + iColor) & 0xFFFFFF;
		else return iColor ^ 0xFFFFFF;
	}
};
