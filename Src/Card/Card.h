#pragma once

class CCard
{
private:

	float CardPositionX;
	float CardPositionY;

	int TriggerCard;	// ���������̃J�[�h
	int EffectCard;		// ���ʃJ�[�h

public:

	void SetPositionX(float Position) { CardPositionX = Position; }
	void SetPositionY(float Position) { CardPositionY = Position; }

};
