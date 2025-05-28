#pragma once
#include "../Card/CardManager.h"
#include "../Player/Player.h"
#include "../Enemy/EnemyManager.h"

class CStage
{
public:

	enum PHASE_STATE
	{
		NEXT_STAGE_PHASE,		// ���̃X�e�[�W��
		GAMEOVER_STATE_PHASE,	// �Q�[���I�[�o�[

		START_PHASE,			// �^�[���J�n
		END_PHASE,				// �^�[���I��
	};

private:

	int m_NowStage;	// ���݂̃X�e�[�W 
	int m_NowTurn; // ���݂̃^�[��

	int m_Direction_Time;	// ���o����

	PHASE_STATE m_ePhaseState;	// �t�F�C�Y�Ǘ��̕ϐ�

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
