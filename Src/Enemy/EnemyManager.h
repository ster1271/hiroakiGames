#pragma once
#include "Enemy.h"

#define ENEMY_MAX (5)	// 敵の最大数

class CEnemyManager
{
private:

	int Action_Order;	// 行動順

	CEnemy cEnemy[ENEMY_MAX];

public:

	void Init();

	void Load();

	void Step();

	void Exit();

};
