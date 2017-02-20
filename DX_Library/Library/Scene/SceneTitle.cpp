//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneTitle.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SceneTitle.h"

#include "../../Object/Title/Test2D.h"

//¦¦¦¦¦¦ SetParent‚ğ–Y‚ê‚¸‚É!!! ¦¦¦¦¦¦
//¦¦¦¦¦¦ SetParent‚ğ–Y‚ê‚¸‚É!!! ¦¦¦¦¦¦
//¦¦¦¦¦¦ SetParent‚ğ–Y‚ê‚¸‚É!!! ¦¦¦¦¦¦

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

//¦¦¦¦¦¦ SetParent‚ğ–Y‚ê‚¸‚É!!! ¦¦¦¦¦¦
//¦¦¦¦¦¦ SetParent‚ğ–Y‚ê‚¸‚É!!! ¦¦¦¦¦¦
//¦¦¦¦¦¦ SetParent‚ğ–Y‚ê‚¸‚É!!! ¦¦¦¦¦¦