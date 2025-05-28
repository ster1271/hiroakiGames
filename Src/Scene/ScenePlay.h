#pragma once
#include "DxLib.h"

#include "../Common.h"
#include "Scene.h"
#include "../Stage/Stage.h"


class ScenePlay : public SceneBase
{
private:
	//ƒƒ“ƒo[•Ï”‚Í‚±‚±

	
	CStage cStage;

public:
	void Init();
	void Load();
	void Step();
	void Draw();
	void Fin();

	ScenePlay();
	~ScenePlay();
};