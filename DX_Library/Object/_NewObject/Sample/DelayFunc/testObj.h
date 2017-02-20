//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [testObj.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____testObj_H_____
#define _____testObj_H_____

#include <iostream>
#include "../Library/Task/TaskManager.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"
#include "../Library/Function/DelayFunction.h"
#include "../Library/DirectX/DirectInputManager.h"

class testObj : public GameObject {

private:
	CObject3DModel m_Obj;
	CDelayFunctionManager* m_pDelayFuncManager;
	CDirectInputManager* m_pDirectInputManager;

public:

	testObj();
	~testObj();

	bool Start();
	void Update();
	void Draw();
	void CreateDelay();
	
	testObj* GetDownCastClass(GameObject* Obj) {
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		testObj* Child = static_cast<testObj*>(Obj); 
		return Child;
	}
};

#endif