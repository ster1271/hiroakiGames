#pragma once

class CEnemy
{
private:

	int m_HP;	// �̗�
	int m_AP;	// �U����

	bool m_IsActive;	// �����t���O

public:

	void Init();

	void Load();

	void Step();

	void Exit();

	void SetDamage(int Damage) { m_HP -= Damage; }

	void SetEnemyActive(bool Flag) { m_IsActive = Flag; }

};
