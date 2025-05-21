#include "Stage.h"

void CStage::Init()
{
	m_NowStage = 0; 
	m_NowTurn = 0;
	m_ePhaseState = START_PHASE;
}

void CStage::Load()
{
	m_NowStage = 0;
	m_NowTurn = 0;
	m_ePhaseState = START_PHASE;
}

void CStage::Step()
{
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

}

void CStage::Exit()
{

}