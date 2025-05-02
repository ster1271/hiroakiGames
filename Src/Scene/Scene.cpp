#include "DxLib.h"
#include "Scene.h"
#include "SceneTitle.h"
#include "ScenePlay.h"
#include "SceneResult.h"
#include "../Loading/Loading.h"

SCENEID SceneManager::NextSceneID;

SceneManager::SceneManager()
{
	CurrentSceneID = SCENEID::SCENE_ID_TITLE;
	NextSceneID = SCENEID::SCENE_ID_TITLE;

	scene = nullptr;
}

SceneManager::~SceneManager()
{
	InitGraph();
	InitSoundMem();
}

void SceneManager::SceneInit()
{
	if (scene == nullptr)
	{
		CurrentSceneID = SCENEID::SCENE_ID_TITLE;
		NextSceneID = SCENEID::SCENE_ID_TITLE;
		scene = new SceneTitle;
	}
}

bool SceneManager::SceneLoop()
{
	if (CurrentSceneID != NextSceneID)
	{
		if (scene != nullptr)
		{
			delete scene;
			scene = nullptr;
		}
		switch (NextSceneID)
		{
		case SCENEID::SCENE_ID_TITLE:
			scene = new SceneTitle;
			break;
		case SCENEID::SCENE_ID_PLAY:
			scene = new ScenePlay;
			break;
		case SCENEID::SCENE_ID_RESULT:
			scene = new SceneResult;
			break;
		default:
			break;
		}
		CurrentSceneID = NextSceneID;
	}

	if (CurrentSceneID == SCENEID::SCENE_ID_END)
	{
		return true;
	}

	if (scene != nullptr)
		scene->ExecutionStateFunc();

	Loading::Step();
	Loading::Draw();
	return false;
}

void SceneManager::SceneFin()
{
	InitGraph();
	InitSoundMem();

	if (scene != nullptr)
		delete scene;
}
