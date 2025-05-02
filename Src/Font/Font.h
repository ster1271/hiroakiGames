#pragma once
#include <iostream>

#include <cstdarg>
#include <cstdio>

enum class FontType
{
	HGP‘n‰pŠpƒ|ƒbƒv‘Ì,
	HGP‘n‰pŠpƒ|ƒbƒv‘Ì24_10,
	HGP‘n‰pŠpƒ|ƒbƒv‘Ì64_20,

	KindNum
};

constexpr char FONT_PATH[(int)FontType::KindNum][128] =
{
	"HGP‘n‰pŠpƒ|ƒbƒv‘Ì",
	"HGP‘n‰pŠpƒ|ƒbƒv‘Ì",
};

constexpr int FONT_SIZE[(int)FontType::KindNum] =
{
	16,
	24,
	64,
};

constexpr int FONT_THICK[(int)FontType::KindNum] =
{
	5,
	10,
	20,
};

constexpr int FONT_EDGE_THICK[(int)FontType::KindNum] =
{
	1,
	2,
	2,
};

//DrawFormatStringToHandle
//GetDrawFormatStringWidthToHandle
class Font
{
private:
	static int bufCount;
	static int fontHandle[(int)FontType::KindNum];
	
	//static void Draw_to_Screen(FontType font, int x, int y, unsigned int Color, TCHAR* FormatString, va_list ap);

public:
	static void Init();
	static void Fin();

	static int GetfontHandle(FontType font) { return fontHandle[(int)font]; }

	static void DrawString(FontType font, int x, int y, unsigned int Color, const char* String);
	static void DrawFormatString(FontType font, int x, int y, unsigned int Color, const char* FormatString, ...);
	static void DrawFormatStringR(FontType font, int x, int y, unsigned int Color, const char* FormatString, ...);
	static void DrawFormatStringC(FontType font, int x, int y, unsigned int Color, const char* FormatString, ...);
};