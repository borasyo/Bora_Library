//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneStageSelect.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SceneStageSelect_H_____
#define _____SceneStageSelect_H_____

#include <iostream>
#include "../Task/TaskManager.h"
#include "../Task/GameObject.h"
#include "SceneBase.h"

class CSceneStageSelect : public CSceneBase {

private:
	// ���̃V�[���̃}�l�[�W���[�𖱂߂�I�u�W�F�N�g�͕ێ����Ă����Ƃ悢

public:

	CSceneStageSelect();
	~CSceneStageSelect();
	
	bool CreateSceneObject();

	CSceneStageSelect* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "SceneStageSelect" ) // ���s!!!
			return nullptr;

		CSceneStageSelect* Child = static_cast<CSceneStageSelect*>(Obj); 
		return Child;
	}
};

#endif