#pragma once

class CPlayer
{

public:

	enum TRIGGER
	{

	};

private:

	int m_PlayerHP;	// ���C�t�|�C���g
	int m_PlayerGP; // �K�[�h�|�C���g

public:
	
	void Init();

	void Load();

	void Step();

	void Exit();

};
