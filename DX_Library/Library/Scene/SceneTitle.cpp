//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneTitle.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SceneTitle.h"

#include "../../Object/Title/Test2D.h"

//������������ SetParent��Y�ꂸ��!!! ������������
//������������ SetParent��Y�ꂸ��!!! ������������
//������������ SetParent��Y�ꂸ��!!! ������������

CSceneTitle::CSceneTitle() {
	m_Transform.Name = "SceneTitle";
}

CSceneTitle::~CSceneTitle() {
	
}

bool CSceneTitle::CreateSceneObject() {
	
	TaskManager* pTask = TaskManager::Instance();

	pTask->CreateObject(new testObj2D)->SetParent(this);
	
	return true;
}

//������������ SetParent��Y�ꂸ��!!! ������������
//������������ SetParent��Y�ꂸ��!!! ������������
//������������ SetParent��Y�ꂸ��!!! ������������