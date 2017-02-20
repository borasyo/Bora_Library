//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneResult.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SceneResult_H_____
#define _____SceneResult_H_____

#include <iostream>
#include "../Task/TaskManager.h"
#include "../Task/GameObject.h"
#include "SceneBase.h"

class CSceneResult : public CSceneBase {

private:
	// ���̃V�[���̃}�l�[�W���[�𖱂߂�I�u�W�F�N�g�͕ێ����Ă����Ƃ悢

public:

	CSceneResult();
	~CSceneResult();
	
	bool CreateSceneObject();

	CSceneResult* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "SceneResult" ) // ���s!!!
			return nullptr;

		CSceneResult* Child = static_cast<CSceneResult*>(Obj); 
		return Child;
	}
};

#endif