//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneResult.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SceneResult.h"

//※※※※※※ SetParentを忘れずに!!! ※※※※※※
//※※※※※※ SetParentを忘れずに!!! ※※※※※※
//※※※※※※ SetParentを忘れずに!!! ※※※※※※

CSceneResult::CSceneResult() {
	m_Transform.Name = "SceneResult";
}

CSceneResult::~CSceneResult() {
	
}

bool CSceneResult::CreateSceneObject() { 
	
	TaskManager* pTask = TaskManager::Instance();

	return true;
}

//※※※※※※ SetParentを忘れずに!!! ※※※※※※
//※※※※※※ SetParentを忘れずに!!! ※※※※※※
//※※※※※※ SetParentを忘れずに!!! ※※※※※※