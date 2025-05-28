#include <math.h>
#include <list>

#include "DxLib.h"
#include "../Common.h"
#include "../Log/Log.h"
#include "../DebugString/DebugString.h"
#include "../Loading/Loading.h"
#include "ScenePlay.h"
#include "../Vector/Vector.h"
#include "../FrameRate/FrameRate.h"
#include "../System/SoundManager/SoundManager.h"

#include "../Time/Time.h"

#include "../Font/Font.h"

//シングルトン

ScenePlay::ScenePlay()
{
	stateFunc = (void (SceneBase::*)()) & ScenePlay::Load;
}

ScenePlay::~ScenePlay()
{
	return;
}

//プレイシーン初期化
void ScenePlay::Init()
{
	SoundManager::SetFadeIn(SoundKind::BGM_BATTLE, 0.5f);

	cStage.Init();

	Time::StopReset(-1);
	Time::SlowReset(-1);

	stateFunc = (void (SceneBase::*)()) & ScenePlay::Step;
}

//プレイシーン初期化
void ScenePlay::Load()
{
	if (!isLoadStart)
	{
		//ここにロード関数を全部いれてね
		
		cStage.Load();

		Loading::LoadStart();
		isLoadStart = true;
	}

	if (Loading::IsLoadFin())
	{
		Loading::FadeOut();
		stateFunc = (void (SceneBase::*)()) & ScenePlay::Init;
	}
}

//プレイシーン通常処理
void ScenePlay::Step()
{
	
	cStage.Step();

	if (Log::IsButtonPush(InputButton::Decide))
	{
		stateFunc = (void (SceneBase::*)()) & ScenePlay::Fin;
		return;
	}

	Draw();
}

//プレイシーン描画処理
void ScenePlay::Draw()
{

	cStage.Draw();

	//以降UI
	Font::DrawFormatString(FontType::HGP創英角ポップ体24_10,
		5, 10, GetColor(255, 255, 255),
		"プレイ");
}

//プレイシーン後処理
void ScenePlay::Fin()
{
	if (!FadeOutFlag)
	{
		Loading::FadeIn();
		FadeOutFlag = true;

		SoundManager::SetFadeOut(SoundKind::BGM_BATTLE, 0.5f);
	}
	if (Loading::IsLoadWait())
	{
		//終了関数はここ
		//FinとかDeleteInstanceとか

		cStage.Exit();
	

		SceneManager::NextSceneID = SCENEID::SCENE_ID_RESULT;
	}
	else
	{
		Step();
		stateFunc = (void (SceneBase::*)()) & ScenePlay::Fin;
	}
}