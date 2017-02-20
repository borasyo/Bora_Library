//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [TaskManager.h]
// author : 大洞祥太
// 
// Scene上の全てのオブジェクトを管理する。
//
// ex)std::vector<GameObject*> Vec = ....FindWithNameAll(...); 
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TaskManager_H_____
#define _____TaskManager_H_____

#include <iostream>
#include "GameObject.h"
#include <list>
#include <string>
#include <vector>

class TaskManager {

private:
	static TaskManager* m_pTaskManager;
	std::list<GameObject*> AllGameObject; // シーン上の全てのゲームオブジェクトを保持
	int nOldTaskSize;
	
private:
	TaskManager();

public:
	~TaskManager();

	// インスタンス取得
	static TaskManager* Instance() { return m_pTaskManager; }

	// ゲームオブジェクト新規作成
	GameObject* CreateObject(GameObject* Obj);

	// ゲームオブジェクトを削除	
	bool DestroyObject(GameObject* pObj, bool bParentErase = true);
	
	// 開始処理
	bool Start();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// 削除処理
	void Clear();

	// nullのポインタをリストから消去
	void NullObjectErase();
	
	// 全てのオブジェクトを返す
	std::list<GameObject*>* FindAllObject();
	
	// 全てのオブジェクトの中からアクティブなオブジェクトを全て返す
	std::list<GameObject*> FindWithActive(bool bActive = true);

	// 全てのオブジェクトの中から名前の一致するオブジェクトを全て返す
	std::vector<GameObject*> FindWithNameAll(const std::string name, bool bActive = true);

	// 全てのオブジェクトの中から名前の一致するオブジェクトを1つ返す(nameがuniqueではない場合使用しない)
	GameObject* FindWithName(const std::string name, bool bActive = true);

	// 全てのオブジェクトの中からタグの一致するオブジェクトを全て返す
	std::vector<GameObject*> FindWithTagAll(const std::string tag, bool bActive = true);

	// 全てのオブジェクトの中からタグの一致するオブジェクトを1つ返す(tagがuniqueではない場合使用しない)
	GameObject* FindWithTag(const std::string tag, bool bActive = true);
	
	// 全てのオブジェクトの中からレイヤーの一致するオブジェクトを全て返す
	std::vector<GameObject*> FindWithLayerAll(const std::string layer, bool bActive = true);

	// 全てのオブジェクトの中からレイヤーの一致するオブジェクトを1つ返す(layerがuniqueではない場合使用しない)
	GameObject* FindWithLayer(const std::string layer, bool bActive = true);

	// 全てのオブジェクトのActive変更
	void SetAllActive(bool bActive);

	// 全てのオブジェクトのUpdateFlgを変更
	void SetAllUpdateFlg(bool bUpdate);

	// 深度ソートを実施
	void DepthSort();

	// 現在のシーンの固定オブジェクトから探索する(特定の状況で処理を軽減できる)
	GameObject* FindWithNameForScene(const std::string name);
	GameObject* FindWithTagForScene(const std::string tag);
	GameObject* FindWithLayerForScene(const std::string layer);
};

#endif