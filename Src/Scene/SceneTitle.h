#pragma once
#include "DxLib.h"
#include "Scene.h"

constexpr char TITLE_IMAGE_PATH[128] = "Data/Image/BUFFighterタイトルロゴ.png";
constexpr char MENU_IMAGE_PATH[128] = "Data/Image/操作説明.png";

constexpr char TITLE_BACK_MODEL_PATH[128] = "model/自作モデル/titleBack/titleBack.mv1";
constexpr char TITLE_OUT_MODEL_PATH[128] = "model/自作モデル/titleBack/titleOut.mv1";

constexpr float TITLE_OUT_POS_Y = -100.f;
constexpr float TITLE_IN_POS_Y = 200.f;

constexpr float TITLE_IN_SPEED = 150.f;
constexpr float TITLE_OUT_SPEED = 1500.f;

constexpr VECTOR TITLE_CAM_BACK_POS = { 0.0f, 150.0f, -600.0f };
constexpr float TITLE_CAM_BACK_SPEED = 500.0f;
constexpr VECTOR TITLE_CAM_END_POS = { 0.0f, 100.0f, 2500.0f };
constexpr float TITLE_CAM_END_SPEED = 3000.0f;

//シーン情報
class SceneTitle : public SceneBase
{
private:
	enum class State
	{
		Error = -1,
		Intro,
		Default,
		CameraBack,
		ChangeScene,

	};

	typedef void (SceneTitle::* TitleFunc)();

private:
	bool endFlag;
	bool startFlag;

	int titleImageHandle;
	VECTOR titleImagePos;

	int titleBackModel;
	int titleOutModel;

	int menuHandle;
	bool menuFlag;

	TitleFunc titleFunc;

protected:
	void Init();
	void Load();
	void Step();
	void Draw();
	void Fin();

	State GetcurrentState();

	void IntroFanc();
	void DefaultFanc();
	void CameraBackFanc();
	void ChangeSceneFanc();

public:
	SceneTitle();
	~SceneTitle();
};