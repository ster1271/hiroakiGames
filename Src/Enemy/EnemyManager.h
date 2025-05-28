#pragma once
#include "Enemy.h"

#define ENEMY_MAX (6)	// “G‚ÌÅ‘å”

class CEnemyManager
{
private:

	int m_Action_Order;	// s“®‡

	CEnemy cEnemy[ENEMY_MAX];

public:

	void Init();

	void Load();

	void Step();

	void Draw();

	void Exit();

};
