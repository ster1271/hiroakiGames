#include "DxLib.h"
#include "../Common.h"
#include "../Log/Log.h"
#include "SceneResult.h"
#include "../System/SoundManager/SoundManager.h"

#include "../Loading/Loading.h"

SceneResult::SceneResult()
{
	resultImageHandle = -1;

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
		SetUseASyncLoadFlag(TRUE);
		resultImageHandle = LoadGraph(RESULT_IMAGE_PATH);
		Loading::AddLoadNum();
		SetUseASyncLoadFlag(FALSE);

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
	DrawGraph(0, 0, resultImageHandle, true);

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
		DeleteGraph(resultImageHandle);

		SceneManager::NextSceneID = SCENEID::SCENE_ID_TITLE;
	}
	else
	{
		Draw();
		stateFunc = (void (SceneBase::*)()) & SceneResult::Fin;
	}
}
