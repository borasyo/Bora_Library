//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [testcol.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____testcol_H_____
#define _____testcol_H_____

#include <iostream>
#include "../Library/Task/TaskManager.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Collision3D.h"
//#include "../Library/ObjectType/Collision2D.h"

class testcol : public GameObject {

private:
	Collision3D Collision;
	GameObject* pPlayer;
	GameObject* pEnemy;

public:

	testcol();
	~testcol();

	bool Start();
	void Update();
	void Draw();
	
	testcol* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		testcol* Child = static_cast<testcol*>(Obj); 
		return Child;
	}
};

#endif