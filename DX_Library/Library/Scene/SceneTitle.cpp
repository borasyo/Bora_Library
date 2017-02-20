//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneTitle.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SceneTitle.h"

#include "../../Object/Title/Test2D.h"

//※※※※※※ SetParentを忘れずに!!! ※※※※※※
//※※※※※※ SetParentを忘れずに!!! ※※※※※※
//※※※※※※ SetParentを忘れずに!!! ※※※※※※

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

//※※※※※※ SetParentを忘れずに!!! ※※※※※※
//※※※※※※ SetParentを忘れずに!!! ※※※※※※
//※※※※※※ SetParentを忘れずに!!! ※※※※※※