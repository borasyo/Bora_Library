//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneTitle.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SceneTitle_H_____
#define _____SceneTitle_H_____

#include <iostream>
#include "../Task/TaskManager.h"
#include "../Task/GameObject.h"
#include "SceneBase.h"

class CSceneTitle : public CSceneBase {

private:
	// そのシーンのマネージャーを務めるオブジェクトは保持しておくとよい

public:

	CSceneTitle();
	~CSceneTitle();

	bool CreateSceneObject();
	
	CSceneTitle* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "SceneTitle" ) // 失敗!!!
			return nullptr;

		CSceneTitle* Child = static_cast<CSceneTitle*>(Obj); 
		return Child;
	}
};

#endif