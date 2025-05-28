#pragma once
#include "DxLib.h"


class CPlayer
{

public:

	enum TRIGGER
	{
		TRIGGER_TURN_START,		// ターン開始時
		TRIGGER_TURN_END,		// ターン終了時
		TRIGGER_PLAYER_DAMAGE,	// プレイヤーがダメージを受けたとき
		TRIGGER_ENEMY_DAMAGE,	// 敵にダメージを与えたとき 
		TRIGGER_ENEMY_DEFEAT,	// 敵を倒したとき
		TRIGGER_STAGE_CLEAR,	// ステージをクリアしたとき
		TRIGGER_GET_CARD,		// カードを手に入れたとき
	};

private:

	int m_PlayerHP;	// ライフポイント
	int m_PlayerGP; // ガードポイント
	int m_PlayerAP;	// 攻撃力

	int m_FontHandle;
	int m_StateHndl;//ステータスハンドル

public:
	
	void Init();

	void Load();

	void Step();

	void Draw();

	void Exit();

};
