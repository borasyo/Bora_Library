//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [TaskManager.cpp]
// author : 大洞祥太
// 
// Scene上の全てのオブジェクトを管理する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "TaskManager.h"
#include <iostream>
#include "../DirectX/Direct3D.h"
#include "DepthSort.h" 
#include "../Scene/SceneManager.h"

// 実体定義
TaskManager* TaskManager::m_pTaskManager = new TaskManager;

TaskManager::TaskManager(){
	nOldTaskSize = 0;
}

// 全てのゲームオブジェクトを削除
TaskManager::~TaskManager(){
	Clear();
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) delete *Ite;
	AllGameObject.erase(AllGameObject.begin(),AllGameObject.end());
}

// ゲームオブジェクト新規作成
GameObject* TaskManager::CreateObject(GameObject* Obj){
	AllGameObject.push_back(Obj);
	return Obj;
}

// ゲームオブジェクトを削除	
bool TaskManager::DestroyObject(GameObject* pObj, bool bParentErase){

	// そのオブジェクトは存在するかをチェック
	if( !pObj )
		return false; // 失敗!!

	// 探索の前に破壊可能かチェック
	if( !pObj->GetDestory() )
		return false; // 失敗!!

	// 子を削除
	std::list<GameObject*>* Child = pObj->GetChild(); // 子リストを取得
	for( auto ChildIte = Child->begin(); ChildIte != Child->end(); ChildIte++ ) {
		DestroyObject(*ChildIte,false); // 子リスト全てにDestroyを実行
		(*ChildIte)->SetLife(-999);
	}

	if( pObj->GetName() == "Shadow" ) {
		int i = 0;
	}

	// 親が居れば、親への登録を解除(bParentEraseがfalseの場合、重複するので解除しない)
	if( pObj->GetParent() && bParentErase ){
		std::list<GameObject*>* Parent = pObj->GetParent()->GetChild(); // 親の子リストを取得
		if( Parent ) {
			for( auto ParentIte = Parent->begin(); ParentIte != Parent->end(); ParentIte++ ){
				if( pObj == *ParentIte ){ // 親の子リストから自分を見つけ出す
					Parent->erase(ParentIte); // 削除
					break;
				}
			}
		}
	}

	// 自身を削除
	pObj->Clear();
	pObj->SetLife(-999);

	return true; // 成功!!
}

//	開始処理
bool TaskManager::Start(){
	
	//	優先的に初期化
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		if(!(*Ite)->GetActive())
			continue;

		//	Awake実行
		(*Ite)->Awake();	
	}

	// 通常の初期化
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		if(!(*Ite)->GetActive())
			continue;

		//	Start実行
		if(!(*Ite)->Start())
			return false;
 	}

	// 深度ソートかける
	AllGameObject.sort(CheckDepth);

	return true;
}

//	更新処理
void TaskManager::Update(){

	//	LifeCheck
	std::vector<GameObject*> Destroy;
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite ++)
		if( (*Ite)->GetLife() == 0 )
			Destroy.push_back(*Ite);
	for( auto Ite = Destroy.begin(); Ite != Destroy.end(); Ite++ )
		DestroyObject(*Ite);
	
	//	Nullになったオブジェクトをリストから消去
	NullObjectErase();
	
	//	Fast & Preparation
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		//	更新前準備
		(*Ite)->Preparation();

		//	更新するか
		if( !(*Ite)->GetUpdateFlg() ) 
			continue;

		//	優先して更新
		(*Ite)->FastUpdate();
	}

	//	Normal
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		
		//	更新するか
		if( !(*Ite)->GetUpdateFlg() ) 
			continue;
		
		//	更新
		(*Ite)->Update();
	}

	//	Late
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		
		//	更新するか
		if( !(*Ite)->GetUpdateFlg() ) 
			continue;

		//	遅れて更新
		(*Ite)->LateUpdate();
	}

	// object数が多くなるほど負荷がかかる
	// object数に変動があった場合はソート
//	if(nOldTaskSize != AllGameObject.size()) {	
//		AllGameObject.sort(CheckDepth);
//	}

	nOldTaskSize = AllGameObject.size();
}

// 描画処理
void TaskManager::Draw(){

	//	LifeCheck
	std::vector<GameObject*> Destroy;
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite ++)
		if( (*Ite)->GetLife() == 0 )
			Destroy.push_back(*Ite);
	for( auto Ite = Destroy.begin(); Ite != Destroy.end(); Ite++ )
		DestroyObject(*Ite);

	//	Nullになったオブジェクトをリストから消去
	NullObjectErase();
	
	//	Fast
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		//	描画するか
		if( !(*Ite)->GetActive() )
			continue;

		//	優先して描画
		(*Ite)->FastDraw();
	}

	//	Normal
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		//	描画するか
		if( !(*Ite)->GetActive() ) 
			continue;

		//	描画
		(*Ite)->Draw();
	}

	//	Late
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		//	描画するか
		if( !(*Ite)->GetActive() ) 
			continue;

		//	遅れて描画
		(*Ite)->LateDraw();
	}
}

// 削除処理
void TaskManager::Clear(){	
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ )
		(*Ite)->Clear();
}

// 死んだオブジェクトをリストから消去
void TaskManager::NullObjectErase() {
	
	auto Ite = AllGameObject.begin();
	while( Ite != AllGameObject.end() ) {
		
		if( (*Ite)->GetLife() != 0 ) {
			Ite++;
		}
		else if( (*Ite)->GetDestory() ) {
			GameObject* pObj = *Ite;
			Ite = AllGameObject.erase(Ite);
			delete pObj;
			pObj = nullptr;
		}
		else
			Ite++;
	}
}

// 全てのオブジェクトを取得
std::list<GameObject*>* TaskManager::FindAllObject(){
	return &AllGameObject;
}

// 全てのアクティブオブジェクトを取得
std::list<GameObject*> TaskManager::FindWithActive(bool bActive){
	std::list<GameObject*> GetObj;

	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		if( (*Ite)->GetActive() != bActive ) 
			continue;
		
		// Activeなので格納
		GetObj.push_back(*Ite);
	}

	return GetObj;
}

// 全てのオブジェクトの中から名前の一致するオブジェクトを全て返す
std::vector<GameObject*> TaskManager::FindWithNameAll(const std::string name, bool bActive){
	std::vector<GameObject*> GetObj;

	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {

		if((*Ite)->GetName() != name)
			continue;

		if((*Ite)->GetActive() != bActive)
			continue;

		GetObj.push_back(*Ite);
	}

	return GetObj;
}

// 全てのオブジェクトの中から名前の一致するオブジェクトを1つ返す(nameがuniqueではない場合使用しない)
GameObject* TaskManager::FindWithName(const std::string name, bool bActive){
	
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){

		if((*Ite)->GetName() != name)
			continue;

		if((*Ite)->GetActive() != bActive)
			continue;
		
		return *Ite;
	}
	
	return nullptr;
}

// 全てのオブジェクトの中からタグの一致するオブジェクトを全て返す
std::vector<GameObject*> TaskManager::FindWithTagAll(const std::string tag, bool bActive){
	std::vector<GameObject*> GetObj;

	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		
		if((*Ite)->GetTag() != tag)
			continue;

		if((*Ite)->GetActive() != bActive)
			continue;

		GetObj.push_back(*Ite);
	}

	return GetObj;
}

// 全てのオブジェクトの中からタグの一致するオブジェクトを1つ返す(tagがuniqueではない場合使用しない)
GameObject* TaskManager::FindWithTag(const std::string tag, bool bActive){
	
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {

		if((*Ite)->GetTag() != tag)
			continue;

		if((*Ite)->GetActive() != bActive)
			continue;

		return *Ite;
	}

	return nullptr;
}

// 全てのオブジェクトの中からレイヤーの一致するオブジェクトを全て返す
std::vector<GameObject*> TaskManager::FindWithLayerAll(const std::string layer, bool bActive){
	std::vector<GameObject*> GetObj;
	
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		if((*Ite)->GetLayer() != layer)
			continue;

		if((*Ite)->GetActive() != bActive)
			continue;

		GetObj.push_back(*Ite);
	}

	return GetObj;
}

// 全てのオブジェクトの中からレイヤーの一致するオブジェクトを1つ返す(layerがuniqueではない場合使用しない)
GameObject* TaskManager::FindWithLayer(const std::string layer, bool bActive){
	
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {

		if((*Ite)->GetLayer() != layer)
			continue;

		if((*Ite)->GetActive() != bActive)
			continue;

		return *Ite;
	}

	return nullptr;
}

// 全てのオブジェクトのActive変更
void TaskManager::SetAllActive(bool bActive) {
	
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		(*Ite)->SetActive(bActive);
	}
}

// 全てのオブジェクトのUpdateFlgを変更
void TaskManager::SetAllUpdateFlg(bool bUpdate) {
	
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		(*Ite)->SetUpdateFlg(bUpdate);
	}
}

// 深度ソート
void TaskManager::DepthSort() {
	AllGameObject.sort(CheckDepth);
}

// 現在のシーンの固定オブジェクトから探索する(特定の状況で処理を軽減できる)
GameObject* TaskManager::FindWithNameForScene(const std::string name){
	
	GameObject* pScene = SceneManager::Instance()->GetNowScene();
	for( auto Ite = pScene->GetChild()->begin(); Ite != pScene->GetChild()->end(); Ite++ ){

		if((*Ite)->GetName() != name)
			continue;
		
		return *Ite;
	}
	
	return nullptr;
}

GameObject* TaskManager::FindWithTagForScene(const std::string tag){
	
	GameObject* pScene = SceneManager::Instance()->GetNowScene();
	for( auto Ite = pScene->GetChild()->begin(); Ite != pScene->GetChild()->end(); Ite++ ){

		if((*Ite)->GetTag() != tag)
			continue;
		
		return *Ite;
	}
	
	return nullptr;
}

GameObject* TaskManager::FindWithLayerForScene(const std::string layer){
	
	GameObject* pScene = SceneManager::Instance()->GetNowScene();
	for( auto Ite = pScene->GetChild()->begin(); Ite != pScene->GetChild()->end(); Ite++ ){

		if((*Ite)->GetLayer() != layer)
			continue;
		
		return *Ite;
	}
	
	return nullptr;
}