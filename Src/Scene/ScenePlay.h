#pragma once
#include "DxLib.h"

#include "../Common.h"
#include "Scene.h"

class ScenePlay : public SceneBase
{
private:
	//�����o�[�ϐ��͂���


public:
	void Init();
	void Load();
	void Step();
	void Draw();
	void Fin();

	ScenePlay();
	~ScenePlay();
};