#pragma once
#include "Enemy.h"

#define ENEMY_MAX (3)	// ìGÇÃç≈ëÂêî
#define ENEMY_HANDLE ("Data/Enemy/Enemy.png")
#define ENEMY_STATE_HANDLE ("Data/Enemy/EnemyState.png")

class CEnemyManager
{
private:

	int m_EnemyHandle;
	int m_EnemyStateHandle;

	CEnemy cEnemy[ENEMY_MAX];

	void SetEnemyAlive(int Index, bool Flag) { cEnemy[Index].SetEnemyActive(Flag); }

public:

	void Init();

	void Load();

	void Step();

	void Draw();

	void Exit();

	void StepNextStage(int Round);

	void SetActionOrder(int ActionOrder);

};
