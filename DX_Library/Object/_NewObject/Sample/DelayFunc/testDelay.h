//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [testDelay.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____testDelay_H_____
#define _____testDelay_H_____

#include <iostream>
#include "../Library/Task/TaskManager.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class testDelay : public GameObject {

private:
	CObject2D m_Object2D;

public:

	testDelay();
	~testDelay();

	bool Start();
	void Update();
	void Draw();
	
	testDelay* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "testDelay" ) // Ž¸”s!!!
			return nullptr;

		testDelay* Child = static_cast<testDelay*>(Obj); 
		return Child;
	}
};

#endif