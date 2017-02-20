//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneManager.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SceneManager.h"
#include "../Task/ObjectFactory.h"

// ���̒�`
SceneManager* SceneManager::m_pSceneManager = nullptr;

// --- �R���X�g���N�^
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

	// �V�[���J�ڂ����Ȃ珉�����������s
	if(m_eNextScene != SCENE_MAX) {
		TaskManager::Instance()->Start();
		m_eNowScene = m_eNextScene;
		m_eNextScene = SCENE_MAX;
	}
}

// �E�B���h�E�����O�ɐ������Ă�������object�𐶐�
void SceneManager::SetObject() {

	// ��{�V�[������
	m_pTitle = CreateObject(new CSceneTitle);
	m_pStageSelect = CreateObject(new CSceneStageSelect);
	m_pGameMain = CreateObject(new CSceneGameMain);
	m_pResult = CreateObject(new CSceneResult);

	// �����܂łŐ��������I�u�W�F�N�g�͏I�����܂Ŕj�󂳂��Ȃ�
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		(*Ite)->BanDestroy();
		(*Ite)->SetActive(false);
	}
	
#ifdef DEBUG
	std::cout << "SetObject" << m_pAllObj->size() << std::endl;
#endif
}

// ---- �V�[���Ǘ��֐�

// �^�C�g���ŕK�v�ȃI�u�W�F�N�g���A�N�e�B�u��Ԃɂ���
void SceneManager::Title() {

	// ��U�S�ẴI�u�W�F�N�g��false��
	m_pCreator->SetAllActive(false);
	
	ReInit();
	m_pTitle->SetActive(true);
	m_pTitle->CreateSceneObject();
	
	// �K�v�I�u�W�F�N�g����true��
	
#ifdef DEBUG
	std::cout << "Title" << std::endl;
#endif
}

// �X�e�[�W�Z���N�g�ŕK�v�ȃI�u�W�F�N�g���A�N�e�B�u��Ԃɂ���
void SceneManager::StageSelect() {
	
	// ��U�S�ẴI�u�W�F�N�g��false��
	m_pCreator->SetAllActive(false);

	ReInit();
	m_pStageSelect->SetActive(true);
	m_pStageSelect->CreateSceneObject();

#ifdef DEBUG
	std::cout << "StageSelect" << std::endl;
#endif
}

// �Q�[�����C���ŕK�v�ȃI�u�W�F�N�g���A�N�e�B�u��Ԃɂ���
void SceneManager::GameMain() {

	// ��U�S�ẴI�u�W�F�N�g��false��
	m_pCreator->SetAllActive(false);
	
	ReInit();
	m_pGameMain->SetActive(true);
	m_pGameMain->CreateSceneObject();

#ifdef DEBUG
	std::cout << "GameMain" << std::endl;
#endif
}

// �Q�[���N���A�ŕK�v�ȃI�u�W�F�N�g���A�N�e�B�u��Ԃɂ���
void SceneManager::Result() {
	
	// ��U�S�ẴI�u�W�F�N�g��false��
	m_pCreator->SetAllActive(false);
	
	ReInit();
	m_pResult->SetActive(true);
	m_pResult->CreateSceneObject();
	
#ifdef DEBUG
	std::cout << "Result" << std::endl;
#endif
}

// ������xPlay
void SceneManager::ReInit() {
	
	// �j��\�I�u�W�F�N�g��S�j��
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		m_pCreator->DestroyObject( *Ite );
	}

	// �j�󂳂ꂽ�I�u�W�F�N�g�����X�g�������
	m_pCreator->NullObjectErase();
	
	std::vector<GameObject*> ParentList = m_pCreator->FindWithTagAll("Parent");
	for( auto Parent = ParentList.begin(); Parent != ParentList.end(); Parent++ ) {
		for( auto Child = (*Parent)->GetChild()->begin(); Child != (*Parent)->GetChild()->end(); Child++ ) {
			(*Child)->SetActive(false);
			(*Child)->SetCollisionFlg(false);
		}
	}

	// ��U�S�ẴI�u�W�F�N�g��true��
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		(*Ite)->SetActive(false);
	}
}

//	���݂̃V�[����Ԃ�
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