#pragma once

//設定フレームレート
#define FRAME_RATE 60

//1フレームの時間（ミリ秒）
#define FRAME_TIME (1000 / FRAME_RATE)

class FrameRate
{
private:
	static float deltaTime;			//経過時間
	static ULONGLONG currentTime;	//前回のフレーム実行時の時間
	static ULONGLONG lastFrateTime;	//前回のフレーム実行時の時間

	static int count;			//フレームカウント用
	static ULONGLONG calcFpsTime;		//FPSを計算した時間
	static float fps;				//計測したFPS（表示用）

public:
	static float GetDeltaTime() { return deltaTime; }

	static void Init();

	static bool Admin();	//FPS管理関数

	static void CalcFPS();			//FPS計算

	static void DrawFPS();			//FPS表示（デバック用）
};

