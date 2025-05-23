#pragma once
#include "DxLib.h"

class CPlayer
{

public:

	enum TRIGGER
	{

	};

private:

	int m_PlayerHP;	// ライフポイント
	int m_PlayerGP; // ガードポイント

	int m_StateHndl;//ステータスハンドル

public:
	
	void Init();

	void Load();

	void Step();

	void Draw();

	void Exit();

};
