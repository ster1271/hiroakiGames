#pragma once

class Time
{
public:
	//��~�������̎�ޕ���
	enum class TimeKind
	{
		ALL,	//�ŏ��
		PLAYER1,	//�v���C���[1�̂�

		KIND_NUM
	};

private:
	//���Ԓ�~�t���O
	// 0:(�ŏ��)
	// 1:(�v���C���[�̂�)
	// 2:(�G�l�~�[�̂�)
	static bool stop_Flag[(int)TimeKind::KIND_NUM];
	static float stop_Time[(int)TimeKind::KIND_NUM];

	//�X���E�t���O
	// 0:(�ŏ��)
	// 1:(�v���C���[�̂�)
	// 2:(�G�l�~�[�̂�)
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

	// -1 �őS�ă��Z�b�g
	static void StopReset(int target);
	static void SlowReset(int target);

	// -1 �Œʏ��DeltaTime
	static float GetRoleDelta(int target);

	static TimeKind GetTimeKind_byCharaID(int ID);
};