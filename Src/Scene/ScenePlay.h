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
	//ƒƒ“ƒo[•Ï”‚Í‚±‚±

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