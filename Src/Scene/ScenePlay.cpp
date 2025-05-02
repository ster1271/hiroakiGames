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
#include "../Shader/Shader.h"
#include "../System/SoundManager/SoundManager.h"

#include "../Time/Time.h"

#include "../CollisionManager/CollisionManager.h"

#include "../Font/Font.h"

//シングルトン
#include "../Field/Field.h"
#include "../Field/Sky.h"
#include "../AttackArea/AttackAreaManager/AttackAreaManager.h"
#include "../Character/CharacterManager/CharacterManager.h"
#include "../ObjectManager/ObjectManager.h"
#include "../Camera/CameraManager/CameraManager.h"
#include "../CPU/CPU.h"

#include "../Rule/Rule.h"

#include "../UI/UI_Manager/UI_Manager.h"

#include "../Character/CharacterBase/CharacterBase.h"
#include "../Character/Buff/BuffManager/BuffManager.h"

#include "../WhiteFade/WhiteFade.h"

#include "../Effekseer_wrap/Effekseer_wrap.h"

ScenePlay::ScenePlay()
{
	Debug_View_Flag = false;

	showState = ShowState::Error;
	ShowStageStopTime = 0.0f;
	ShowCharaStopTime = 0.0f;
	ShowCharaFlag = false;

	Debug_View_Flag = false;
	stateFunc = (void (SceneBase::*)()) & ScenePlay::Load;
}

ScenePlay::~ScenePlay()
{
	return;
}

//プレイシーン初期化
void ScenePlay::Init()
{
	Debug_View_Flag = false;

	showState = ShowState::Stage_1;
	ShowStageStopTime = 0.0f;
	ShowCharaStopTime = 0.0f;
	ShowCharaFlag = false;

	SoundManager::SetFadeIn(SoundKind::BGM_BATTLE, 0.5f);

	// カメラ関係======
	CameraManager::GetInstance().SetUpEventCam();
	CameraManager::GetInstance().SetUpButtleCam();
	CameraManager::GetInstance().Init();
	CameraManager::GetInstance().SetNearFar(5.0f, 3500.0f);
	CameraManager::GetInstance().SetEvent(
		SHOW_STAGE_1_EVENT_CAM_FIRST_POS,
		SHOW_STAGE_1_EVENT_CAM_FOCUS_POS,
		SHOW_STAGE_1_EVENT_CAM_END_POS,
		SHOW_STAGE_1_EVENT_CAM_SPEED);

	Field::GetInstance().Init();
	Sky::GetInstance().Init();
	ObjectManager::GetInstance().Init();
	AttackAreaManager::GetInstance().Init();
	CharacterManager::GetInstance().Init();
	BuffManager::GetInstance().Init();
	UI_Manager::GetInstance().Init();
	Rule::GetInstance().Init();
	WhiteFade::GetInstance().Init();

	CPU::GetInstance().Init();

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		CharacterManager::GetInstance().Setcharacter_spider(i);

		std::weak_ptr<CharacterBase> weakChara = CharacterManager::GetInstance().Getcharacter(i);
		if (auto sharedChara = weakChara.lock())
		{
			(*sharedChara).Load();
			(*sharedChara).Init();
			(*sharedChara).SetNoControlFlag(true);
		}
	}

	Time::StopReset(-1);
	Time::SlowReset(-1);

	stateFunc = (void (SceneBase::*)()) & ScenePlay::Step;
}

//プレイシーン初期化
void ScenePlay::Load()
{
	if (!isLoadStart)
	{
		Field::GetInstance().Load();
		Sky::GetInstance().Load();
		ObjectManager::GetInstance().Load();
		AttackAreaManager::GetInstance().Load();

		CharacterManager::GetInstance().Load();
		BuffManager::GetInstance().Load();

		UI_Manager::GetInstance().Load();
		Rule::GetInstance().Load();
		WhiteFade::GetInstance().Load();

		Loading::LoadStart();
		isLoadStart = true;
	}

	if (Loading::IsLoadFin())
	{
		Loading::FadeOut();
		playFunc = &ScenePlay::ShowStageFanc;
		stateFunc = (void (SceneBase::*)()) & ScenePlay::Init;
	}
}

//プレイシーン通常処理
void ScenePlay::Step()
{
	UI_Manager::GetInstance().ClearScreen();

	(this->*playFunc)();

	Rule::GetInstance().Step();
	WhiteFade::GetInstance().Step();

	CPU::GetInstance().Step();

	Field::GetInstance().Step();
	ObjectManager::GetInstance().Step();

	//キャラ操作
	CharacterManager::GetInstance().Step();

	BuffManager::GetInstance().Step();
	if (GetcurrentState() == State::ShowStage ||
		GetcurrentState() == State::ShowChara)
	{
		Sky::GetInstance().SetPos(
			CameraManager::GetInstance().GetActiveCameraPos());
	}
	else
	{
		Sky::GetInstance().SetPos(
			CharacterManager::GetInstance().GetcharaPos(
				Log::GetplayerID()));
	}
	Sky::GetInstance().Step();

	AttackAreaManager::GetInstance().Step();

	CollisionManager::CheckHitAttackArea();
	CollisionManager::CheckHitBindAttack();

	//カメラ
	CameraManager::GetInstance().Step();

	CollisionManager::CameraSpring();

	CharacterManager::GetInstance().SetlastFramePos();

	CharacterManager::GetInstance().UpDate();

	UI_Manager::GetInstance().Step();

	CameraManager::GetInstance().UpDate();

	CEffekseerCtrl::UpdateAutoCamera();

	Draw();
}

//プレイシーン描画処理
void ScenePlay::Draw()
{
	ObjectManager::GetInstance().Draw();
	AttackAreaManager::GetInstance().Draw();

	CharacterManager::GetInstance().Draw();

	Sky::GetInstance().Draw();
	Field::GetInstance().Draw();

	CEffekseerCtrl::Draw();

	//以降UI

	if (GetcurrentState() == State::Default)
	{
		BuffManager::GetInstance().Draw();

		UI_Manager::GetInstance().Draw();

		if (!CharacterManager::GetInstance().GetTargetFlag(Log::GetplayerID()))
		{
			DrawCircleAA(SCREEN_SIZE_X / 2.0f, SCREEN_SIZE_Y / 2.0f,
				1.0f, 20, GetColor(255, 0, 0));
		}

		Font::DrawFormatString(FontType::HGP創英角ポップ体24_10,
			5, 10, GetColor(255, 255, 255),
			"色の違うクモを倒しましょう！");
	}

	if (GetcurrentState() == State::ShowStage)
	{
		if (Log::IsUsePad())
		{
			Font::DrawFormatStringR(FontType::HGP創英角ポップ体64_20,
				SCREEN_SIZE_X - 20, SCREEN_SIZE_Y - 80, GetColor(255, 255, 255),
				"Press A!");
		}
		else
		{
			Font::DrawFormatStringR(FontType::HGP創英角ポップ体64_20,
				SCREEN_SIZE_X - 20, SCREEN_SIZE_Y - 80, GetColor(255, 255, 255),
				"Press Enter!");
		}
	}
	
	Rule::GetInstance().Draw();
	WhiteFade::GetInstance().Draw();

	if (Debug_View_Flag)
	{
		for (int i = 0; i < PLAYER_NUM; i++)
		{
			std::weak_ptr<CharacterBase> weakChara = CharacterManager::GetInstance().Getcharacter(i);
			if (auto sharedChara = weakChara.lock())
			{
				static_cast<Capsule>(*sharedChara).Draw();
			}
		}

		std::weak_ptr<CharacterBase> weakChara = CharacterManager::GetInstance().Getcharacter(Log::GetplayerID());
		if (auto sharedChara = weakChara.lock())
		{
			DebugString::GetInstance().AddFormatString(10, 10,
				"キャラ座標 ( x = %.2f , y = %.2f , z = %.2f )",
				sharedChara->Get_pos().x,
				sharedChara->Get_pos().y,
				sharedChara->Get_pos().z);
		}
		DebugString::GetInstance().AddFormatString(10, 30,
			"カメラ座標 ( x = %.2f , y = %.2f , z = %.2f )",
			CameraManager::GetInstance().GetActiveCameraPos().x,
			CameraManager::GetInstance().GetActiveCameraPos().y,
			CameraManager::GetInstance().GetActiveCameraPos().z);

		DebugString::GetInstance().AddFormatString(10, 70,
			"BackSpace で表示/非表示");

		DebugString::GetInstance().AddFormatString(10, 250,
			"Eを押すと移動できるようになった\nQで拘束攻撃なんだけどつくりかけ");

		DebugString::GetInstance().AddFormatString(10, 290,
			"フィールド変えたんだけど\n壁が描画できない");

		DebugString::GetInstance().AddFormatString(10, 330,
			"近づいたとこだけ描画したい");


		for (int i = 0; i < PLAYER_NUM; i++)
		{
			std::weak_ptr<CharacterBase> weakChara = CharacterManager::GetInstance().Getcharacter(i);
			if (auto sharedChara = weakChara.lock())
			{
				sharedChara->DebugDraw();
			}
		}

		Shader::NumDraw();
	}
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
		Field::GetInstance().Fin();
		Sky::GetInstance().Fin();
		ObjectManager::GetInstance().Fin();
		AttackAreaManager::GetInstance().Fin();
		CharacterManager::GetInstance().Fin();
		BuffManager::GetInstance().Fin();
		UI_Manager::GetInstance().Fin();
		Rule::GetInstance().Fin();
		WhiteFade::GetInstance().Fin();

		CameraManager::GetInstance().EndEvent();
		CameraManager::GetInstance().Fin();

		CPU::GetInstance().Fin();

		Field::DeleteInstance();
		Sky::DeleteInstance();
		ObjectManager::DeleteInstance();
		AttackAreaManager::DeleteInstance();
		CharacterManager::DeleteInstance();
		BuffManager::DeleteInstance();
		UI_Manager::DeleteInstance();
		Rule::DeleteInstance();
		WhiteFade::DeleteInstance();

		CameraManager::DeleteInstance();

		SceneManager::NextSceneID = SCENEID::SCENE_ID_RESULT;
	}
	else
	{
		Step();
		stateFunc = (void (SceneBase::*)()) & ScenePlay::Fin;
	}
}

ScenePlay::State ScenePlay::GetcurrentState()
{
	if (playFunc == &ScenePlay::ShowStageFanc)
		return State::ShowStage;
	if (playFunc == &ScenePlay::ShowCharaFanc)
		return State::ShowChara;
	if (playFunc == &ScenePlay::ReadyFanc)
		return State::Ready;
	if (playFunc == &ScenePlay::DefaultFanc)
		return State::Default;
	if (playFunc == &ScenePlay::FinishFanc)
		return State::Finish;

	return State::Error;
}

void ScenePlay::ShowStageFanc()
{
	if (CameraManager::GetInstance().IsEndMoveEvent())
	{
		if (ShowStageStopTime < SHOW_CHARA_STOP_TIME)
		{
			ShowStageStopTime += Time::GetRoleDelta(-1);

			if (ShowStageStopTime >= SHOW_CHARA_STOP_TIME)
			{
				WhiteFade::GetInstance().FadeIn();
			}
		}
		else
		{
			if (WhiteFade::GetInstance().IsWhite())
			{
				if (showState == ShowState::Stage_1)
				{
					CameraManager::GetInstance().SetEvent(
						SHOW_STAGE_2_EVENT_CAM_FIRST_POS,
						SHOW_STAGE_2_EVENT_CAM_FOCUS_POS,
						SHOW_STAGE_2_EVENT_CAM_END_POS,
						SHOW_STAGE_2_EVENT_CAM_SPEED);
					showState = ShowState::Stage_2;

					ShowStageStopTime = 0.0f;

					WhiteFade::GetInstance().FadeOut();
				}
				else if (showState == ShowState::Stage_2)
				{
					CameraManager::GetInstance().SetEvent(
						SHOW_STAGE_1_EVENT_CAM_FIRST_POS,
						SHOW_STAGE_1_EVENT_CAM_FOCUS_POS,
						SHOW_STAGE_1_EVENT_CAM_END_POS,
						SHOW_STAGE_1_EVENT_CAM_SPEED);
					showState = ShowState::Stage_1;

					ShowStageStopTime = 0.0f;

					WhiteFade::GetInstance().FadeOut();
				}
			}
		}
	}

	if (Log::IsButtonPush(InputButton::Decide))
	{
		if (!ShowCharaFlag)
		{
			ShowCharaFlag = true;
			WhiteFade::GetInstance().FadeIn();
			return;
		}
	}

	if (ShowCharaFlag)
	{
		if (WhiteFade::GetInstance().IsWhite())
		{
			CameraManager::GetInstance().SetEvent(
				SHOW_TEAM_A_EVENT_CAM_FIRST_POS,
				SHOW_TEAM_A_EVENT_CAM_FOCUS_POS,
				SHOW_TEAM_A_EVENT_CAM_END_POS,
				SHOW_TEAM_A_EVENT_CAM_SPEED);
			showState = ShowState::TeamA;

			WhiteFade::GetInstance().FadeOut();

			playFunc = &ScenePlay::ShowCharaFanc;
			return;
		}
	}
}

void ScenePlay::ShowCharaFanc()
{
	if (CameraManager::GetInstance().IsEndMoveEvent())
	{
		if (ShowCharaStopTime < SHOW_CHARA_STOP_TIME)
		{
			ShowCharaStopTime += Time::GetRoleDelta(-1);

			if (ShowCharaStopTime >= SHOW_CHARA_STOP_TIME)
			{
				WhiteFade::GetInstance().FadeIn();
			}
		}
		else
		{
			if (WhiteFade::GetInstance().IsWhite())
			{
				if (showState == ShowState::TeamA)
				{
					CameraManager::GetInstance().SetEvent(
						SHOW_TEAM_B_EVENT_CAM_FIRST_POS,
						SHOW_TEAM_B_EVENT_CAM_FOCUS_POS,
						SHOW_TEAM_B_EVENT_CAM_END_POS,
						SHOW_TEAM_B_EVENT_CAM_SPEED);
					showState = ShowState::TeamB;

					ShowCharaStopTime = 0.0f;

					WhiteFade::GetInstance().FadeOut();
				}
				else if (showState == ShowState::TeamB)
				{
					ShowCharaStopTime = 0.0f;

					showState = ShowState::Error;

					CameraManager::GetInstance().EndEvent();

					Rule::GetInstance().ReadyStart();

					WhiteFade::GetInstance().FadeOut();

					playFunc = &ScenePlay::ReadyFanc;
					return;
				}
			}
		}
	}
}

void ScenePlay::ReadyFanc()
{
	if (Rule::GetInstance().IsStartGame())
	{
		CharacterManager::GetInstance().SetNoControlFlag(false);

		playFunc = &ScenePlay::DefaultFanc;
		return;
	}
}

void ScenePlay::DefaultFanc()
{
	if (Rule::GetInstance().IsEndGame())
	{
		Rule::GetInstance().Judge();
		CharacterManager::GetInstance().SetNoControlFlag(true);

		playFunc = &ScenePlay::FinishFanc;
		return;
	}
}

void ScenePlay::FinishFanc()
{
	if (Rule::GetInstance().IsFinPlay())
	{
		stateFunc = (void (SceneBase::*)()) & ScenePlay::Fin;
		return;
	}
}
