//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneStageSelect.h]
// author : 大洞祥太
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
	// そのシーンのマネージャーを務めるオブジェクトは保持しておくとよい

public:

	CSceneStageSelect();
	~CSceneStageSelect();
	
	bool CreateSceneObject();

	CSceneStageSelect* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "SceneStageSelect" ) // 失敗!!!
			return nullptr;

		CSceneStageSelect* Child = static_cast<CSceneStageSelect*>(Obj); 
		return Child;
	}
};

#endif