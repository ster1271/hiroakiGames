#pragma once
#include "Enemy.h"

#define ENEMY_MAX (5)	// �G�̍ő吔

class CEnemyManager
{
private:

	int Action_Order;	// �s����

	CEnemy cEnemy[ENEMY_MAX];

public:

	void Init();

	void Load();

	void Step();

	void Exit();

};
