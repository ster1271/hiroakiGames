#pragma once
#include "DxLib.h"
#include "Scene.h"

//ƒV[ƒ“î•ñ
class SceneTitle : public SceneBase
{
private:
	bool endFlag;

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