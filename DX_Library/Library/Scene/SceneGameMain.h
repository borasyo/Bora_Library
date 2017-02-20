//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneGameMain.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SceneGameMain_H_____
#define _____SceneGameMain_H_____

#include <iostream>
#include "../Task/TaskManager.h"
#include "../Task/GameObject.h"
#include "SceneBase.h"

class CSceneGameMain : public CSceneBase {

private:
	// ���̃V�[���̃}�l�[�W���[�𖱂߂�I�u�W�F�N�g�͕ێ����Ă����Ƃ悢

public:

	CSceneGameMain();
	~CSceneGameMain();
	
	bool CreateSceneObject();
	
	CSceneGameMain* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "SceneGameMain" ) // ���s!!!
			return nullptr;

		CSceneGameMain* Child = static_cast<CSceneGameMain*>(Obj); 
		return Child;
	}
};

#endif