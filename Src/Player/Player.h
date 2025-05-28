#pragma once
#include "DxLib.h"


class CPlayer
{

public:

	enum TRIGGER
	{
		TRIGGER_TURN_START,		// �^�[���J�n��
		TRIGGER_TURN_END,		// �^�[���I����
		TRIGGER_PLAYER_DAMAGE,	// �v���C���[���_���[�W���󂯂��Ƃ�
		TRIGGER_ENEMY_DAMAGE,	// �G�Ƀ_���[�W��^�����Ƃ� 
		TRIGGER_ENEMY_DEFEAT,	// �G��|�����Ƃ�
		TRIGGER_STAGE_CLEAR,	// �X�e�[�W���N���A�����Ƃ�
		TRIGGER_GET_CARD,		// �J�[�h����ɓ��ꂽ�Ƃ�
	};

private:

	int m_PlayerHP;	// ���C�t�|�C���g
	int m_PlayerGP; // �K�[�h�|�C���g
	int m_PlayerAP;	// �U����

	int m_FontHandle;
	int m_StateHndl;//�X�e�[�^�X�n���h��

public:
	
	void Init();

	void Load();

	void Step();

	void Draw();

	void Exit();

};
