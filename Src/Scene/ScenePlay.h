#pragma once
#include "DxLib.h"

#include "../Common.h"
#include "Scene.h"

class ScenePlay : public SceneBase
{
private:
	//ƒƒ“ƒo[•Ï”‚Í‚±‚±


public:
	void Init();
	void Load();
	void Step();
	void Draw();
	void Fin();

	ScenePlay();
	~ScenePlay();
};