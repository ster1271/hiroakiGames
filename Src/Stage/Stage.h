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

	int m_NowStage;	// ���݂̃X�e�[�W 
	int m_NowTurn; // ���݂̃^�[��
	PHASE_STATE m_ePhaseState;	// �t�F�C�Y�Ǘ��̕ϐ�

public:

	void Init();

	void Load();

	void Step();

	void Draw();

	void Exit();

};
