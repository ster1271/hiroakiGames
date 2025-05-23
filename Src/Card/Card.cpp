#include "Card.h"

#define CARD_HANDLE ("Data/Card/Card.png")
#define CARD_FLAME_HANDLE ("Data/Card/CardFlame.png")

void CCard::Init()
{
	m_CardPositionX = 0;
	m_CardPositionY = 0;
	m_CardHandle = 0;
	m_CardFlameHandle = 0;
	m_IsActive = false;
	m_eCardType = ENPTY_CARD;

}

void CCard::Load()
{
	m_CardHandle = LoadGraph(CARD_HANDLE);
}

void CCard::Step()
{

}

void CCard::Draw()
{

}

void CCard::Exit()
{

}