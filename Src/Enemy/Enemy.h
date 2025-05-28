#pragma once

class CEnemy
{
private:

	int m_HP;	// �̗�
	int m_AP;	// �U����

	int m_Action_Order;	// �s����

	bool m_IsActive;	// �����t���O

public:

	void Init();

	void Load();

	void Step();

	void Exit();

	void Attack();

	void SetDamage(int Damage) { m_HP -= Damage; }

	void SetEnemyActive(bool Flag) { m_IsActive = Flag; }

};
