#pragma once

class CPlayer
{

private:

	int m_PlayerHP;	// ライフポイント
	int m_PlayerGP; // ガードポイント

public:
	
	void Init();

	void Load();

	void Step();

	void Exit();

};
