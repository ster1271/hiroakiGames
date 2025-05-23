#include "DxLib.h"
#include "../Common.h"
#include "SceneTitle.h"
#include "../System/SoundManager/SoundManager.h"

#include "../Time/Time.h"

#include "../Log/Log.h"

#include "../Loading/Loading.h"

#include "../Font/Font.h"

//�V���O���g��

SceneTitle::SceneTitle()
{
	endFlag = false;

	stateFunc = (void (SceneBase::*)()) & SceneTitle::Load;
}

SceneTitle::~SceneTitle()
{
	return;
}

//�^�C�g��������
void SceneTitle::Init()
{
	endFlag = false;

	SoundManager::SetFadeIn(SoundKind::BGM_TITLE, 0.5f);

	m_Time = 0;
	m_Count = 0;

	stateFunc = (void (SceneBase::*)()) & SceneTitle::Step;
}

//�^�C�g���ǂݍ���
void SceneTitle::Load()
{
	if (!isLoadStart)
	{
		//�����Ƀ��[�h�֐���S������Ă�

		Loading::LoadStart();
		isLoadStart = true;
	}
	if (Loading::IsLoadFin())
	{
		Loading::FadeOut();
		stateFunc = (void (SceneBase::*)()) & SceneTitle::Init;
	}
}

//�^�C�g���ʏ폈��
void SceneTitle::Step()
{
	if (Log::IsButtonPush(InputButton::Decide))
	{
		stateFunc = (void (SceneBase::*)()) & SceneTitle::Fin;
		return;
	}
	
	m_Time++;
	if (m_Time % 60 == 0) {
		m_Count++;

	}

	Draw();
}

//�^�C�g���`�揈��
void SceneTitle::Draw()
{
	Font::DrawFormatString(FontType::HGP�n�p�p�|�b�v��24_10,
		5, 10, GetColor(255, 255, 255),
		"�^�C�g��");

	if (m_Count >= 1) {
		Font::DrawFormatString(FontType::HGP�n�p�p�|�b�v��128_20,
			250, 580, GetColor(255, 255, 255),
			"T");
	}

	if (m_Count >= 2) {
		Font::DrawFormatString(FontType::HGP�n�p�p�|�b�v��128_20,
			350, 580, GetColor(255, 255, 255),
			"I");
	}

	if (m_Count >= 3) {
		Font::DrawFormatString(FontType::HGP�n�p�p�|�b�v��128_20,
			450, 580, GetColor(255, 255, 255),
			"T");
	}

	if (m_Count >= 4) {
		Font::DrawFormatString(FontType::HGP�n�p�p�|�b�v��128_20,
			550, 580, GetColor(255, 255, 255),
			"L");
	}

	if (m_Count >= 5) {
		Font::DrawFormatString(FontType::HGP�n�p�p�|�b�v��128_20,
			650, 580, GetColor(255, 255, 255),
			"E");
	}


}

//�^�C�g���㏈��
void SceneTitle::Fin()
{
	if (!FadeOutFlag)
	{
		Loading::FadeIn();
		FadeOutFlag = true;

		SoundManager::SetFadeOut(SoundKind::BGM_TITLE, 0.5f);
	}
	if (Loading::IsLoadWait())
	{
		//�I���֐��͂���
		//Fin�Ƃ�DeleteInstance�Ƃ�

		if (endFlag)
			SceneManager::NextSceneID = SCENEID::SCENE_ID_END;
		else
			SceneManager::NextSceneID = SCENEID::SCENE_ID_PLAY;
	}
	else
	{
		Step();
		stateFunc = (void (SceneBase::*)()) & SceneTitle::Fin;
	}
}
