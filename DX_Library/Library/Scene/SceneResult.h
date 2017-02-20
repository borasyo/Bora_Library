//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneResult.h]
// author : 大洞祥太
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
	// そのシーンのマネージャーを務めるオブジェクトは保持しておくとよい

public:

	CSceneResult();
	~CSceneResult();
	
	bool CreateSceneObject();

	CSceneResult* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "SceneResult" ) // 失敗!!!
			return nullptr;

		CSceneResult* Child = static_cast<CSceneResult*>(Obj); 
		return Child;
	}
};

#endif