//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [TestP.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TestP_H_____
#define _____TestP_H_____

#include <iostream>
#include "../Library/Task/TaskManager.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"
#include "../Library/DirectX/DirectInputManager.h"

class TestP : public GameObject {

private:
	CObject2D m_Object2D;
	CDirectInputManager* m_pDirectInputManager;

public:

	TestP();
	~TestP();

	bool Start();
	void Update();
	void Draw();
	void LateDraw();
	void OnCollisionEnter(GameObject* pObj);
	
	TestP* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		TestP* Child = static_cast<TestP*>(Obj); 
		return Child;
	}
};

#endif