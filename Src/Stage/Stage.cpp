#include "Stage.h"

void CStage::Init()
{
	m_NowStage = 0; 
	m_NowTurn = 0;

	m_Start_Phase = false;
	m_End_Phase = false;

	m_ePhaseState = NEXT_STAGE_PHASE;

	cCardManager.Init();
	cEnemyManager.Init();
}

void CStage::Load()
{
	m_NowStage = 0;
	m_NowTurn = 0;

	m_Start_Phase = true;
	m_End_Phase = true;

	m_ePhaseState = NEXT_STAGE_PHASE;

	cCardManager.Load();
	cPlayer.Load();
	cEnemyManager.Load();
}

void CStage::Step()
{
	cCardManager.Step();
	cEnemyManager.Step();
	cPlayer.Step();

	m_Start_Phase = true;
	m_End_Phase = true;

	switch (m_ePhaseState)
	{
	case CStage::NEXT_STAGE_PHASE:
	{
		if (m_Start_Phase)
		{
			m_NowStage++;
			m_NowTurn = 0;

			cEnemyManager.StepNextStage(m_ePhaseState);

		}

		if (m_End_Phase)
		{
			m_ePhaseState = START_PHASE;
		}

	}
		break;
	case CStage::GAMEOVER_STATE_PHASE:
		break;
	case CStage::START_PHASE:
	{
		if (m_Start_Phase)
		{

		}

		if (m_End_Phase)
		{
			m_ePhaseState = END_PHASE;
		}
	}
		break;
	case CStage::END_PHASE:
	{
			if (m_Start_Phase)
			{

			}

			if (m_End_Phase)
			{
				m_ePhaseState = START_PHASE;
				m_NowTurn++;
			}
	}
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

	DrawFormatString(20, 15, GetColor(0, 0, 0), "ラウンド：%d", m_NowStage);
	DrawFormatString(20, 30, GetColor(0, 0, 0), "ターン：%d", m_NowTurn);
}

void CStage::Exit()
{
	cCardManager.Exit();
	cEnemyManager.Exit();
	cPlayer.Exit();
}