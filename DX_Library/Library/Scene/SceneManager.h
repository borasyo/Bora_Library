//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneManager.h]
// author : 大洞祥太
//
// シーンで必要なオブジェクトをアクティブに、
// その他を非アクティブにすることでシーンを管理。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SCENE_H_____
#define _____SCENE_H_____

#include <iostream>
#include "../Task/GameObject.h"
#include "../Task/TaskManager.h"

// ---- 基本シーン
#include "../Scene/SceneTitle.h"
#include "../Scene/SceneStageSelect.h"
#include "../Scene/SceneGameMain.h"
#include "../Scene/SceneResult.h"

// ---- 列挙
enum eScene {

	SCENE_TITLE = 0,
	SCENE_STAGESELECT,
	SCENE_GAMEMAIN,
	SCENE_RESULT,

	SCENE_MAX,
};

class SceneManager {

private:
	static SceneManager* m_pSceneManager;

	eScene m_eNowScene;
	eScene m_eNextScene;

	TaskManager* m_pCreator;
	std::list<GameObject*>* m_pAllObj;
	
	CSceneTitle* m_pTitle;
	CSceneStageSelect* m_pStageSelect;
	CSceneGameMain* m_pGameMain;
	CSceneResult* m_pResult;
	
private:
	SceneManager();
	
	// ---- シーン管理関数
	void Title();		// タイトル
	void StageSelect();	// ステージセレクト
	void GameMain();	// ゲームメイン
	void Result();		// リザルト
	void ReInit();		// 不必要になったオブジェクトを全削除

public:
	~SceneManager();
	
	static SceneManager* Create() { 	
		if( !m_pSceneManager )
			m_pSceneManager = new SceneManager;
		return m_pSceneManager;
	}
	static SceneManager* Instance() { return m_pSceneManager; }

	// シーン変更要求が来ていないかをチェック
	void Update();

	// ここでobjectを生成
	void SetObject();

	// シーン変更を予約
	void SetScene(eScene Scene) { m_eNextScene = Scene; }

	// 現在のシーンを返す
	GameObject* GetNowScene();
};

#endif