#include "DebugString.h"

#include "../Common.h"
#include "../Font/Font.h"

std::unique_ptr<DebugString> DebugString::m_Instance;

DebugString::DebugString()
{
	textList.resize(TEXTINFO_LIST_SIZE);
}

DebugString::~DebugString()
{
	
}

DebugString& DebugString::GetInstance()
{
	if (!m_Instance)
		m_Instance = std::make_unique<DebugString>();

	return *m_Instance;
}

void DebugString::DeleteInstance()
{
	if (m_Instance)
		m_Instance.reset();
}

void DebugString::Draw()
{
	if (IsDebug)
	{
		for (auto& elem : textList)
		{
			Font::DrawString(FontType::HGP‘n‰pŠpƒ|ƒbƒv‘Ì,
				elem.x, elem.y, elem.color,
				elem.debug_stirng.c_str());
		}
	}
	textList.clear();
}

void DebugString::AddTextInfo(TextInfo textInfo)
{
	if (textList.size() < TEXTINFO_LIST_SIZE)
		textList.emplace_back(textInfo);
}

void DebugString::AddString(int x, int y, std::string string)
{
	TextInfo value = { x, y, string, DEFAULT_COLOR };

	AddTextInfo(value);
}

void DebugString::AddFormatString(int x, int y, const char* format, ...)
{
	char buffer[FORMAT_STRING_MAX_LEN];

	va_list args;
	va_start(args, format);

	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	TextInfo value = { x, y, buffer, DEFAULT_COLOR };
	AddTextInfo(value);
}

void DebugString::DrawLogString(std::string string)
{
	string += '\n';
	OutputDebugString(string.c_str());
	
}

void DebugString::DrawLogFormatString(const char* format, ...)
{
	char buffer[FORMAT_STRING_MAX_LEN];

	va_list args;
	va_start(args, format);

	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	DrawLogString(buffer);
}
