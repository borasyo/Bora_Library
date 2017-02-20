//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneManager.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SceneManager.h"
#include "../Task/ObjectFactory.h"

// 実体定義
SceneManager* SceneManager::m_pSceneManager = nullptr;

// --- コンストラクタ
SceneManager::SceneManager() {
	m_eNowScene = SCENE_TITLE;
	m_eNextScene = SCENE_MAX;
	m_pCreator = TaskManager::Instance();
	m_pAllObj = m_pCreator->FindAllObject();
}

SceneManager::~SceneManager() {
	
}

void SceneManager::Update() {

	switch(m_eNextScene) {

	case SCENE_TITLE:
		Title();
		break;

	case SCENE_STAGESELECT:
		StageSelect();
		break;

	case SCENE_GAMEMAIN:
		GameMain();
		break;

	case SCENE_RESULT:
		Result();
		break;

	default:
		break;
	}

	// シーン遷移したなら初期化処理実行
	if(m_eNextScene != SCENE_MAX) {
		TaskManager::Instance()->Start();
		m_eNowScene = m_eNextScene;
		m_eNextScene = SCENE_MAX;
	}
}

// ウィンドウ生成前に生成しておきたいobjectを生成
void SceneManager::SetObject() {

	// 基本シーン生成
	m_pTitle = CreateObject(new CSceneTitle);
	m_pStageSelect = CreateObject(new CSceneStageSelect);
	m_pGameMain = CreateObject(new CSceneGameMain);
	m_pResult = CreateObject(new CSceneResult);

	// ここまでで生成したオブジェクトは終了時まで破壊させない
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		(*Ite)->BanDestroy();
		(*Ite)->SetActive(false);
	}
	
#ifdef DEBUG
	std::cout << "SetObject" << m_pAllObj->size() << std::endl;
#endif
}

// ---- シーン管理関数

// タイトルで必要なオブジェクトをアクティブ状態にする
void SceneManager::Title() {

	// 一旦全てのオブジェクトをfalseに
	m_pCreator->SetAllActive(false);
	
	ReInit();
	m_pTitle->SetActive(true);
	m_pTitle->CreateSceneObject();
	
	// 必要オブジェクトだけtrueに
	
#ifdef DEBUG
	std::cout << "Title" << std::endl;
#endif
}

// ステージセレクトで必要なオブジェクトをアクティブ状態にする
void SceneManager::StageSelect() {
	
	// 一旦全てのオブジェクトをfalseに
	m_pCreator->SetAllActive(false);

	ReInit();
	m_pStageSelect->SetActive(true);
	m_pStageSelect->CreateSceneObject();

#ifdef DEBUG
	std::cout << "StageSelect" << std::endl;
#endif
}

// ゲームメインで必要なオブジェクトをアクティブ状態にする
void SceneManager::GameMain() {

	// 一旦全てのオブジェクトをfalseに
	m_pCreator->SetAllActive(false);
	
	ReInit();
	m_pGameMain->SetActive(true);
	m_pGameMain->CreateSceneObject();

#ifdef DEBUG
	std::cout << "GameMain" << std::endl;
#endif
}

// ゲームクリアで必要なオブジェクトをアクティブ状態にする
void SceneManager::Result() {
	
	// 一旦全てのオブジェクトをfalseに
	m_pCreator->SetAllActive(false);
	
	ReInit();
	m_pResult->SetActive(true);
	m_pResult->CreateSceneObject();
	
#ifdef DEBUG
	std::cout << "Result" << std::endl;
#endif
}

// もう一度Play
void SceneManager::ReInit() {
	
	// 破壊可能オブジェクトを全破壊
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		m_pCreator->DestroyObject( *Ite );
	}

	// 破壊されたオブジェクトをリストから消去
	m_pCreator->NullObjectErase();
	
	std::vector<GameObject*> ParentList = m_pCreator->FindWithTagAll("Parent");
	for( auto Parent = ParentList.begin(); Parent != ParentList.end(); Parent++ ) {
		for( auto Child = (*Parent)->GetChild()->begin(); Child != (*Parent)->GetChild()->end(); Child++ ) {
			(*Child)->SetActive(false);
			(*Child)->SetCollisionFlg(false);
		}
	}

	// 一旦全てのオブジェクトをtrueに
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		(*Ite)->SetActive(false);
	}
}

//	現在のシーンを返す
GameObject* SceneManager::GetNowScene() {
	switch(m_eNowScene) {
		
	case SCENE_TITLE:
		return m_pTitle;

	case SCENE_STAGESELECT:
		return m_pStageSelect;

	case SCENE_GAMEMAIN:
		return m_pGameMain;

	case SCENE_RESULT:
		return m_pResult;

	default:
		break;
	}

	return nullptr;
}