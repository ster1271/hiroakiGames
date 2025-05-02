#include "DxLib.h"
#include "../Common.h"
#include "../Log/Log.h"
#include "SceneResult.h"
#include "../System/SoundManager/SoundManager.h"

#include "../Loading/Loading.h"

SceneResult::SceneResult()
{
	stateFunc = (void (SceneBase::*)()) & SceneResult::Load;
}

SceneResult::~SceneResult()
{
	return;
}

//�N���A������
void SceneResult::Init()
{
	SoundManager::SetFadeIn(SoundKind::BGM_END, 0.5f);

	stateFunc = (void (SceneBase::*)()) & SceneResult::Step;
}

//�N���A������
void SceneResult::Load()
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
		stateFunc = (void (SceneBase::*)()) & SceneResult::Init;
	}
}

//�N���A�ʏ폈��
void SceneResult::Step()
{
	if (Log::IsButtonPush(InputButton::Decide))
	{
		stateFunc = (void (SceneBase::*)()) & SceneResult::Fin;
		return;
	}
	stateFunc = (void (SceneBase::*)()) & SceneResult::Draw;

	ExecutionStateFunc();
}

//�N���A�`�揈��
void SceneResult::Draw()
{
	stateFunc = (void (SceneBase::*)()) & SceneResult::Step;
}

//�N���A�㏈��
void SceneResult::Fin()
{
	if (!FadeOutFlag)
	{
		SoundManager::SetFadeOut(SoundKind::BGM_END, 0.5f);

		Loading::FadeIn();
		FadeOutFlag = true;
	}
	if (Loading::IsLoadWait())
	{
		//�I���֐��͂���
		//Fin�Ƃ�DeleteInstance�Ƃ�

		SceneManager::NextSceneID = SCENEID::SCENE_ID_TITLE;
	}
	else
	{
		Draw();
		stateFunc = (void (SceneBase::*)()) & SceneResult::Fin;
	}
}
