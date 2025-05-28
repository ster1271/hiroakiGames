#include "Player.h"

const char STATE_HNDL_PATH[] = { "Data/Player/PlayerState.png" };

void CPlayer::Init()
{
}

void CPlayer::Load()
{
	m_StateHndl = LoadGraph(STATE_HNDL_PATH);
	m_FontHandle = CreateFontToHandle("MS ゴシック", 24, -1);
	m_PlayerHP = 100;
	m_PlayerGP = 100;
}

void CPlayer::Step()
{

}

void CPlayer::Draw()
{
	DrawRotaGraph(1100, 600, 0.8f, 0.0f, m_StateHndl, false);			//ステータス画像

	DrawStringToHandle(100, 100, "こんにちは、DXライブラリ！", GetColor(255, 255, 255), m_FontHandle);

	DrawFormatString(1100, 550, GetColor(0, 0, 0), "%d", m_PlayerHP);	//HP
	DrawFormatString(1100, 637, GetColor(0, 0, 0), "%d", m_PlayerGP);	//シールド
}

void CPlayer::Exit()
{
	m_StateHndl = -1;
}