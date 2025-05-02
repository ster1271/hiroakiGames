#include "DxLib.h"
#include "../Common.h"
#include "SceneTitle.h"
#include "../System/SoundManager/SoundManager.h"

#include "../Time/Time.h"

#include "../Log/Log.h"

#include "../Loading/Loading.h"

#include "../Font/Font.h"

//シングルトン

SceneTitle::SceneTitle()
{
	endFlag = false;

	stateFunc = (void (SceneBase::*)()) & SceneTitle::Load;
}

SceneTitle::~SceneTitle()
{
	return;
}

//タイトル初期化
void SceneTitle::Init()
{
	endFlag = false;

	SoundManager::SetFadeIn(SoundKind::BGM_TITLE, 0.5f);



	stateFunc = (void (SceneBase::*)()) & SceneTitle::Step;
}

//タイトル読み込み
void SceneTitle::Load()
{
	if (!isLoadStart)
	{
		//ここにロード関数を全部いれてね

		Loading::LoadStart();
		isLoadStart = true;
	}
	if (Loading::IsLoadFin())
	{
		Loading::FadeOut();
		stateFunc = (void (SceneBase::*)()) & SceneTitle::Init;
	}
}

//タイトル通常処理
void SceneTitle::Step()
{
	if (Log::IsButtonPush(InputButton::Decide))
	{
		stateFunc = (void (SceneBase::*)()) & SceneTitle::Fin;
		return;
	}
	
	Draw();
}

//タイトル描画処理
void SceneTitle::Draw()
{
	
}

//タイトル後処理
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
		//終了関数はここ
		//FinとかDeleteInstanceとか

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
