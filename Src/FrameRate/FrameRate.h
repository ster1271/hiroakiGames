#pragma once

//�ݒ�t���[�����[�g
#define FRAME_RATE 60

//1�t���[���̎��ԁi�~���b�j
#define FRAME_TIME (1000 / FRAME_RATE)

class FrameRate
{
private:
	static float deltaTime;			//�o�ߎ���
	static ULONGLONG currentTime;	//�O��̃t���[�����s���̎���
	static ULONGLONG lastFrateTime;	//�O��̃t���[�����s���̎���

	static int count;			//�t���[���J�E���g�p
	static ULONGLONG calcFpsTime;		//FPS���v�Z��������
	static float fps;				//�v������FPS�i�\���p�j

public:
	static float GetDeltaTime() { return deltaTime; }

	static void Init();

	static bool Admin();	//FPS�Ǘ��֐�

	static void CalcFPS();			//FPS�v�Z

	static void DrawFPS();			//FPS�\���i�f�o�b�N�p�j
};

