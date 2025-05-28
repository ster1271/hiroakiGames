#pragma once

class CEnemy
{
private:

	int m_HP;	// ‘Ì—Í
	int m_AP;	// UŒ‚—Í

	int m_Action_Order;	// s“®‡

	bool m_IsActive;	// ¶‘¶ƒtƒ‰ƒO

public:

	void Init();

	void Load();

	void Step();

	void Exit();

	void Attack();

	void SetDamage(int Damage) { m_HP -= Damage; }

	void SetEnemyActive(bool Flag) { m_IsActive = Flag; }

};
