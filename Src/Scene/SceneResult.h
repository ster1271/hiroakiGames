#pragma once
#include "Scene.h"

class SceneResult : public SceneBase
{
private:

	int m_ResultHndle;		//���U���g�摜�n���h��

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