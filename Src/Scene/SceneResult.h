#pragma once
#include "Scene.h"

constexpr char RESULT_IMAGE_PATH[128] = "Data/Image/èIÇÌÇË.png";

class SceneResult : public SceneBase
{
private:
	int resultImageHandle;

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