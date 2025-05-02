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
	
	Draw();
}

//�^�C�g���`�揈��
void SceneTitle::Draw()
{
	
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
