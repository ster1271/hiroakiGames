#pragma once

class CCard
{
public: 
	enum CARD_TYPE
	{
		ENPTY_CARD,		// ���Ƀ^�C�v�����܂��ĂȂ��Ƃ��ɓ����
		TRIGGER_CARD,	// ���������̃J�[�h
		EFFECT_CARD,	// ���ʃJ�[�h

	};

private:

	float m_CardPositionX;
	float m_CardPositionY;

	bool m_IsActive;
	CARD_TYPE m_eCardType;

	int TriggerCard;	
	int EffectCard;		

public:

	void Init();

	void Load();

	void Step();

	void Draw();

	void Exit();

	float GetPositionX() { return m_CardPositionX; }
	float GetPositionY() { return m_CardPositionY; }

	void SetPositionX(float Position) { m_CardPositionX = Position; }
	void SetPositionY(float Position) { m_CardPositionY = Position; }

};
