#pragma once
#include "../Card/CardManager.h"
#include "../Player/Player.h"
#include "../Enemy/EnemyManager.h"

class CStage
{
public:

	enum PHASE_STATE
	{
		NEXT_STAGE_PHASE,		// 次のステージへ
		GAMEOVER_STATE_PHASE,	// ゲームオーバー

		START_PHASE,			// ターン開始
		END_PHASE,				// ターン終了
	};

private:

	int m_NowStage;	// 現在のステージ 
	int m_NowTurn; // 現在のターン

	bool m_Start_Phase;	// そのフェイズのスタート時だけ行う処理
	bool m_End_Phase;	// そのフェイズの終了時だけ行う処理

	int m_Direction_Time;	// 演出時間

	PHASE_STATE m_ePhaseState;	// フェイズ管理の変数

	CPlayer cPlayer;
	CEnemyManager cEnemyManager;
	CCardManager cCardManager;

public:

	void Init();

	void Load();

	void Step();

	void Draw();

	void Exit();

};
