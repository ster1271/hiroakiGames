#include <vector>

#include "DxLib.h"
#include "Font.h"

#include "../Common.h"

int Font::bufCount;
int Font::fontHandle[(int)FontType::KindNum];

void Font::Init()
{
	bufCount = 0;
	for (int i = 0; i < (int)FontType::KindNum; i++)
	{
		if (FONT_EDGE_THICK[i] != -1)
			fontHandle[i] = CreateFontToHandle(FONT_PATH[i], FONT_SIZE[i], FONT_THICK[i], DX_FONTTYPE_ANTIALIASING_EDGE_8X8,
				-1, FONT_EDGE_THICK[i]);
		else
			fontHandle[i] = CreateFontToHandle(FONT_PATH[i], FONT_SIZE[i], FONT_THICK[i], DX_FONTTYPE_ANTIALIASING_8X8);
	}
}

void Font::Fin()
{
	for (int i = 0; i < (int)FontType::KindNum; i++)
	{
		DeleteFontToHandle(fontHandle[i]);
	}
}

void Font::DrawString(FontType font, int x, int y, unsigned int Color, const char* String)
{
	DrawFormatStringToHandle(x, y, Color,
		Font::GetfontHandle(font),
		String);
}

void Font::DrawFormatString(FontType font, int x, int y, unsigned int Color, const char* FormatString, ...)
{
	char buffer[FORMAT_STRING_MAX_LEN];

	va_list args;
	va_start(args, FormatString);

	vsnprintf(buffer, sizeof(buffer), FormatString, args);
	va_end(args);

	DrawFormatStringToHandle(x, y, Color,
		Font::GetfontHandle(font),
		buffer);
}

void Font::DrawFormatStringR(FontType font, int x, int y, unsigned int Color, const char* FormatString, ...)
{
	char buffer[FORMAT_STRING_MAX_LEN];

	va_list args;
	va_start(args, FormatString);

	vsnprintf(buffer, sizeof(buffer), FormatString, args);
	va_end(args);

	int width = GetDrawFormatStringWidthToHandle(Font::GetfontHandle(font),
		buffer);

	if (width != -1)
		DrawFormatStringToHandle(x - width, y, Color,
			Font::GetfontHandle(font),
			buffer);
}

void Font::DrawFormatStringC(FontType font, int x, int y, unsigned int Color, const char* FormatString, ...)
{
	char buffer[FORMAT_STRING_MAX_LEN];

	va_list args;
	va_start(args, FormatString);

	vsnprintf(buffer, sizeof(buffer), FormatString, args);
	va_end(args);

	int width = GetDrawFormatStringWidthToHandle(Font::GetfontHandle(font),
		buffer);

	if (width != -1)
		DrawFormatStringToHandle(x - width / 2, y, Color,
			Font::GetfontHandle(font),
			buffer);
}
