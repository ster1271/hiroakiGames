#pragma once
#include "DxLib.h"

class CPlayer
{

public:

	enum TRIGGER
	{

	};

private:

	int m_PlayerHP;	// ���C�t�|�C���g
	int m_PlayerGP; // �K�[�h�|�C���g

	int m_StateHndl;//�X�e�[�^�X�n���h��

public:
	
	void Init();

	void Load();

	void Step();

	void Draw();

	void Exit();

};
