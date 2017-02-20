//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MoveMassBase.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MoveMassBase_H_____
#define _____MoveMassBase_H_____

#include <iostream>
#include "../../../../Library/Task/TaskManager.h"
#include "../../../../Library/Task/GameObject.h"
#include "../../../../Library/ObjectType/Object3D_Polygon.h"

class CMoveMassBase : public GameObject {

protected:
	CObject3DPolygon m_Mass;

public:

	CMoveMassBase();
	~CMoveMassBase();

	bool Start();
	void Update();
	void Draw();
	
	CMoveMassBase* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "MoveMassBase" ) // Ž¸”s!!!
			return nullptr;

		CMoveMassBase* Child = static_cast<CMoveMassBase*>(Obj); 
		return Child;
	}
};

#endif