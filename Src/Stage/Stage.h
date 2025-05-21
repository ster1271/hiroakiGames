#pragma once

class CStage
{
public:

	enum PHASE_STATE
	{
		START_PHASE,
		END_PHASE,
	};

private:

	int m_NowStage;	// 現在のステージ 
	int m_NowTurn; // 現在のターン
	PHASE_STATE m_ePhaseState;	// フェイズ管理の変数

public:

	void Init();

	void Load();

	void Step();

	void Draw();

	void Exit();

};
