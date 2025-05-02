#pragma once
#include <functional>

class SceneManager;

enum class SCENEID
{
	//終了のID
	SCENE_ID_END = -1,	//エンドシーンのID

	//タイトルシーンのID
	SCENE_ID_TITLE = 100,	//初期化シーンのID

	//プレイシーンのID
	SCENE_ID_PLAY = 200,	//初期化シーンのID

	//リザルトシーンのID
	SCENE_ID_RESULT = 300,		//初期化シーンのID
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
	SCENEID CurrentSceneID;	//現在のシーンID

	SceneBase* scene;
public:
	static SCENEID NextSceneID;	//次のシーンID

	SceneManager();
	~SceneManager();

	void SceneInit();

	bool SceneLoop();

	void SceneFin();
};
