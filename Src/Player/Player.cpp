#include "Player.h"

const char STATE_HNDL_PATH[] = { "Data/Player/PlayerState.png" };

void CPlayer::Init()
{
}

void CPlayer::Load()
{
	m_StateHndl = LoadGraph(STATE_HNDL_PATH);
}

void CPlayer::Step()
{

}

void CPlayer::Draw()
{
	DrawRotaGraph(1100, 600, 0.8f, 0.0f, m_StateHndl, false);			//�X�e�[�^�X�摜

	DrawFormatString(1100, 550, GetColor(0, 0, 0), "%d", m_PlayerHP);	//HP
	DrawFormatString(1100, 637, GetColor(0, 0, 0), "%d", m_PlayerGP);	//�V�[���h
}

void CPlayer::Exit()
{
	m_StateHndl = -1;
}