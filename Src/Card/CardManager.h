#pragma once

#include "Card.h"

#define CARD_MAX (12)
#define TRIGGER_CARD_ROW_POSITION (100)	// 発動条件カードの列の座標
#define EFFECT_CARD_ROW_POSITION (100)	// 効果カードの列の座標

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
