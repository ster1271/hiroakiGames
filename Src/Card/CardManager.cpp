#include "CardManager.h"

void CCardManager::Init()
{

}

void CCardManager::Load()
{
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
	}

	
}

void CCardManager::Exit()
{

}