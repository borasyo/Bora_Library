//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [TaskManager.cpp]
// author : �哴�ˑ�
// 
// Scene��̑S�ẴI�u�W�F�N�g���Ǘ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "TaskManager.h"
#include <iostream>
#include "../DirectX/Direct3D.h"
#include "DepthSort.h" 
#include "../Scene/SceneManager.h"

// ���̒�`
TaskManager* TaskManager::m_pTaskManager = new TaskManager;

TaskManager::TaskManager(){
	nOldTaskSize = 0;
}

// �S�ẴQ�[���I�u�W�F�N�g���폜
TaskManager::~TaskManager(){
	Clear();
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) delete *Ite;
	AllGameObject.erase(AllGameObject.begin(),AllGameObject.end());
}

// �Q�[���I�u�W�F�N�g�V�K�쐬
GameObject* TaskManager::CreateObject(GameObject* Obj){
	AllGameObject.push_back(Obj);
	return Obj;
}

// �Q�[���I�u�W�F�N�g���폜	
bool TaskManager::DestroyObject(GameObject* pObj, bool bParentErase){

	// ���̃I�u�W�F�N�g�͑��݂��邩���`�F�b�N
	if( !pObj )
		return false; // ���s!!

	// �T���̑O�ɔj��\���`�F�b�N
	if( !pObj->GetDestory() )
		return false; // ���s!!

	// �q���폜
	std::list<GameObject*>* Child = pObj->GetChild(); // �q���X�g���擾
	for( auto ChildIte = Child->begin(); ChildIte != Child->end(); ChildIte++ ) {
		DestroyObject(*ChildIte,false); // �q���X�g�S�Ă�Destroy�����s
		(*ChildIte)->SetLife(-999);
	}

	if( pObj->GetName() == "Shadow" ) {
		int i = 0;
	}

	// �e������΁A�e�ւ̓o�^������(bParentErase��false�̏ꍇ�A�d������̂ŉ������Ȃ�)
	if( pObj->GetParent() && bParentErase ){
		std::list<GameObject*>* Parent = pObj->GetParent()->GetChild(); // �e�̎q���X�g���擾
		if( Parent ) {
			for( auto ParentIte = Parent->begin(); ParentIte != Parent->end(); ParentIte++ ){
				if( pObj == *ParentIte ){ // �e�̎q���X�g���玩���������o��
					Parent->erase(ParentIte); // �폜
					break;
				}
			}
		}
	}

	// ���g���폜
	pObj->Clear();
	pObj->SetLife(-999);

	return true; // ����!!
}

//	�J�n����
bool TaskManager::Start(){
	
	//	�D��I�ɏ�����
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		if(!(*Ite)->GetActive())
			continue;

		//	Awake���s
		(*Ite)->Awake();	
	}

	// �ʏ�̏�����
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		if(!(*Ite)->GetActive())
			continue;

		//	Start���s
		if(!(*Ite)->Start())
			return false;
 	}

	// �[�x�\�[�g������
	AllGameObject.sort(CheckDepth);

	return true;
}

//	�X�V����
void TaskManager::Update(){

	//	LifeCheck
	std::vector<GameObject*> Destroy;
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite ++)
		if( (*Ite)->GetLife() == 0 )
			Destroy.push_back(*Ite);
	for( auto Ite = Destroy.begin(); Ite != Destroy.end(); Ite++ )
		DestroyObject(*Ite);
	
	//	Null�ɂȂ����I�u�W�F�N�g�����X�g�������
	NullObjectErase();
	
	//	Fast & Preparation
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		//	�X�V�O����
		(*Ite)->Preparation();

		//	�X�V���邩
		if( !(*Ite)->GetUpdateFlg() ) 
			continue;

		//	�D�悵�čX�V
		(*Ite)->FastUpdate();
	}

	//	Normal
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		
		//	�X�V���邩
		if( !(*Ite)->GetUpdateFlg() ) 
			continue;
		
		//	�X�V
		(*Ite)->Update();
	}

	//	Late
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		
		//	�X�V���邩
		if( !(*Ite)->GetUpdateFlg() ) 
			continue;

		//	�x��čX�V
		(*Ite)->LateUpdate();
	}

	// object���������Ȃ�قǕ��ׂ�������
	// object���ɕϓ����������ꍇ�̓\�[�g
//	if(nOldTaskSize != AllGameObject.size()) {	
//		AllGameObject.sort(CheckDepth);
//	}

	nOldTaskSize = AllGameObject.size();
}

// �`�揈��
void TaskManager::Draw(){

	//	LifeCheck
	std::vector<GameObject*> Destroy;
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite ++)
		if( (*Ite)->GetLife() == 0 )
			Destroy.push_back(*Ite);
	for( auto Ite = Destroy.begin(); Ite != Destroy.end(); Ite++ )
		DestroyObject(*Ite);

	//	Null�ɂȂ����I�u�W�F�N�g�����X�g�������
	NullObjectErase();
	
	//	Fast
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		//	�`�悷�邩
		if( !(*Ite)->GetActive() )
			continue;

		//	�D�悵�ĕ`��
		(*Ite)->FastDraw();
	}

	//	Normal
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		//	�`�悷�邩
		if( !(*Ite)->GetActive() ) 
			continue;

		//	�`��
		(*Ite)->Draw();
	}

	//	Late
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		//	�`�悷�邩
		if( !(*Ite)->GetActive() ) 
			continue;

		//	�x��ĕ`��
		(*Ite)->LateDraw();
	}
}

// �폜����
void TaskManager::Clear(){	
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ )
		(*Ite)->Clear();
}

// ���񂾃I�u�W�F�N�g�����X�g�������
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

// �S�ẴI�u�W�F�N�g���擾
std::list<GameObject*>* TaskManager::FindAllObject(){
	return &AllGameObject;
}

// �S�ẴA�N�e�B�u�I�u�W�F�N�g���擾
std::list<GameObject*> TaskManager::FindWithActive(bool bActive){
	std::list<GameObject*> GetObj;

	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		
		if( (*Ite)->GetActive() != bActive ) 
			continue;
		
		// Active�Ȃ̂Ŋi�[
		GetObj.push_back(*Ite);
	}

	return GetObj;
}

// �S�ẴI�u�W�F�N�g�̒����疼�O�̈�v����I�u�W�F�N�g��S�ĕԂ�
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

// �S�ẴI�u�W�F�N�g�̒����疼�O�̈�v����I�u�W�F�N�g��1�Ԃ�(name��unique�ł͂Ȃ��ꍇ�g�p���Ȃ�)
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

// �S�ẴI�u�W�F�N�g�̒�����^�O�̈�v����I�u�W�F�N�g��S�ĕԂ�
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

// �S�ẴI�u�W�F�N�g�̒�����^�O�̈�v����I�u�W�F�N�g��1�Ԃ�(tag��unique�ł͂Ȃ��ꍇ�g�p���Ȃ�)
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

// �S�ẴI�u�W�F�N�g�̒����烌�C���[�̈�v����I�u�W�F�N�g��S�ĕԂ�
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

// �S�ẴI�u�W�F�N�g�̒����烌�C���[�̈�v����I�u�W�F�N�g��1�Ԃ�(layer��unique�ł͂Ȃ��ꍇ�g�p���Ȃ�)
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

// �S�ẴI�u�W�F�N�g��Active�ύX
void TaskManager::SetAllActive(bool bActive) {
	
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		(*Ite)->SetActive(bActive);
	}
}

// �S�ẴI�u�W�F�N�g��UpdateFlg��ύX
void TaskManager::SetAllUpdateFlg(bool bUpdate) {
	
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		(*Ite)->SetUpdateFlg(bUpdate);
	}
}

// �[�x�\�[�g
void TaskManager::DepthSort() {
	AllGameObject.sort(CheckDepth);
}

// ���݂̃V�[���̌Œ�I�u�W�F�N�g����T������(����̏󋵂ŏ������y���ł���)
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