#pragma once
#include <functional>

class SceneManager;

enum class SCENEID
{
	//�I����ID
	SCENE_ID_END = -1,	//�G���h�V�[����ID

	//�^�C�g���V�[����ID
	SCENE_ID_TITLE = 100,	//�������V�[����ID

	//�v���C�V�[����ID
	SCENE_ID_PLAY = 200,	//�������V�[����ID

	//���U���g�V�[����ID
	SCENE_ID_RESULT = 300,		//�������V�[����ID
};

class SceneBase
{
protected:
	typedef void(SceneBase::* StateFunc)();

	StateFunc stateFunc;

	bool isLoadStart;
	bool FadeOutFlag;

	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Step() = 0;
	virtual void Draw() = 0;
	virtual void Fin() = 0;

public:
	SceneBase() { isLoadStart = false; FadeOutFlag = false; stateFunc = nullptr; }

	void ExecutionStateFunc() { (this->*stateFunc)(); }
};

class SceneManager
{
private:
	SCENEID CurrentSceneID;	//���݂̃V�[��ID

	SceneBase* scene;
public:
	static SCENEID NextSceneID;	//���̃V�[��ID

	SceneManager();
	~SceneManager();

	void SceneInit();

	bool SceneLoop();

	void SceneFin();
};
