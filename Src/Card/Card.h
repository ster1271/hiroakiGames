#pragma once

class CCard
{
private:

	float CardPositionX;
	float CardPositionY;

	int TriggerCard;	// 発動条件のカード
	int EffectCard;		// 効果カード

public:

	void SetPositionX(float Position) { CardPositionX = Position; }
	void SetPositionY(float Position) { CardPositionY = Position; }

};
