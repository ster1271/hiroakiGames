#pragma once

class CEnemy
{
private:

	int m_HP;	// 体力
	int m_AP;	// 攻撃力

	int m_Action_Order;	// 行動順

	bool m_IsActive;	// 生存フラグ

public:

	void Init();

	void Load();

	void Step();

	void Exit();

	void Attack();

	void SetDamage(int Damage) { m_HP -= Damage; }

	void SetEnemyActive(bool Flag) { m_IsActive = Flag; }

};
