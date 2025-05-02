#pragma once
#include <memory>
#include <list>
#include <string>

#include <cstdarg>
#include <cstdio>

#include "DxLib.h"

const unsigned int DEFAULT_COLOR = GetColor(255, 255, 255);

constexpr int TEXTINFO_LIST_SIZE = 50;

class DebugString
{
public:
	struct TextInfo
	{
		int x;
		int y;
		std::string debug_stirng;

		unsigned int color;
	};

public:
	DebugString();
	~DebugString();

public:
	//インスタンスを取得
	static DebugString& GetInstance();

	//インスタンスを削除
	static void DeleteInstance();

private:
	//インスタンス
	static std::unique_ptr<DebugString> m_Instance;

private:
	std::list<TextInfo> textList;
	
private:
	void AddTextInfo(TextInfo textInfo);

public:
	void Draw();

	void AddString(int x, int y, std::string string);
	void AddFormatString(int x, int y, const char* format, ...);

	void DrawLogString(std::string string);
	void DrawLogFormatString(const char* format, ...);
};