//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneBase.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SceneBase_H_____
#define _____SceneBase_H_____

#include <iostream>
#include "../Task/TaskManager.h"
#include "../Task/GameObject.h"
#include "../Task/Empty.h"
#include "../Task/EmptyCollision.h"

class CSceneBase : public GameObject {

protected:
	TaskManager* m_pCreator;

public:

	CSceneBase();
	~CSceneBase();

	virtual bool CreateSceneObject() { return true; }
	
	CSceneBase* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "SceneBase" ) // Ž¸”s!!!
			return nullptr;

		CSceneBase* Child = static_cast<CSceneBase*>(Obj); 
		return Child;
	}
};

#endif