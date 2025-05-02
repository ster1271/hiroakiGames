#include "DxLib.h"
#include "Common.h"
#include "Log/Log.h"
#include "Input/Input.h"
#include "System/SoundManager/SoundManager.h"
#include "FrameRate/FrameRate.h"
#include "Font/Font.h"
#include "Scene/Scene.h"
#include "Loading/Loading.h"

#include "Time/Time.h"

#include "DebugString/DebugString.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//ウィンドウの状態を設定
	ChangeWindowMode(false);

	//画面サイズを設定
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//SetUseDirect3DVersion(DX_DIRECT3D_9EX);

	//フルスクリーンアンチエイリアスモードの設定
	SetFullSceneAntiAliasingMode(4, 3);

	//MakeScreen用のアンチエイリアス設定
	SetCreateDrawValidGraphMultiSample(2, 1);

	//初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//描画するスクリーンを裏に設定
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	/*最初に１度だけやる処理*/
	DebugString::GetInstance();

	InputButtonInfo::Init();
	Log::Init();
	Input::Init();
	Input::Mouse_Disappear();

	Font::Init();

	SoundManager::LoadAllData();
	SoundManager::Init();

	Loading::Init();

	SceneManager scene_manager;
	scene_manager.SceneInit();

	FrameRate::Init();
	Time::Init();

	//ゲームのメインループ
	while (ProcessMessage() != -1)
	{
		if (FrameRate::Admin())
		{
			Log::SetNextData();
			Input::DataSet();

			//0キーで終了
			if (CheckHitKey(KEY_INPUT_0) && CheckHitKey(KEY_INPUT_LSHIFT))
			{
				break;
			}

			//画面を初期化
			ClearDrawScreen();

			Time::Step();

			SoundManager::Step();

			// ↓ メインの処理
			if (scene_manager.SceneLoop())
			{
				break;
			}


			DebugString::GetInstance().Draw();

			//FPS計算
			FrameRate::CalcFPS();

			//FPS表示
			//FrameRate::DrawFPS();

			// 1ループ終了
			ScreenFlip();
		}
	}

	/*最後に１度だけやる処理*/
	scene_manager.SceneFin();

	DebugString::DeleteInstance();

	SoundManager::Fin();
	Font::Fin();
	Loading::Fin();

	//DxLibの後処理
	DxLib_End();

	return 0;
}