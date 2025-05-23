#pragma once

#include "Card.h"

#define CARD_MAX (12)
#define TRIGGER_CARD_ROW_POSITION (100)	// ���������J�[�h�̗�̍��W
#define EFFECT_CARD_ROW_POSITION (100)	// ���ʃJ�[�h�̗�̍��W

class CCardManager
{
private:

	CCard cCard[CARD_MAX];

public:

	void Init();

	void Load();

	void Step();

	void Draw();

	void Exit();

};
