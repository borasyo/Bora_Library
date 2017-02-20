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

class player : public GameObject {

private:
	CObject3DModel m_Obj;

public:

	player(){}
	~player(){}
	
	player* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		player* Child = static_cast<player*>(Obj); 
		return Child;
	}
};

class testObj : public player {

private:
	CObject3DModel m_Obj;

public:

	testObj();
	~testObj();

	bool Start();
	void Update();
	void Draw();
	
	testObj* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		testObj* Child = static_cast<testObj*>(Obj); 
		return Child;
	}
};

#endif