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

//�V���O���g��

ScenePlay::ScenePlay()
{
	stateFunc = (void (SceneBase::*)()) & ScenePlay::Load;
}

ScenePlay::~ScenePlay()
{
	return;
}

//�v���C�V�[��������
void ScenePlay::Init()
{
	SoundManager::SetFadeIn(SoundKind::BGM_BATTLE, 0.5f);

	cStage.Init();

	Time::StopReset(-1);
	Time::SlowReset(-1);

	stateFunc = (void (SceneBase::*)()) & ScenePlay::Step;
}

//�v���C�V�[��������
void ScenePlay::Load()
{
	if (!isLoadStart)
	{
		//�����Ƀ��[�h�֐���S������Ă�
		
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

//�v���C�V�[���ʏ폈��
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

//�v���C�V�[���`�揈��
void ScenePlay::Draw()
{

	cStage.Draw();

	//�ȍ~UI
	Font::DrawFormatString(FontType::HGP�n�p�p�|�b�v��24_10,
		5, 10, GetColor(255, 255, 255),
		"�v���C");
}

//�v���C�V�[���㏈��
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
		//�I���֐��͂���
		//Fin�Ƃ�DeleteInstance�Ƃ�

		cStage.Exit();
	

		SceneManager::NextSceneID = SCENEID::SCENE_ID_RESULT;
	}
	else
	{
		Step();
		stateFunc = (void (SceneBase::*)()) & ScenePlay::Fin;
	}
}