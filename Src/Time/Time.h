#pragma once

class Time
{
public:
	//停止処理等の種類分け
	enum class TimeKind
	{
		ALL,	//最上位
		PLAYER1,	//プレイヤー1のみ

		KIND_NUM
	};

private:
	//時間停止フラグ
	// 0:(最上位)
	// 1:(プレイヤーのみ)
	// 2:(エネミーのみ)
	static bool stop_Flag[(int)TimeKind::KIND_NUM];
	static float stop_Time[(int)TimeKind::KIND_NUM];

	//スロウフラグ
	// 0:(最上位)
	// 1:(プレイヤーのみ)
	// 2:(エネミーのみ)
	static bool slow_Flag[(int)TimeKind::KIND_NUM];
	static int slow_Frame[(int)TimeKind::KIND_NUM];
	static int slow_CurrentFrame[(int)TimeKind::KIND_NUM];
	static float slow_Time[(int)TimeKind::KIND_NUM];

public:
	static void Init();
	static void Step();

	static void Stop(int target, float stopTime);
	static void Slow(int target, float slowTime);

	static bool StopJudge(int target);
	static bool SlowJudge(int target);

	// -1 で全てリセット
	static void StopReset(int target);
	static void SlowReset(int target);

	// -1 で通常のDeltaTime
	static float GetRoleDelta(int target);

	static TimeKind GetTimeKind_byCharaID(int ID);
};