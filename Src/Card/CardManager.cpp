#include "CardManager.h"

void CCardManager::Init()
{
	m_CardHandle = 0;
	m_CardFlameHandle = 0;
}

void CCardManager::Load()
{
	m_CardHandle = LoadGraph(CARD_HANDLE);

	for (int Index = 0; Index < CARD_MAX; Index++)
	{
		cTriggerCard[Index].SetPositionX(100.0f + (Index * 150.0f));
		cTriggerCard[Index].SetPositionY(TRIGGER_CARD_ROW_POSITION);

		cEffectCard[Index].SetPositionX(100.0f + (Index * 150.0f));
		cEffectCard[Index].SetPositionY(EFFECT_CARD_ROW_POSITION);
	}

}

void CCardManager::Step()
{

}

void CCardManager::Draw()
{
	DrawBox(0, 0, 1280, 720, GetColor(0, 255, 0), -1);

	m_CardHandle = LoadGraph(CARD_HANDLE);

	bool ai = true;

	for (int Index = 0; Index < CARD_MAX; Index++)
	{
		/*DrawBox(cCard[Index].GetPositionX(), cCard[Index].GetPositionY(),
			cCard[Index].GetPositionX() + 100, cCard[Index].GetPositionY() + 120,
			GetColor(255, 0, 0), false);*/

		DrawRotaGraph((int)cTriggerCard[Index].GetPositionX(), (int)cTriggerCard[Index].GetPositionY(),
			2.0f, 0.0f, m_CardHandle, true,false);

		DrawRotaGraph((int)cEffectCard[Index].GetPositionX(), (int)cEffectCard[Index].GetPositionY(),
			2.0f, 0.0f, m_CardHandle, true, false);

	}

}

void CCardManager::Exit()
{

}