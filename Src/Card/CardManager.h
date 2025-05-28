#pragma once

#include "Card.h"

#define CARD_MAX (12)
#define TRIGGER_CARD_ROW_POSITION (100)	// ���������J�[�h�̗�̍��W
#define EFFECT_CARD_ROW_POSITION (100)	// ���ʃJ�[�h�̗�̍��W

#define CARD_HANDLE ("Data/Card/Card.png")
#define CARD_FLAME_HANDLE ("Data/Card/CardFlame.png")

class CCardManager
{
private:

	CCard cCard[CARD_MAX];

	int m_CardHandle;
	int m_CardFlameHandle;

public:

	void Init();

	void Load();

	void Step();

	void Draw();

	void Exit();

};
