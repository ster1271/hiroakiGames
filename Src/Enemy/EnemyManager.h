#pragma once
#include "Enemy.h"

#define ENEMY_MAX (5)	// “G‚ÌÅ‘å”

class CEnemyManager
{
private:

	int Action_Order;	// s“®‡

	CEnemy cEnemy[ENEMY_MAX];

public:

	void Init();

	void Load();

	void Step();

	void Exit();

};
