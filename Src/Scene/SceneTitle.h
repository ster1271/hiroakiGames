#pragma once
#include "DxLib.h"
#include "Scene.h"

//�V�[�����
class SceneTitle : public SceneBase
{
private:
	bool endFlag;
	int m_TitleHndle;			//�^�C�g���摜�̕ϐ�
	int m_BackHndl;				//�^�C�g���̔w�i�摜�̕ϐ�
	int m_Time;					//�`��̃^�C�~���O
	int m_Count;				//�J�E���g

protected:
	void Init();
	void Load();
	void Step();
	void Draw();
	void Fin();

public:
	SceneTitle();
	~SceneTitle();
};