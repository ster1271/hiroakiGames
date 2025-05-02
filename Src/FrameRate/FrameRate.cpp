#include "DxLib.h"
#include "FrameRate.h"
#include "../Font/Font.h"
#include "../Common.h"

float FrameRate::deltaTime;
ULONGLONG FrameRate::currentTime;
ULONGLONG FrameRate::lastFrateTime;
int FrameRate::count;
ULONGLONG FrameRate::calcFpsTime;
float FrameRate::fps;

void FrameRate::Init()
{
	deltaTime = 0.0f;
	currentTime = static_cast<ULONGLONG>(0);
	lastFrateTime = static_cast<ULONGLONG>(0);
	count = 0;
	calcFpsTime = static_cast<ULONGLONG>(0);
	fps = 0.0f;
}

bool FrameRate::Admin()
{
	Sleep(1);	//システムに処理を返す

	//現在の時間を取得
	currentTime = GetNowSysPerformanceCount();

	//最初のループなら
	// ナンバーフォントデータを初期化
	//現在の時間を、FPSの計算をした時間に設定
	if (calcFpsTime == (ULONGLONG)0)
	{
		calcFpsTime = lastFrateTime = currentTime;
		fps = (float)FRAME_RATE;
	}

	//現在の時間が、前回のフレーム時より
	//FRAME_TIME以上経過していたら処理を実行する
	ULONGLONG work = currentTime - lastFrateTime;
	deltaTime = static_cast<float>(work) / 10000000.0f;
	if (deltaTime >= 0.05f)
	{
		deltaTime = 0.05f;
	}
	if (deltaTime * 1000.0f >= FRAME_TIME)
	{
		//フレーム実行時の時間を更新
		lastFrateTime = currentTime;

		//フレーム数をカウント
		count++;

		return true;
	}

	return false;
}

void FrameRate::CalcFPS()
{
	//前回のFPSを計算した時間からの経過時間を求める
	ULONGLONG difTime = ConvSysPerformanceCountToMilliSeconds(currentTime - calcFpsTime);

	//前回のFPSを計算した時間から
	//1秒以上経過していたらFPSを計算する
	if (difTime > 1000)
	{
		//フレーム回数をミリ秒に合わせる
		//小数まで出したいのでfloatにキャスト
		float frameCount = (float)(count * 1000.0f);

		//FPSを求める
		//理想の数値は 60000 / 1000 で 60 となる	(FRAME_RATE = 60 の場合)
		fps = frameCount / difTime;

		//フレームレートカウントをクリア
		count = 0;

		//FPSを計算した時間を更新
		calcFpsTime = currentTime;
	}
}

//FPS表示（デバック用）
void FrameRate::DrawFPS()
{
	int fontWidth = GetDrawFormatStringWidthToHandle(Font::GetfontHandle(FontType::HGP創英角ポップ体), "%.2f", fps);
	DrawFormatStringToHandle(SCREEN_SIZE_X - fontWidth, SCREEN_SIZE_Y - 20,
		GetColor(255, 255, 255), Font::GetfontHandle(FontType::HGP創英角ポップ体),
		"%.2f", fps);
	DrawFormatStringToHandle(0, SCREEN_SIZE_Y - 20,
		GetColor(255, 255, 255), Font::GetfontHandle(FontType::HGP創英角ポップ体),
		"%.5f", deltaTime);
}
