//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneStageSelect.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SceneStageSelect.h"

//※※※※※※ SetParentを忘れずに!!! ※※※※※※
//※※※※※※ SetParentを忘れずに!!! ※※※※※※
//※※※※※※ SetParentを忘れずに!!! ※※※※※※

CSceneStageSelect::CSceneStageSelect() {
	m_Transform.Name = "SceneStageSelect";
}

CSceneStageSelect::~CSceneStageSelect() {
	
}

bool CSceneStageSelect::CreateSceneObject() {
	
	TaskManager* pTask = TaskManager::Instance();

	return true;
}

//※※※※※※ SetParentを忘れずに!!! ※※※※※※
//※※※※※※ SetParentを忘れずに!!! ※※※※※※
//※※※※※※ SetParentを忘れずに!!! ※※※※※※