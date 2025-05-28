#include "EnemyManager.h"

void CEnemyManager::Init() 
{

}

void CEnemyManager::Load()
{

}

void CEnemyManager::Step()
{

}

void CEnemyManager::Draw()
{

}

void CEnemyManager::Exit()
{

}

void CEnemyManager::StepNextStage(int Round)
{
	for (int Index = 0; Index < ENEMY_MAX;Index++)
	{
		SetEnemyAlive(Index, true);
	}
}
