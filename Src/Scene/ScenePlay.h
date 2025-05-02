#pragma once
#include "DxLib.h"

#include "../Common.h"
#include "Scene.h"

constexpr VECTOR SHOW_STAGE_1_EVENT_CAM_FIRST_POS = { 1000.0f, 300.0f, -1000.0f };
constexpr VECTOR SHOW_STAGE_1_EVENT_CAM_END_POS = { -1000.0f, 300.0f, 600.0f };
constexpr VECTOR SHOW_STAGE_1_EVENT_CAM_FOCUS_POS = { 0.0f, 100.0f, 0.0f };
constexpr float SHOW_STAGE_1_EVENT_CAM_SPEED = 200.0f;

constexpr VECTOR SHOW_STAGE_2_EVENT_CAM_FIRST_POS = { 1000.0f, 300.0f, 1000.0f };
constexpr VECTOR SHOW_STAGE_2_EVENT_CAM_END_POS = { -1000.0f, 300.0f, -600.0f };
constexpr VECTOR SHOW_STAGE_2_EVENT_CAM_FOCUS_POS = { 0.0f, 100.0f, 0.0f };
constexpr float SHOW_STAGE_2_EVENT_CAM_SPEED = 200.0f;

constexpr VECTOR SHOW_TEAM_A_EVENT_CAM_FIRST_POS = { -150.0f, 40.0f, -120.0f };
constexpr VECTOR SHOW_TEAM_A_EVENT_CAM_END_POS = { 150.0f, 40.0f, -120.0f };
constexpr VECTOR SHOW_TEAM_A_EVENT_CAM_FOCUS_POS = { -500.0f, 25.0f, -1000.0f };
constexpr float SHOW_TEAM_A_EVENT_CAM_SPEED = 200.0f;

constexpr VECTOR SHOW_TEAM_B_EVENT_CAM_FIRST_POS = { -150.0f, 40.0f, 120.0f };
constexpr VECTOR SHOW_TEAM_B_EVENT_CAM_END_POS = { 150.0f, 40.0f, 120.0f };
constexpr VECTOR SHOW_TEAM_B_EVENT_CAM_FOCUS_POS = { -500.0f, 25.0f, 1000.0f };
constexpr float SHOW_TEAM_B_EVENT_CAM_SPEED = 200.0f;

constexpr float SHOW_STAGE_STOP_TIME = 1.0f;
constexpr float SHOW_CHARA_STOP_TIME = 1.0f;

class ScenePlay : public SceneBase
{
private:
	enum class State
	{
		Error = -1,
		ShowStage,
		ShowChara,
		Ready,
		Default,
		Finish,

	};

	enum class ShowState
	{
		Error = -1,
		Stage_1,
		Stage_2,
		TeamA,
		TeamB,

	};

	typedef void (ScenePlay::* PlayFunc)();

private:
	bool Debug_View_Flag;

	ShowState showState;
	float ShowStageStopTime;
	float ShowCharaStopTime;

	bool ShowCharaFlag;

	PlayFunc playFunc;

public:
	void Init();
	void Load();
	void Step();
	void Draw();
	void Fin();

	State GetcurrentState();

	void ShowStageFanc();
	void ShowCharaFanc();
	void ReadyFanc();
	void DefaultFanc();
	void FinishFanc();

	ScenePlay();
	~ScenePlay();
};