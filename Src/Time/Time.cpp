#include "Dxlib.h"
#include "../Common.h"
#include "Time.h"
#include "../FrameRate/FrameRate.h"

bool Time::stop_Flag[(int)TimeKind::KIND_NUM];
float Time::stop_Time[(int)TimeKind::KIND_NUM];

bool Time::slow_Flag[(int)TimeKind::KIND_NUM];
int Time::slow_Frame[(int)TimeKind::KIND_NUM];
int Time::slow_CurrentFrame[(int)TimeKind::KIND_NUM];
float Time::slow_Time[(int)TimeKind::KIND_NUM];

void Time::Init()
{
	for (int i = 0; i < (int)TimeKind::KIND_NUM; i++)
	{
		stop_Flag[i] = false;
		stop_Time[i] = 0.0f;

		slow_Flag[i] = false;
		slow_Frame[i] = 0;
		slow_CurrentFrame[i] = 0;
		slow_Time[i] = 0.0f;
	}
}

void Time::Step()
{
	for (int i = 0; i < (int)TimeKind::KIND_NUM; i++)
	{
		if (stop_Flag[i])
		{
			stop_Time[i] -= FrameRate::GetDeltaTime();
			if (stop_Time[i] <= 0.0f)
			{
				stop_Time[i] = 0.0f;
				stop_Flag[i] = false;

				continue;
			}
		}
		else if (slow_Flag[i])
		{
			slow_CurrentFrame[i]++;
			if (slow_CurrentFrame[i] > slow_Frame[i])
			{
				slow_CurrentFrame[i] = 0;
			}

			if (slow_Time[i] > 0.0f)
			{
				slow_Time[i] -= FrameRate::GetDeltaTime();
				if (slow_Time[i] <= 0.0f)
				{
					slow_Time[i] = 0.0f;
				}
			}
			else
			{
				if (slow_CurrentFrame[i] >= slow_Frame[i])
				{
					slow_Frame[i]--;
					if (slow_Frame[i] <= 0)
					{
						slow_Flag[i] = false;
						slow_Frame[i] = 0;
						slow_CurrentFrame[i] = 0;
						slow_Time[i] = 0.0f;
					}
				}
			}
		}
	}
}

void Time::Stop(int target, float stopTime)
{
	stop_Flag[target] = true;
	stop_Time[target] = stopTime;
}
void Time::Slow(int target, float slowTime)
{
	slow_Flag[target] = true;
	slow_Frame[target] = 2;
	slow_CurrentFrame[target] = 0;
	slow_Time[target] = slowTime;
}

bool Time::StopJudge(int target)
{
	return stop_Flag[target];
}
bool Time::SlowJudge(int target)
{
	if (slow_Flag[target])
	{
		if (slow_CurrentFrame[target] >= slow_Frame[target])
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

void Time::StopReset(int target)
{
	if (target == -1)
	{
		for (int i = 0; i < (int)TimeKind::KIND_NUM; i++)
		{
			stop_Flag[i] = false;
			stop_Time[i] = 0.0f;
		}
	}
	else if (target >= 0 && target < (int)TimeKind::KIND_NUM)
	{
		stop_Flag[target] = false;
		stop_Time[target] = 0.0f;
	}
}
void Time::SlowReset(int target)
{
	if (target == -1)
	{
		for (int i = 0; i < (int)TimeKind::KIND_NUM; i++)
		{
			slow_Flag[i] = false;
			slow_Frame[i] = 0;
			slow_CurrentFrame[i] = 0;
			slow_Time[i] = 0.0f;
		}
	}
	else if (target >= 0 && target < (int)TimeKind::KIND_NUM)
	{
		slow_Flag[target] = false;
		slow_Frame[target] = 0;
		slow_CurrentFrame[target] = 0;
		slow_Time[target] = 0.0f;
	}
}

float Time::GetRoleDelta(int target)
{
	switch (target)
	{
	case -1:
		return FrameRate::GetDeltaTime();
		break;
	case (int)TimeKind::ALL:
		if (stop_Flag[target])
		{
			return 0.0f;
		}
		else if (slow_Flag[target])
		{
			return FrameRate::GetDeltaTime() / static_cast<float>(slow_Frame[target]);
		}
		else
		{
			return FrameRate::GetDeltaTime();
		}
		break;
	case (int)TimeKind::PLAYER1:
		if (stop_Flag[(int)TimeKind::ALL] || stop_Flag[target])
		{
			return 0.0f;
		}
		else if (slow_Flag[(int)TimeKind::ALL])
		{
			return FrameRate::GetDeltaTime() / static_cast<float>(slow_Frame[(int)TimeKind::ALL]);
		}
		else if (slow_Flag[target])
		{
			return FrameRate::GetDeltaTime() / static_cast<float>(slow_Frame[target]);
		}
		else
		{
			return FrameRate::GetDeltaTime();
		}
		break;
	default:
		return FrameRate::GetDeltaTime();
		break;
	}

	if (target < -1 || target >= (int)TimeKind::KIND_NUM)
		return FrameRate::GetDeltaTime();

	if(target == -1)
		return FrameRate::GetDeltaTime();

	if (target == (int)TimeKind::ALL)
	{
		if (stop_Flag[target])
		{
			return 0.0f;
		}
		else if (slow_Flag[target])
		{
			return FrameRate::GetDeltaTime() / static_cast<float>(slow_Frame[target]);
		}
		else
		{
			return FrameRate::GetDeltaTime();
		}
	}

	if (stop_Flag[target])
	{
		return 0.0f;
	}
	else if (slow_Flag[target])
	{
		if (target == -1)
		{
			return FrameRate::GetDeltaTime();
		}
		else if (target >= 0 && target < (int)TimeKind::KIND_NUM)
		{
			return FrameRate::GetDeltaTime() / static_cast<float>(slow_Frame[target]);
		}
	}
	else
	{
		return FrameRate::GetDeltaTime();
	}
}

Time::TimeKind Time::GetTimeKind_byCharaID(int ID)
{
	if (ID >= 0 && ID < PLAYER_NUM)
	{
		switch (ID)
		{
		case 0:
			return TimeKind::PLAYER1;
			break;
		default:
			return TimeKind::ALL;
			break;
		}
	}
	else
		return TimeKind::ALL;
}