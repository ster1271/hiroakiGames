#pragma once
#include "DxLib.h"
#include "Scene.h"

//シーン情報
class SceneTitle : public SceneBase
{
private:
	bool endFlag;
	int m_TitleHndle;			//タイトル画像の変数
	int m_BackHndl;				//タイトルの背景画像の変数
	int m_Time;					//描画のタイミング
	int m_Count;				//カウント

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