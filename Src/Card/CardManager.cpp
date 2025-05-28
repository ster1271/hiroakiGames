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
		cCard[Index].SetPositionX(300.0f + (Index * 100.0f));
		cCard[Index].SetPositionY(300.0f);
	}
}

void CCardManager::Step()
{

}

void CCardManager::Draw()
{
	DrawBox(0, 0, 1280, 720, GetColor(0, 255, 0), -1);

	for (int Index = 0; Index < CARD_MAX; Index++)
	{
		DrawBox(cCard[Index].GetPositionX(), cCard[Index].GetPositionY(),
			cCard[Index].GetPositionX() + 100, cCard[Index].GetPositionY() + 120,
			GetColor(255, 0, 0), false);

		/*DrawRotaGraph((int)cCard[Index].GetPositionX(), (int)cCard[Index].GetPositionY(),
			1.0f, 1.0f, m_CardHandle, true,false);*/

		DrawGraph((int)cCard[Index].GetPositionX(), (int)cCard[Index].GetPositionY(), m_CardHandle, false);
		
	}

	DrawRotaGraph(500, 600, 0.8f, 0.0f, m_CardHandle, false);
}

void CCardManager::Exit()
{

}