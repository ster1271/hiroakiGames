#pragma once

// 0 < x <= 255
constexpr int LOAD_CIRCLE_NUM = 10;

constexpr int FADE_SPEED = 10;

class Loading
{
private:
	enum class State
	{
		NO_TASK,
		Loading_Wait,
		Loading_Start,
		Loading_Now,
		Loading_Fin,
		FadeIn,
		FadeOut,
	};
	static State currentState;
	static int DrawAlpha;
	static int LoadNum;

	static float Load_Angle;

public:
	static void Init();
	static void Load();
	static void Step();
	static void Draw();
	static void Fin();

	static void FadeIn();
	static void FadeOut();

	static void LoadStart();

	static bool IsLoadWait();
	static bool IsLoadFin();

	static void AddLoadNum(int addNum = 1) { LoadNum += addNum; }
	static void ResetLoadNum() { LoadNum = 0; }
};