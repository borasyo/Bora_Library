//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneGameMain.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SceneGameMain.h"
#include "../Task/ObjectFactory.h"

#include "../../Object/GameMain/Field/Field.h"
#include "../../Object/GameMain/Field/Sky.h"
#include "../../Object/GameMain/Main/MainCamera.h"
#include "../../Object/GameMain/Main/MainLight.h"
#include "../../Object/GameMain/Field/FieldMassManager.h"
#include "../../Object/GameMain/Charactor/Manager/CharactorManager.h"
#include "../../Object/GameMain/Player/SelectMass.h"

//������������ SetParent��Y�ꂸ��!!! ������������
//������������ SetParent��Y�ꂸ��!!! ������������
//������������ SetParent��Y�ꂸ��!!! ������������

CSceneGameMain::CSceneGameMain() {
	m_Transform.Name = "SceneGameMain";
}

CSceneGameMain::~CSceneGameMain() {
	
}

bool CSceneGameMain::CreateSceneObject() {
	
	TaskManager* pTask = TaskManager::Instance();
	
	pTask->CreateObject(new CMainLight)->SetParent(this);
	pTask->CreateObject(new CMainCamera)->SetParent(this);
	pTask->CreateObject(new CSky)->SetParent(this);
	pTask->CreateObject(new CField)->SetParent(this);

	// �t�B�[���h�}�X�ƃL�����}�l�[�W���̐���
	CFieldMassManager* pFieldMassManager = CreateObject(new CFieldMassManager(7));
	pFieldMassManager->SetParent(this);

	CCharactorManager* pCharactorManager = CreateObject(new CCharactorManager(pFieldMassManager));
	pCharactorManager->SetParent(this);

	CreateObject(new CSelectMass(pCharactorManager, pFieldMassManager));	// �Z���N�g�}�X����

	return true;
}

//������������ SetParent��Y�ꂸ��!!! ������������
//������������ SetParent��Y�ꂸ��!!! ������������
//������������ SetParent��Y�ꂸ��!!! ������������