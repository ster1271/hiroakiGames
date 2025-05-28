#pragma once

#include "Card.h"
#include "../Loading/Loading.h"

#define CARD_MAX (6)
#define TRIGGER_CARD_ROW_POSITION (350)	// ���������J�[�h�̗�̍��W
#define EFFECT_CARD_ROW_POSITION (600)	// ���ʃJ�[�h�̗�̍��W

#define CARD_HANDLE ("Data/Card/Card.png")
#define CARD_FLAME_HANDLE ("Data/Card/CardFlame.png")

class CCardManager
{
private:

	CCard cTriggerCard[CARD_MAX];
	CCard cEffectCard[CARD_MAX];

	int m_CardHandle;
	int m_CardFlameHandle;

public:

	void Init();

	void Load();

	void Step();

	void Draw();

	void Exit();

};
