#pragma once
#include "Scene.h"

class SceneResult : public SceneBase
{
private:

protected:
	void Init();
	void Load();
	void Step();
	void Draw();
	void Fin();

public:
	SceneResult();
	~SceneResult();
};