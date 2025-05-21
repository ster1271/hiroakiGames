#pragma once
#include "DxLib.h"

#include "../Common.h"
#include "Scene.h"
#include "../Card/CardManager.h"
#include "../Player/Player.h"
#include "../Enemy/EnemyManager.h"

class ScenePlay : public SceneBase
{
private:
	//�����o�[�ϐ��͂���

	CPlayer cPlayer;
	CEnemyManager cEnemyManager;
	CCardManager cCardManager;

public:
	void Init();
	void Load();
	void Step();
	void Draw();
	void Fin();

	ScenePlay();
	~ScenePlay();
};