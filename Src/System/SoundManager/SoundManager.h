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
	"Data/Music/BGM/���������R�~�J��.mp3",
	"Data/Music/BGM/The-Charlatan.ogg",
	"Data/Music/BGM/���炾����j��.mp3",

	"Data/Music/SE/����{�^��������22.mp3",
	"Data/Music/SE/����ł�1_�Z.wav",
	"Data/Music/SE/�{�����1_�Z.wav"
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

	//����������
	static void Init();

	//���֌W����
	static void Step();

	//�I������
	static void Fin();

	//�S�f�[�^�ǂݍ���
	//��return 
	// -> true  = ���[�h����
	// -> false = 1�ȏ�̃f�[�^�����[�h���s
	static bool LoadAllData();

	//���݂̍Đ����Ԏ擾
	static int GetSoundTime(SoundKind soundID);

	//���Đ����Ԏ擾
	static int GetSoundAllTime(SoundKind soundID);

	//�Đ���Ԏ擾
	static bool IsPlay(SoundKind soundID);

	//�Đ��J�n���Ԑݒ�
	static void SetStartTime(SoundKind soundID, int startTime);

	//�{�����[���ݒ�
	// 0.0f <= Volime <= 1.0f
	static void SetVolume(SoundKind soundID, float Volume);

	//�T�E���h�Đ�
	static int Play(SoundKind soundID, int playType = DX_PLAYTYPE_BACK, bool isStart = true);

	//�T�E���h��~
	static int Stop(SoundKind soundID);

	//�S�T�E���h��~
	static void StopAll();

	static void SetFadeIn(SoundKind soundID, float spd);
	static void SetFadeOut(SoundKind soundID, float spd);
};