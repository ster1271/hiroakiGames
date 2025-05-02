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
	//�E�B���h�E�̏�Ԃ�ݒ�
	ChangeWindowMode(false);

	//��ʃT�C�Y��ݒ�
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//SetUseDirect3DVersion(DX_DIRECT3D_9EX);

	//�t���X�N���[���A���`�G�C���A�X���[�h�̐ݒ�
	SetFullSceneAntiAliasingMode(4, 3);

	//MakeScreen�p�̃A���`�G�C���A�X�ݒ�
	SetCreateDrawValidGraphMultiSample(2, 1);

	//����������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//�`�悷��X�N���[���𗠂ɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	/*�ŏ��ɂP�x������鏈��*/
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

	//�Q�[���̃��C�����[�v
	while (ProcessMessage() != -1)
	{
		if (FrameRate::Admin())
		{
			Log::SetNextData();
			Input::DataSet();

			//0�L�[�ŏI��
			if (CheckHitKey(KEY_INPUT_0) && CheckHitKey(KEY_INPUT_LSHIFT))
			{
				break;
			}

			//��ʂ�������
			ClearDrawScreen();

			Time::Step();

			SoundManager::Step();

			// �� ���C���̏���
			if (scene_manager.SceneLoop())
			{
				break;
			}


			DebugString::GetInstance().Draw();

			//FPS�v�Z
			FrameRate::CalcFPS();

			//FPS�\��
			//FrameRate::DrawFPS();

			// 1���[�v�I��
			ScreenFlip();
		}
	}

	/*�Ō�ɂP�x������鏈��*/
	scene_manager.SceneFin();

	DebugString::DeleteInstance();

	SoundManager::Fin();
	Font::Fin();
	Loading::Fin();

	//DxLib�̌㏈��
	DxLib_End();

	return 0;
}