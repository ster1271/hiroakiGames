#include "Stage.h"

void CStage::Init()
{
	m_NowStage = 0; 
	m_NowTurn = 0;
	m_ePhaseState = START_PHASE;

	cCardManager.Init();
	cEnemyManager.Init();
}

void CStage::Load()
{
	m_NowStage = 0;
	m_NowTurn = 0;
	m_ePhaseState = START_PHASE;

	cCardManager.Load();
	cPlayer.Load();
	cEnemyManager.Load();
}

void CStage::Step()
{
	cCardManager.Step();
	cEnemyManager.Step();
	cPlayer.Step();

	switch (m_ePhaseState)
	{
	case CStage::START_PHASE:
		break;
	case CStage::END_PHASE:
		break;
	default:
		break;
	}
}

void CStage::Draw()
{
	cCardManager.Draw();

	cEnemyManager.Draw();

	cPlayer.Draw();
}

void CStage::Exit()
{
	cCardManager.Exit();
	cEnemyManager.Exit();
	cPlayer.Exit();
}