#pragma once
#include "DxLib.h"

enum class SoundKind
{
	NONE = -1,
	BGM_TITLE,
	BGM_BATTLE,
	BGM_END,

	SE_TITLE_BUTTON,
	SE_ATTACK,
	SE_BIND_ATTACK,

	KindNum
};

constexpr char SE_FILE_PATH[(int)SoundKind::KindNum][128] =
{
	"Data/Music/BGM/ぐだぐだコミカル.mp3",
	"Data/Music/BGM/The-Charlatan.ogg",
	"Data/Music/BGM/だらだら日曜日.mp3",

	"Data/Music/SE/決定ボタンを押す22.mp3",
	"Data/Music/SE/平手打ち1_短.wav",
	"Data/Music/SE/本を閉じる1_短.wav"
};

class SoundManager
{
private:
	static int soundHandle[(int)SoundKind::KindNum];
	static float vol[(int)SoundKind::KindNum];

	static float fadeInSpeed[(int)SoundKind::KindNum];
	static float fadeOutSpeed[(int)SoundKind::KindNum];

public:
	SoundManager();
	~SoundManager();

	//初期化処理
	static void Init();

	//音関係処理
	static void Step();

	//終了処理
	static void Fin();

	//全データ読み込み
	//※return 
	// -> true  = ロード成功
	// -> false = 1つ以上のデータがロード失敗
	static bool LoadAllData();

	//現在の再生時間取得
	static int GetSoundTime(SoundKind soundID);

	//総再生時間取得
	static int GetSoundAllTime(SoundKind soundID);

	//再生状態取得
	static bool IsPlay(SoundKind soundID);

	//再生開始時間設定
	static void SetStartTime(SoundKind soundID, int startTime);

	//ボリューム設定
	// 0.0f <= Volime <= 1.0f
	static void SetVolume(SoundKind soundID, float Volume);

	//サウンド再生
	static int Play(SoundKind soundID, int playType = DX_PLAYTYPE_BACK, bool isStart = true);

	//サウンド停止
	static int Stop(SoundKind soundID);

	//全サウンド停止
	static void StopAll();

	static void SetFadeIn(SoundKind soundID, float spd);
	static void SetFadeOut(SoundKind soundID, float spd);
};