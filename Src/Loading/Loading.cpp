#include <math.h>
#include "DxLib.h"
#include "../Common.h"
#include "Loading.h"

Loading::State Loading::currentState;
int Loading::DrawAlpha;
int Loading::LoadNum;

float Loading::Load_Angle;

void Loading::Init()
{
	currentState = State::Loading_Wait;
	DrawAlpha = 255;
	LoadNum = 0;

	Load_Angle = 0.0f;
}

void Loading::Load()
{

}

void Loading::Step()
{
	switch (currentState)
	{
	case Loading::State::Loading_Wait:
		break;
	case Loading::State::Loading_Start:
		currentState = State::Loading_Now;
		break;
	case Loading::State::Loading_Now:
		Load_Angle += 0.15f;
		if (Load_Angle > DX_PI_F)
		{
			Load_Angle -= DX_TWO_PI_F;
		}
		if (GetASyncLoadNum() == 0)
		{
			currentState = State::Loading_Fin;
		}
		break;
	case Loading::State::Loading_Fin:
		break;
	case Loading::State::FadeIn:
		DrawAlpha += FADE_SPEED;
		if (DrawAlpha >= 255)
		{
			DrawAlpha = 255;
			currentState = State::Loading_Wait;
		}
		break;
	case Loading::State::FadeOut:
		DrawAlpha -= FADE_SPEED;
		if (DrawAlpha <= 0)
		{
			DrawAlpha = 0;
			ResetLoadNum();
			currentState = State::NO_TASK;
		}
		break;
	default:
		break;
	}
}

void Loading::Draw()
{
	if (currentState != State::NO_TASK)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, DrawAlpha);
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(100, 100, 100), true);
		switch (currentState)
		{
		case Loading::State::Loading_Wait:
			DrawFormatString(0, 20, GetColor(255, 0, 0), "“Ç‚Ýž‚Ý‘Ò‚¿");
			break;
		case Loading::State::Loading_Start:
			DrawFormatString(0, 20, GetColor(255, 0, 0), "“Ç‚Ýž‚Ý—ÊF0“");
			break;
		case Loading::State::Loading_Now:
			DrawFormatString(0, 20, GetColor(255, 0, 0), "“Ç‚Ýž‚Ý—ÊF%.0f“", 100.0f - (float)GetASyncLoadNum() / (float)LoadNum * 100.0f);
			for (int i = 0; i < LOAD_CIRCLE_NUM; i++)
			{
				if (LOAD_CIRCLE_NUM > 0 && LOAD_CIRCLE_NUM <= 255)
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / LOAD_CIRCLE_NUM * (LOAD_CIRCLE_NUM - i));

					DrawCircleAA(SCREEN_SIZE_X - 100.0f - 20.0f * cosf(Load_Angle - 0.6f * i), SCREEN_SIZE_Y - 100.0f - 20.0f * sinf(Load_Angle - 0.6f * i), 1.0f + 0.5f * (float)(LOAD_CIRCLE_NUM - i), 10, GetColor(0, 255, 255));

					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
			}
			break;
		case Loading::State::Loading_Fin:
			DrawFormatString(0, 20, GetColor(255, 0, 0), "“Ç‚Ýž‚ÝŠ®—¹");
			break;
		case Loading::State::FadeIn:
			break;
		case Loading::State::FadeOut:
			break;
		default:
			break;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Loading::Fin()
{

}

void Loading::FadeIn()
{
	currentState = State::FadeIn;
}

void Loading::FadeOut()
{
	currentState = State::FadeOut;
}

void Loading::LoadStart()
{
	if (currentState == State::Loading_Wait)
		currentState = State::Loading_Start;
}

bool Loading::IsLoadWait()
{
	if (currentState == State::Loading_Wait)
		return true;
	else
		return false;
}

bool Loading::IsLoadFin()
{
	if (currentState == State::Loading_Fin)
		return true;
	else
		return false;
}