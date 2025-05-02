#include "DxLib.h"
#include "../Common.h"
#include "SceneTitle.h"
#include "../System/SoundManager/SoundManager.h"

#include "../Time/Time.h"

#include "../Log/Log.h"

#include "../Loading/Loading.h"

#include "../Font/Font.h"

//シングルトン
#include "../Field/Sky.h"
#include "../Camera/CameraManager/CameraManager.h"

#include "../Effekseer_wrap/Effekseer_wrap.h"

SceneTitle::SceneTitle()
{
	endFlag = false;

	titleOutModel = -1;
	titleImageHandle = -1;
	menuHandle = -1;
	menuFlag = false;

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
	startFlag = false;

	SoundManager::SetFadeIn(SoundKind::BGM_TITLE, 0.5f);
	menuFlag = false;

	// カメラ関係======
	CameraManager::GetInstance().SetUpEventCam();
	CameraManager::GetInstance().Init();
	CameraManager::GetInstance().SetNearFar(5.0f, 3500.0f);
	CameraManager::GetInstance().SetEvent(VGet(0.0f, 100.0f, -500.0f), 
		VGet(0.0f, 80.0f, 3000.0f), VGet(0.0f, 100.0f, -500.0f), 0.0f);

	titleImagePos = VGet(SCREEN_SIZE_X / 2.0f, TITLE_OUT_POS_Y, 0.0f);

	MV1SetRotationXYZ(titleBackModel, VGet(0.0f, 0.0f, 0.0f));

	MV1SetPosition(titleBackModel, VGet(0.0f, 0.0f, 0.0f));

	MV1SetRotationXYZ(titleOutModel, VGet(0.0f, 0.0f, 0.0f));

	MV1SetPosition(titleOutModel, VGet(0.0f, 0.0f, 0.0f));

	Sky::GetInstance().Init();

	titleFunc = &SceneTitle::IntroFanc;
	stateFunc = (void (SceneBase::*)()) & SceneTitle::Step;
}

//タイトル読み込み
void SceneTitle::Load()
{
	if (!isLoadStart)
	{
		Sky::GetInstance().Load();

		SetUseASyncLoadFlag(TRUE);
		titleImageHandle = LoadGraph(TITLE_IMAGE_PATH);
		Loading::AddLoadNum();
		menuHandle = LoadGraph(MENU_IMAGE_PATH);
		Loading::AddLoadNum();

		titleBackModel = MV1LoadModel(TITLE_BACK_MODEL_PATH);
		Loading::AddLoadNum();

		titleOutModel = MV1LoadModel(TITLE_OUT_MODEL_PATH);
		Loading::AddLoadNum();

		SetUseASyncLoadFlag(FALSE);

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
	(this->*titleFunc)();

	Sky::GetInstance().SetPos(
		CameraManager::GetInstance().GeteventCam()->GetCameraPos());
	Sky::GetInstance().Step();

	CameraManager::GetInstance().Step();
	CameraManager::GetInstance().UpDate();

	CEffekseerCtrl::UpdateAutoCamera();
	
	Draw();
}

//タイトル描画処理
void SceneTitle::Draw()
{
	Sky::GetInstance().Draw();

	MV1DrawModel(titleOutModel);
	MV1DrawModel(titleBackModel);

	CEffekseerCtrl::Draw();

	if (GetcurrentState() == State::Default)
	{
		if (Log::IsUsePad())
		{
			Font::DrawFormatStringC(FontType::HGP創英角ポップ体64_20,
				SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 - 20, GetColor(255, 255, 255),
				"A : ゲームスタート!");
			Font::DrawFormatStringC(FontType::HGP創英角ポップ体64_20,
				SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 + 70, GetColor(255, 255, 255),
				"Start : 操作説明");
			Font::DrawFormatStringC(FontType::HGP創英角ポップ体64_20,
				SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 + 150, GetColor(255, 255, 255),
				"Back : 終了");
		}
		else
		{
			Font::DrawFormatStringC(FontType::HGP創英角ポップ体64_20,
				SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 - 20, GetColor(255, 255, 255),
				"Enter : ゲームスタート!");
			Font::DrawFormatStringC(FontType::HGP創英角ポップ体64_20,
				SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 + 70, GetColor(255, 255, 255),
				"Esc : 操作説明");
			Font::DrawFormatStringC(FontType::HGP創英角ポップ体64_20,
				SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 + 150, GetColor(255, 255, 255),
				"BackSpace : 終了");
		}
	}

	DrawRotaGraphF(titleImagePos.x, titleImagePos.y, 1.5, 0.0, titleImageHandle, true);

	if (menuFlag)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 0.8, 0.0,
			menuHandle, true);
	}
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
		DeleteGraph(titleImageHandle);
		DeleteGraph(menuHandle);
		if (titleBackModel != -1)
		{
			MV1DeleteModel(titleBackModel);
			titleBackModel = -1;
		}
		if (titleOutModel != -1)
		{
			MV1DeleteModel(titleOutModel);
			titleOutModel = -1;
		}

		Sky::GetInstance().Fin();

		CameraManager::GetInstance().EndEvent();
		CameraManager::GetInstance().Fin();

		Sky::DeleteInstance();
		CameraManager::DeleteInstance();

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

SceneTitle::State SceneTitle::GetcurrentState()
{
	if (titleFunc == &SceneTitle::IntroFanc)
		return State::Intro;
	if (titleFunc == &SceneTitle::DefaultFanc)
		return State::Default;
	if (titleFunc == &SceneTitle::CameraBackFanc)
		return State::CameraBack;
	if (titleFunc == &SceneTitle::ChangeSceneFanc)
		return State::ChangeScene;

	return State::Error;
}

void SceneTitle::IntroFanc()
{
	if (Log::IsButtonPush(InputButton::Back))
	{
		endFlag = true;
		stateFunc = (void (SceneBase::*)()) & SceneTitle::Fin;
		return;
	}

	if (Log::IsButtonPush(InputButton::Menu) || Log::IsButtonPush(InputButton::Decide))
	{
		titleImagePos.y = TITLE_IN_POS_Y;
		titleFunc = &SceneTitle::DefaultFanc;
		return;
	}

	titleImagePos.y += TITLE_IN_SPEED * Time::GetRoleDelta(-1);

	if (titleImagePos.y >= TITLE_IN_POS_Y)
	{
		titleImagePos.y = TITLE_IN_POS_Y;
		titleFunc = &SceneTitle::DefaultFanc;
	}
}

void SceneTitle::DefaultFanc()
{
	if (Log::IsButtonPush(InputButton::Back))
	{
		endFlag = true;
		stateFunc = (void (SceneBase::*)()) & SceneTitle::Fin;
		return;
	}

	if (Log::IsButtonPush(InputButton::Menu))
	{
		menuFlag = !menuFlag;
	}

	if (Log::IsButtonPush(InputButton::Decide))
	{
		SoundManager::Play(SoundKind::SE_TITLE_BUTTON, DX_PLAYTYPE_BACK);

		CameraManager::GetInstance().GeteventCam()->
			Setnext(TITLE_CAM_BACK_POS, TITLE_CAM_BACK_SPEED);
		titleFunc = &SceneTitle::CameraBackFanc;
		return;
	}
}

void SceneTitle::CameraBackFanc()
{
	if (titleImagePos.y > TITLE_OUT_POS_Y)
	{
		titleImagePos.y -= TITLE_OUT_SPEED * Time::GetRoleDelta(-1);

		if (titleImagePos.y <= TITLE_OUT_POS_Y)
		{
			titleImagePos.y = TITLE_OUT_POS_Y;
		}
	}

	if (CameraManager::GetInstance().GeteventCam()->IsEndMove())
	{
		CameraManager::GetInstance().GeteventCam()->
			Setnext(TITLE_CAM_END_POS, TITLE_CAM_END_SPEED);

		titleFunc = &SceneTitle::ChangeSceneFanc;

		stateFunc = (void (SceneBase::*)()) & SceneTitle::Fin;
	}
}

void SceneTitle::ChangeSceneFanc()
{
	if (titleImagePos.y > TITLE_OUT_POS_Y)
	{
		titleImagePos.y -= TITLE_OUT_SPEED * Time::GetRoleDelta(-1);

		if (titleImagePos.y <= TITLE_OUT_POS_Y)
		{
			titleImagePos.y = TITLE_OUT_POS_Y;
		}
	}
}
