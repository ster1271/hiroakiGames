#include "DxLib.h"
#include "../Common.h"
#include "../Log/Log.h"
#include "SceneResult.h"
#include "../System/SoundManager/SoundManager.h"

#include "../Loading/Loading.h"
#include "../Font/Font.h"

SceneResult::SceneResult()
{
	stateFunc = (void (SceneBase::*)()) & SceneResult::Load;
}

SceneResult::~SceneResult()
{
	return;
}

//クリア初期化
void SceneResult::Init()
{
	SoundManager::SetFadeIn(SoundKind::BGM_END, 0.5f);

	stateFunc = (void (SceneBase::*)()) & SceneResult::Step;
}

//クリア初期化
void SceneResult::Load()
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
		stateFunc = (void (SceneBase::*)()) & SceneResult::Init;
	}
}

//クリア通常処理
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

//クリア描画処理
void SceneResult::Draw()
{
	stateFunc = (void (SceneBase::*)()) & SceneResult::Step;
	Font::DrawFormatString(FontType::HGP創英角ポップ体24_10,
		5, 10, GetColor(255, 255, 255),
		"リザルト");
}

//クリア後処理
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
		//終了関数はここ
		//FinとかDeleteInstanceとか

		SceneManager::NextSceneID = SCENEID::SCENE_ID_TITLE;
	}
	else
	{
		Draw();
		stateFunc = (void (SceneBase::*)()) & SceneResult::Fin;
	}
}
