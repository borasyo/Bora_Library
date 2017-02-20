//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneGameMain.h]
// author : 大洞祥太
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
	// そのシーンのマネージャーを務めるオブジェクトは保持しておくとよい

public:

	CSceneGameMain();
	~CSceneGameMain();
	
	bool CreateSceneObject();
	
	CSceneGameMain* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "SceneGameMain" ) // 失敗!!!
			return nullptr;

		CSceneGameMain* Child = static_cast<CSceneGameMain*>(Obj); 
		return Child;
	}
};

#endif